// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#include "opentelemetry/exporters/otlp/otlp_file_log_record_exporter_factory.h"
#include "opentelemetry/exporters/otlp/otlp_file_log_record_exporter.h"
#include "opentelemetry/exporters/otlp/otlp_file_log_record_exporter_options.h"

OPENTELEMETRY_BEGIN_NAMESPACE
namespace exporter
{
namespace otlp
{

std::unique_ptr<opentelemetry::sdk::logs::LogRecordExporter>
OtlpFileLogRecordExporterFactory::Create()
{
  OtlpFileLogRecordExporterOptions options;
  return Create(options);
}

std::unique_ptr<opentelemetry::sdk::logs::LogRecordExporter>
OtlpFileLogRecordExporterFactory::Create(const OtlpFileLogRecordExporterOptions &options)
{
  std::unique_ptr<opentelemetry::sdk::logs::LogRecordExporter> exporter(
      new OtlpFileLogRecordExporter(options));
  return exporter;
}

}  // namespace otlp
}  // namespace exporter
OPENTELEMETRY_END_NAMESPACE
