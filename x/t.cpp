#include <thread>
#include <condition_variable>
#include <mutex>
#include <memory>

#include "opentelemetry/sdk/version/version.h"

// api headers (logs, traces, metrics)
#include "opentelemetry/logs/provider.h"
#include "opentelemetry/metrics/provider.h"
#include "opentelemetry/trace/provider.h"

// sdk providers (logs, traces, metrics)
#include "opentelemetry/sdk/logs/logger_provider_factory.h"
#include "opentelemetry/sdk/metrics/meter_provider_factory.h"
#include "opentelemetry/sdk/trace/tracer_provider_factory.h"

// sdk metric views
#include "opentelemetry/sdk/metrics/view/instrument_selector_factory.h"
#include "opentelemetry/sdk/metrics/view/meter_selector_factory.h"
#include "opentelemetry/sdk/metrics/view/view_factory.h"

// sdk processors (simple logs, simple traces, periodic exporting metrics)
#include "opentelemetry/sdk/logs/simple_log_record_processor_factory.h"
#include "opentelemetry/sdk/metrics/export/periodic_exporting_metric_reader_factory.h"
#include "opentelemetry/sdk/trace/simple_processor_factory.h"

// sdk exporter factories (logs, traces, metrics)
#include "opentelemetry/exporters/ostream/log_record_exporter.h"
#include "opentelemetry/exporters/ostream/metric_exporter_factory.h"
#include "opentelemetry/exporters/ostream/span_exporter_factory.h"
#include "opentelemetry/exporters/otlp/otlp_grpc_forward_proxy.h"
#include "opentelemetry/exporters/otlp/otlp_environment.h"

#include <opentelemetry/metrics/provider.h>
#include <opentelemetry/sdk/common/global_log_handler.h>
#include <opentelemetry/sdk/common/env_variables.h>
#include <opentelemetry/sdk/resource/semantic_conventions.h>
#include <opentelemetry/sdk/metrics/meter_provider_factory.h>
#include <opentelemetry/sdk/metrics/export/periodic_exporting_metric_reader_factory.h>
#include <opentelemetry/exporters/otlp/otlp_grpc_metric_exporter_factory.h>

#include <opentelemetry/version.h>
#include <opentelemetry/trace/provider.h>
#include <opentelemetry/logs/provider.h>
#include <opentelemetry/sdk/common/global_log_handler.h>
#include <opentelemetry/sdk/common/env_variables.h>
#include <opentelemetry/sdk/resource/semantic_conventions.h>
#include <opentelemetry/sdk/trace/tracer_provider.h>
#include <opentelemetry/sdk/trace/tracer_provider_factory.h>
#include <opentelemetry/sdk/trace/batch_span_processor_options.h>
#include <opentelemetry/sdk/trace/batch_span_processor_factory.h>
#include "opentelemetry/sdk/trace/processor.h"
#include <opentelemetry/sdk/logs/logger_provider_factory.h>
#include <opentelemetry/sdk/logs/batch_log_record_processor_options.h>
#include <opentelemetry/sdk/logs/batch_log_record_processor_factory.h>
#include <opentelemetry/sdk/logs/processor.h>
#include <opentelemetry/exporters/otlp/otlp_grpc_exporter_factory.h>
#include <opentelemetry/exporters/otlp/otlp_grpc_log_record_exporter_factory.h>

opentelemetry::nostd::shared_ptr<opentelemetry::trace::Tracer> get_tracer()
{
  auto provider = opentelemetry::trace::Provider::GetTracerProvider();
  return provider->GetTracer("foo_tracer", OPENTELEMETRY_SDK_VERSION);
}

opentelemetry::nostd::shared_ptr<opentelemetry::logs::Logger> get_logger()
{
  auto provider = opentelemetry::logs::Provider::GetLoggerProvider();
  return provider->GetLogger("foo_lbrary_logger", "foo_logger");
}

void traces_f1()
{
  auto scoped_span = opentelemetry::trace::Scope(get_tracer()->StartSpan("malkia_span_f1"));
}

void traces_f2()
{
  auto scoped_span = opentelemetry::trace::Scope(get_tracer()->StartSpan("malkia_span_f2"));
  traces_f1();
  traces_f1();
}

void traces_foo_library()
{
  auto scoped_span = opentelemetry::trace::Scope(get_tracer()->StartSpan("malkia_span_library"));
  traces_f2();
}

void logs_foo_library()
{
  auto span        = get_tracer()->StartSpan("malkia span 1");
  auto scoped_span = opentelemetry::trace::Scope(get_tracer()->StartSpan("malkia_span_foo_library"));
  auto ctx         = span->GetContext();
  auto logger      = get_logger();

  logger->Debug("malkia_logs_test", ctx.trace_id(), ctx.span_id(), ctx.trace_flags());
}

static opentelemetry::nostd::shared_ptr<opentelemetry::metrics::ObservableInstrument>
    double_observable_counter;

std::map<std::string, std::string> get_random_attr()
{
  const std::vector<std::pair<std::string, std::string>> labels = {{"key1", "value1"},
                                                                   {"key5", "value5"}};
  return std::map<std::string, std::string>{labels[rand() % (labels.size() - 1)],
                                            labels[rand() % (labels.size() - 1)]};
}

class MeasurementFetcher
{
public:
  static void Fetcher(opentelemetry::metrics::ObserverResult observer_result, void * /* state */)
  {
    if (opentelemetry::nostd::holds_alternative<
            opentelemetry::nostd::shared_ptr<opentelemetry::metrics::ObserverResultT<double>>>(
            observer_result))
    {
      double random_incr = (rand() % 5) + 1.1;
      value_ += random_incr;
      std::map<std::string, std::string> labels = get_random_attr();
      opentelemetry::nostd::get<
          opentelemetry::nostd::shared_ptr<opentelemetry::metrics::ObserverResultT<double>>>(
          observer_result)
          ->Observe(value_, labels);
    }
  }
  static double value_;
};
double MeasurementFetcher::value_ = 0.0;

void metrics_counter_example(const std::string &name)
{
  std::string counter_name = name + "_counter";
  auto provider            = opentelemetry::metrics::Provider::GetMeterProvider();
  opentelemetry::nostd::shared_ptr<opentelemetry::metrics::Meter> meter =
      provider->GetMeter(name, "1.2.0");
  auto double_counter = meter->CreateDoubleCounter(counter_name);

  for (uint32_t i = 0; i < 2000; ++i)
  {
    double val = (rand() % 700) + 1.1;
    double_counter->Add(val);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}

void metrics_observable_counter_example(const std::string &name)
{
  std::string counter_name = name + "_observable_counter";
  auto provider            = opentelemetry::metrics::Provider::GetMeterProvider();
  opentelemetry::nostd::shared_ptr<opentelemetry::metrics::Meter> meter =
      provider->GetMeter(name, "1.2.0");
  double_observable_counter = meter->CreateDoubleObservableCounter(counter_name);
  double_observable_counter->AddCallback(MeasurementFetcher::Fetcher, nullptr);
  for (uint32_t i = 0; i < 2000; ++i)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}

void metrics_histogram_example(const std::string &name)
{
  std::string histogram_name = name + "_histogram";
  auto provider              = opentelemetry::metrics::Provider::GetMeterProvider();
  opentelemetry::nostd::shared_ptr<opentelemetry::metrics::Meter> meter =
      provider->GetMeter(name, "1.2.0");
  auto histogram_counter = meter->CreateDoubleHistogram(histogram_name, "des", "unit");
  auto context           = opentelemetry::context::Context{};
  for (uint32_t i = 0; i < 2000; ++i)
  {
    double val                                = (rand() % 700) + 1.1;
    std::map<std::string, std::string> labels = get_random_attr();
    auto labelkv = opentelemetry::common::KeyValueIterableView<decltype(labels)>{labels};
    histogram_counter->Record(val, labelkv, context);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}

void InitTracer()
{
  // auto exporter = opentelemetry::exporter::trace::OStreamSpanExporterFactory::Create();
  // auto processor =
  //     opentelemetry::sdk::trace::SimpleSpanProcessorFactory::Create(std::move(exporter));

  // std::shared_ptr<opentelemetry::sdk::trace::TracerProvider> sdk_provider =
  //     opentelemetry::sdk::trace::TracerProviderFactory::Create(std::move(processor));

  // // Set the global trace provider
  // const std::shared_ptr<opentelemetry::trace::TracerProvider> &api_provider = sdk_provider;
  // opentelemetry::trace::Provider::SetTracerProvider(api_provider);

    using namespace opentelemetry;

        exporter::otlp::OtlpGrpcExporterOptions exporterOptions;
        // GTEST_LOG_( INFO ) << "\n"
        //                                    << "otlp trace exporter: " << exporterOptions.endpoint << "\n"
        //                                    << "otlp trace user_agent: " << exporterOptions.user_agent << "\n";
        auto exporter{ exporter::otlp::OtlpGrpcExporterFactory::Create( exporterOptions ) };

        sdk::trace::BatchSpanProcessorOptions batchProcessorOptions;
        batchProcessorOptions.max_export_batch_size = 4096;
        batchProcessorOptions.max_queue_size = 16384;
        batchProcessorOptions.schedule_delay_millis = std::chrono::milliseconds{ 1000 };
        auto batchProcessor{ sdk::trace::BatchSpanProcessorFactory::Create( std::move( exporter ), batchProcessorOptions ) };

        std::vector<std::unique_ptr<sdk::trace::SpanProcessor>> spanProcessors;
        spanProcessors.emplace_back( std::move( batchProcessor ) );
        const std::shared_ptr tracerProvider{ sdk::trace::TracerProviderFactory::Create( std::move( spanProcessors ) ) };

        trace::Provider::SetTracerProvider( tracerProvider );

}

void InitLogger()
{
  // // Create ostream log exporter instance
  // auto exporter = std::unique_ptr<opentelemetry::sdk::logs::LogRecordExporter>(
  //     new opentelemetry::exporter::logs::OStreamLogRecordExporter);
  // auto processor =
  //     opentelemetry::sdk::logs::SimpleLogRecordProcessorFactory::Create(std::move(exporter));

  // std::shared_ptr<opentelemetry::sdk::logs::LoggerProvider> sdk_provider(
  //     opentelemetry::sdk::logs::LoggerProviderFactory::Create(std::move(processor)));

  // // Set the global logger provider
  // const std::shared_ptr<opentelemetry::logs::LoggerProvider> &api_provider = sdk_provider;
  // opentelemetry::logs::Provider::SetLoggerProvider(api_provider);

    using namespace opentelemetry;

  exporter::otlp::OtlpGrpcLogRecordExporterOptions log_opts;
  auto exporter = exporter::otlp::OtlpGrpcLogRecordExporterFactory::Create( log_opts );
  sdk::logs::BatchLogRecordProcessorOptions processorOptions;
  processorOptions.max_export_batch_size = 4096;
  processorOptions.max_queue_size = 16384;
  processorOptions.schedule_delay_millis = std::chrono::milliseconds{ 1000 };
  auto processor = sdk::logs::BatchLogRecordProcessorFactory::Create( std::move( exporter ), processorOptions );

  std::vector<std::unique_ptr<sdk::logs::LogRecordProcessor>> logRecordProcessors;
  logRecordProcessors.emplace_back( std::move( processor ) );

#if 0
  exporter::logs::ElasticsearchExporterOptions elasticOptions;
  elasticOptions.console_debug_ = true;
  elasticOptions.port_ = 9200;
  elasticOptions.host_ = "localhost:";
  elasticOptions.index_ = "otel2";
  {
          nostd::unique_ptr<sdk::logs::LogRecordExporter> elasticExporter( new exporter::logs::ElasticsearchLogRecordExporter(elasticOptions) );
          sdk::logs::BatchLogRecordProcessorOptions processorOptions2;
          processorOptions2.max_export_batch_size = 128;
          processorOptions2.max_queue_size = 256;
          processorOptions2.schedule_delay_millis = std::chrono::milliseconds{ 1000 };
          auto elasticProcessor = sdk::logs::BatchLogRecordProcessorFactory::Create(std::move(elasticExporter), processorOptions);
          logRecordProcessors.emplace_back(std::move(elasticProcessor));
  }
#endif // #if 0

  nostd::shared_ptr<logs::LoggerProvider> provider( sdk::logs::LoggerProviderFactory::Create( std::move( logRecordProcessors ) ) );
  logs::Provider::SetLoggerProvider( provider );
}

void CleanupTracer()
{
  std::shared_ptr<opentelemetry::trace::TracerProvider> noop;
  opentelemetry::trace::Provider::SetTracerProvider(noop);
}

void CleanupLogger()
{
  std::shared_ptr<opentelemetry::logs::LoggerProvider> noop;
  opentelemetry::logs::Provider::SetLoggerProvider(noop);
}

void InitMetrics(const std::string &name)
{
  #if 0
  auto exporter = opentelemetry::exporter::metrics::OStreamMetricExporterFactory::Create();
  #else
    opentelemetry::exporter::otlp::OtlpGrpcMetricExporterOptions exporterOptions;
    //exporterOptions.compression = "gzip";
    auto exporter{ opentelemetry::exporter::otlp::OtlpGrpcMetricExporterFactory::Create( exporterOptions ) };
  #endif

  std::string version{"1.2.0"};
  std::string schema{"https://opentelemetry.io/schemas/1.2.0"};

  // Initialize and set the global MeterProvider
  opentelemetry::sdk::metrics::PeriodicExportingMetricReaderOptions options;
  options.export_interval_millis = std::chrono::milliseconds(100);
  options.export_timeout_millis  = std::chrono::milliseconds(50);

  auto reader = opentelemetry::sdk::metrics::PeriodicExportingMetricReaderFactory::Create(
      std::move(exporter), options);

  auto provider = opentelemetry::sdk::metrics::MeterProviderFactory::Create();

  provider->AddMetricReader(std::move(reader));

  // counter view
  std::string counter_name = name + "_counter";
  std::string unit         = "counter-unit";

  auto instrument_selector = opentelemetry::sdk::metrics::InstrumentSelectorFactory::Create(
      opentelemetry::sdk::metrics::InstrumentType::kCounter, counter_name, unit);

  auto meter_selector =
      opentelemetry::sdk::metrics::MeterSelectorFactory::Create(name, version, schema);

  auto sum_view = opentelemetry::sdk::metrics::ViewFactory::Create(
      name, "description", unit, opentelemetry::sdk::metrics::AggregationType::kSum);

  provider->AddView(std::move(instrument_selector), std::move(meter_selector), std::move(sum_view));

  // observable counter view
  std::string observable_counter_name = name + "_observable_counter";

  auto observable_instrument_selector =
      opentelemetry::sdk::metrics::InstrumentSelectorFactory::Create(
          opentelemetry::sdk::metrics::InstrumentType::kObservableCounter, observable_counter_name,
          unit);

  auto observable_meter_selector =
      opentelemetry::sdk::metrics::MeterSelectorFactory::Create(name, version, schema);

  auto observable_sum_view = opentelemetry::sdk::metrics::ViewFactory::Create(
      name, "test_description", unit, opentelemetry::sdk::metrics::AggregationType::kSum);

  provider->AddView(std::move(observable_instrument_selector), std::move(observable_meter_selector),
                    std::move(observable_sum_view));

  // histogram view
  std::string histogram_name = name + "_histogram";
  unit                       = "histogram-unit";

  auto histogram_instrument_selector =
      opentelemetry::sdk::metrics::InstrumentSelectorFactory::Create(
          opentelemetry::sdk::metrics::InstrumentType::kHistogram, histogram_name, unit);

  auto histogram_meter_selector =
      opentelemetry::sdk::metrics::MeterSelectorFactory::Create(name, version, schema);

  auto histogram_aggregation_config =
      std::unique_ptr<opentelemetry::sdk::metrics::HistogramAggregationConfig>(
          new opentelemetry::sdk::metrics::HistogramAggregationConfig);

  histogram_aggregation_config->boundaries_ = std::vector<double>{
      0.0, 50.0, 100.0, 250.0, 500.0, 750.0, 1000.0, 2500.0, 5000.0, 10000.0, 20000.0};

  std::shared_ptr<opentelemetry::sdk::metrics::AggregationConfig> aggregation_config(
      std::move(histogram_aggregation_config));

  auto histogram_view = opentelemetry::sdk::metrics::ViewFactory::Create(
      name, "description", unit, opentelemetry::sdk::metrics::AggregationType::kHistogram,
      aggregation_config);

  provider->AddView(std::move(histogram_instrument_selector), std::move(histogram_meter_selector),
                    std::move(histogram_view));

  std::shared_ptr<opentelemetry::metrics::MeterProvider> api_provider(std::move(provider));
  opentelemetry::metrics::Provider::SetMeterProvider(api_provider);
}

void CleanupMetrics()
{
  std::shared_ptr<opentelemetry::metrics::MeterProvider> none;
  opentelemetry::metrics::Provider::SetMeterProvider(none);
}

int main()
{
  setvbuf(stdout, nullptr, _IONBF,0);
  setvbuf(stderr, nullptr, _IONBF,0);
  setvbuf(stdin, nullptr, _IONBF,0);

  {
    using namespace opentelemetry::sdk::common::internal_log;
    GlobalLogHandler::SetLogLevel(LogLevel::Debug);
  }

  InitMetrics("malkia_metrics");

  auto provider{ opentelemetry::metrics::Provider::GetMeterProvider() };
  auto meter{ provider->GetMeter("malkia_test_meter", "1.2.0") };
  auto counter{ meter->CreateDoubleCounter("malkia_test_counter") }; 

  for(int i=0; i<10; i++)
  {
    counter->Add(1);
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1000ms);
  }

  CleanupMetrics();
  opentelemetry::metrics::Provider::SetMeterProvider({});
 
  return 0;
}
