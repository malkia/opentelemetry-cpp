// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#include <gtest/gtest.h>
#include <memory>
#include <string>

#include "opentelemetry/version.h"
#include "opentelemetry/exporters/otlp/otlp_file_metric_exporter_factory.h"
#include "opentelemetry/exporters/otlp/otlp_file_metric_exporter_options.h"
#include "opentelemetry/sdk/metrics/push_metric_exporter.h"

/*
  Make sure OtlpFileExporterFactory does not require,
  even indirectly, nlohmann/json headers.
*/
#ifdef NLOHMANN_JSON_VERSION_MAJOR
#  error "nlohmann/json should not be included"
#endif /* NLOHMANN_JSON_VERSION_MAJOR */

/*
  Make sure OtlpFileExporterFactory does not require,
  even indirectly, protobuf headers.
*/
#ifdef GOOGLE_PROTOBUF_VERSION
#  error "protobuf should not be included"
#endif

OPENTELEMETRY_BEGIN_NAMESPACE
namespace exporter
{
namespace otlp
{

TEST(OtlpFileMetricExporterFactory, BuildTest)
{
  OtlpFileMetricExporterOptions opts;
  std::unique_ptr<opentelemetry::sdk::metrics::PushMetricExporter> exporter =
      OtlpFileMetricExporterFactory::Create(opts);

  EXPECT_TRUE(exporter != nullptr);
}

}  // namespace otlp
}  // namespace exporter
OPENTELEMETRY_END_NAMESPACE
