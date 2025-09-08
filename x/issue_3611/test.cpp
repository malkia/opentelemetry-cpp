// https://github.com/open-telemetry/opentelemetry-cpp/issues/3611

#include <memory>
#include <thread>

#include "opentelemetry/version.h"
#include "opentelemetry/exporters/ostream/metric_exporter_factory.h"
#include "opentelemetry/metrics/provider.h"
#include "opentelemetry/sdk/metrics/aggregation/default_aggregation.h"
#include "opentelemetry/sdk/metrics/aggregation/histogram_aggregation.h"
#include "opentelemetry/sdk/metrics/export/periodic_exporting_metric_reader_factory.h"
#include "opentelemetry/sdk/metrics/meter.h"
#include "opentelemetry/sdk/metrics/meter_provider.h"
#include "opentelemetry/sdk/metrics/meter_provider_factory.h"
#include "opentelemetry/sdk/metrics/push_metric_exporter.h"
#include "opentelemetry/sdk/metrics/view/instrument_selector_factory.h"
#include "opentelemetry/sdk/metrics/view/meter_selector_factory.h"
#include "opentelemetry/sdk/metrics/view/view_factory.h"
#include "opentelemetry/context/context.h"
#include "opentelemetry/nostd/shared_ptr.h"

namespace nostd = opentelemetry::nostd;
namespace metrics_sdk = opentelemetry::sdk::metrics;
namespace common = opentelemetry::common;

namespace metrics_api = opentelemetry::metrics;
namespace exportermetrics = opentelemetry::exporter::metrics;

namespace
{

    std::map<std::string, std::string> get_random_attr()
    {
        const std::vector<std::pair<std::string, std::string> > labels = {{"key1", "value1"},
                                                                          {"key2", "value2"},
                                                                          {"key3", "value3"},
                                                                          {"key4", "value4"},
                                                                          {"key5", "value5"}};
        return std::map<std::string, std::string>{labels[rand() % (labels.size() - 1)],
                                                  labels[rand() % (labels.size() - 1)]};
    }

    void InitMetrics(const std::string &name)
    {

        auto exporter = exportermetrics::OStreamMetricExporterFactory::Create();

        std::string version{"1.2.0"};
        std::string schema{"https://opentelemetry.io/schemas/1.2.0"};

        // Initialize and set the global MeterProvider
        metrics_sdk::PeriodicExportingMetricReaderOptions options;
        options.export_interval_millis = std::chrono::milliseconds(1000);
        options.export_timeout_millis = std::chrono::milliseconds(500);

        auto reader = metrics_sdk::PeriodicExportingMetricReaderFactory::Create(std::move(exporter), options);

        auto u_provider = metrics_sdk::MeterProviderFactory::Create();
        auto *p = static_cast<metrics_sdk::MeterProvider *>(u_provider.get());

        p->AddMetricReader(std::move(reader));

        /*metrics_exporter::PrometheusExporterOptions opts;
        if (!addr.empty())
        {
            opts.url = addr;
        }
        */
        // std::puts("PrometheusExporter example program running ...");

        // auto prometheus_exporter = metrics_exporter::PrometheusExporterFactory::Create(opts);
        //  auto exporter = exportermetrics::OStreamMetricExporterFactory::Create();

        // std::string version{"1.2.0"};
        // std::string schema{"https://opentelemetry.io/schemas/1.2.0"};

        // Initialize and set the global MeterProvider
        // metrics_sdk::PeriodicExportingMetricReaderOptions options;
        // options.export_interval_millis = std::chrono::milliseconds(1000);
        // options.export_timeout_millis = std::chrono::milliseconds(500);

        // auto reader =
        //    metrics_sdk::PeriodicExportingMetricReaderFactory::Create(std::move(exporter), options);

        // auto u_provider = metrics_sdk::MeterProviderFactory::Create();
        // auto *p = static_cast<metrics_sdk::MeterProvider *>(u_provider.get());

        // p->AddMetricReader(std::move(prometheus_exporter));

        // histogram view
        std::string histogram_name = name + "_histogram";
        std::string unit = "histogram-unit";

        auto histogram_instrument_selector = metrics_sdk::InstrumentSelectorFactory::Create(
            metrics_sdk::InstrumentType::kHistogram, histogram_name, unit);

        auto histogram_meter_selector = metrics_sdk::MeterSelectorFactory::Create(name, version, schema);

        auto histogram_aggregation_config = std::unique_ptr<metrics_sdk::HistogramAggregationConfig>(
            new metrics_sdk::HistogramAggregationConfig);

        histogram_aggregation_config->boundaries_ = std::vector<double>{
      0.0, 50.0, 100.0, 250.0, 500.0, 750.0, 1000.0, 2500.0, 5000.0, 10000.0, 20000.0};

        std::shared_ptr<metrics_sdk::AggregationConfig> aggregation_config(
            std::move(histogram_aggregation_config));

        // Code in the issue used otel 1.1.1 where the API had "unit", new one no longer has it
        auto histogram_view = metrics_sdk::ViewFactory::Create(
            name, "description", /* unit, */ metrics_sdk::AggregationType::kHistogram, aggregation_config);

        p->AddView(std::move(histogram_instrument_selector), std::move(histogram_meter_selector),
                   std::move(histogram_view));

        std::shared_ptr<opentelemetry::metrics::MeterProvider> provider(std::move(u_provider));
        metrics_api::Provider::SetMeterProvider(provider);
    }

    void CleanupMetrics()
    {
        std::shared_ptr<metrics_api::MeterProvider> none;
        metrics_api::Provider::SetMeterProvider(none);
    }
} // namespace

void histogram_example(const std::string &name)
{
    std::string histogram_name = name + "_histogram";
    auto provider = metrics_api::Provider::GetMeterProvider();
    nostd::shared_ptr<metrics_api::Meter> meter = provider->GetMeter(name, "1.2.0");
    auto histogram_counter = meter->CreateDoubleHistogram(histogram_name, "des", "histogram-unit");
    auto context = opentelemetry::context::Context{};
    for (uint32_t i = 0; i < 20; ++i)
    {
        double val = (rand() % 700) + 1.1;
        std::map<std::string, std::string> labels = get_random_attr();
        auto labelkv = opentelemetry::common::KeyValueIterableView<decltype(labels)>{labels};
        std::cout << "histogram val is " << val << std::endl;
        histogram_counter->Record(val, labelkv, context);
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
}

int main(int argc, char **argv)
{
    std::string name{"ostream_metric_example"};
    InitMetrics(name);
    histogram_example(name);
    CleanupMetrics();
    return 0;
}