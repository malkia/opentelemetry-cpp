#include <thread>

#include <opentelemetry/metrics/provider.h>
#include <opentelemetry/exporters/otlp/otlp_grpc_metric_exporter_factory.h>
#include <opentelemetry/sdk/metrics/export/periodic_exporting_metric_reader_factory.h>
#include <opentelemetry/sdk/metrics/meter_provider_factory.h>
#include <opentelemetry/semconv/incubating/process_attributes.h>
#include <opentelemetry/semconv/service_attributes.h>

#include <opentelemetry/sdk/common/global_log_handler.h>

static void metricsCleanup()
{
  using namespace opentelemetry;
  const auto mp{ std::dynamic_pointer_cast<sdk::metrics::MeterProvider>(metrics::Provider::GetMeterProvider()) };
  if( !mp )
    return;
  const auto p{ mp.get() };
  if( !p )
      return;
  p->ForceFlush();
  p->Shutdown();
}

struct MetricsCleanup
{
  ~MetricsCleanup()
  {
    metricsCleanup();
  }
};

static MetricsCleanup g_metricsCleanup;

int main(int argc, const char *argv[])
{
  {
    setvbuf(stdout, nullptr, _IONBF,0);
    setvbuf(stderr, nullptr, _IONBF,0);
    setvbuf(stdin, nullptr, _IONBF,0);

      // using namespace opentelemetry::sdk::common::internal_log;
      // GlobalLogHandler::SetLogLevel(LogLevel::Debug);
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

  {
    using namespace opentelemetry;
    
    auto exporter{exporter::otlp::OtlpGrpcMetricExporterFactory::Create({})};

    sdk::metrics::PeriodicExportingMetricReaderOptions options;
    options.export_interval_millis = std::chrono::milliseconds(100);
    options.export_timeout_millis = std::chrono::milliseconds(50);

    auto reader{sdk::metrics::PeriodicExportingMetricReaderFactory::Create(std::move(exporter), options)};

    auto meterProvider{sdk::metrics::MeterProviderFactory::Create()};
    meterProvider->AddMetricReader(std::move(reader));

    metrics::Provider::SetMeterProvider(std::move(meterProvider));
  }

  {
    using namespace opentelemetry;

    const auto apiMetricProvider{metrics::Provider::GetMeterProvider()};
    const auto meter{apiMetricProvider->GetMeter("malkia_test_meter", "1.2.3")};
    auto counter{meter->CreateUInt64Counter("malkia_test_monotonic")};
    auto udcounter{meter->CreateInt64UpDownCounter("malkia_test_up_down")};
    bool flip{false};
    int period{0};
    srand(GetCurrentProcessId());
    for (size_t i = 0; i < 1000; i++)
    {
      if( i % 100 == 0 )
      {
        printf("%zd ", i); fflush(stdout);
      }
      flip = !flip;
      if (flip)
        period = rand() % 1000;
      counter->Add(1);//, {{"test1", "one"}, {"test2", "two"}});
      if( flip )
        udcounter->Add(3);//, {{"test1", "one"}, {"test2", "two"}});
      else
        udcounter->Add(-1);//, {{"test1", "one"}, {"test2", "two"}});
      std::this_thread::sleep_for(std::chrono::milliseconds(flip ? period : 1000 - period));
    }
  }

  return 0;
}
