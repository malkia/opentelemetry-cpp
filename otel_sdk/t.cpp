#include <thread>

#include <opentelemetry/exporters/ostream/metric_exporter_factory.h>
#include <opentelemetry/exporters/otlp/otlp_grpc_metric_exporter_factory.h>

#include <opentelemetry/metrics/provider.h>

#include <opentelemetry/sdk/common/global_log_handler.h>
#include <opentelemetry/sdk/metrics/export/periodic_exporting_metric_reader_factory.h>
#include <opentelemetry/sdk/metrics/meter_provider_factory.h>

#include <opentelemetry/semconv/incubating/process_attributes.h>
#include <opentelemetry/semconv/service_attributes.h>

int main(int argc, const char *argv[])
{

  int index = argc == 2 ? atoi(argv[1]) : -1;

  setvbuf(stdout, nullptr, _IONBF, 0);
  setvbuf(stderr, nullptr, _IONBF, 0);
  setvbuf(stdin, nullptr, _IONBF, 0);

  {
    using namespace opentelemetry::sdk::common::internal_log;
    //    GlobalLogHandler::SetLogLevel(LogLevel::Debug);
  }

  {
    using namespace opentelemetry;
    using namespace sdk::resource;
    ResourceAttributes resources{
        {semconv::process::kProcessPid, (int64_t)GetCurrentProcessId()},
        {semconv::service::kServiceName, "t"},
    };
    auto resource          = Resource::Create(resources);
    Resource::GetDefault() = resource;
  }

  // Initialize and set the global MeterProvider
  {
    auto exporter{opentelemetry::exporter::otlp::OtlpGrpcMetricExporterFactory::Create({})};
    auto stdoutExporter = opentelemetry::exporter::metrics::OStreamMetricExporterFactory::Create();
    opentelemetry::sdk::metrics::PeriodicExportingMetricReaderOptions options;
    options.export_interval_millis = std::chrono::milliseconds(100);
    options.export_timeout_millis  = std::chrono::milliseconds(50);
    auto reader{opentelemetry::sdk::metrics::PeriodicExportingMetricReaderFactory::Create(
        std::move(exporter), options)};
    auto stdoutReader{opentelemetry::sdk::metrics::PeriodicExportingMetricReaderFactory::Create(
        std::move(stdoutExporter), options)};
    auto meterProvider{opentelemetry::sdk::metrics::MeterProviderFactory::Create()};
    meterProvider->AddMetricReader(std::move(reader));
    //    meterProvider->AddMetricReader(std::move(stdoutReader));
    opentelemetry::metrics::Provider::SetMeterProvider(std::move(meterProvider));
  }

  {
    const auto apiMetricProvider{opentelemetry::metrics::Provider::GetMeterProvider()};
    const auto meter{apiMetricProvider->GetMeter("test_meter", "666")};
    auto counter{meter->CreateUInt64Counter("test_value")};
    srand(index);
    bool flip{false};
    int period{0};
    for (size_t i = 0; i < 64; i++)
    {
      flip = !flip;
      if (flip)
        period = rand() % 100;
      printf(".");
      counter->Add(1); //, {{"test", "one"}});
      std::this_thread::sleep_for(std::chrono::milliseconds(flip ? period : 100 - period));
    }
  }

  if (const auto mp{std::dynamic_pointer_cast<opentelemetry::sdk::metrics::MeterProvider>(
          opentelemetry::metrics::Provider::GetMeterProvider())};
      mp)
  {
    if (const auto p{mp.get()}; p)
    {
      p->ForceFlush();
      p->Shutdown();
    }
  }

  return 0;
}
