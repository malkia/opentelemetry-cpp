// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <memory>

#include "opentelemetry/version.h"
#include "opentelemetry/sdk/configuration/otlp_grpc_log_record_exporter_configuration.h"
#include "opentelemetry/sdk/logs/exporter.h"

OPENTELEMETRY_BEGIN_NAMESPACE
namespace sdk
{
namespace configuration
{

class OtlpGrpcLogRecordExporterBuilder
{
public:
  OtlpGrpcLogRecordExporterBuilder()                                               = default;
  OtlpGrpcLogRecordExporterBuilder(OtlpGrpcLogRecordExporterBuilder &&)            = default;
  OtlpGrpcLogRecordExporterBuilder(const OtlpGrpcLogRecordExporterBuilder &)       = default;
  OtlpGrpcLogRecordExporterBuilder &operator=(OtlpGrpcLogRecordExporterBuilder &&) = default;
  OtlpGrpcLogRecordExporterBuilder &operator=(const OtlpGrpcLogRecordExporterBuilder &other) =
      default;
  virtual ~OtlpGrpcLogRecordExporterBuilder() = default;

  virtual std::unique_ptr<opentelemetry::sdk::logs::LogRecordExporter> Build(
      const opentelemetry::sdk::configuration::OtlpGrpcLogRecordExporterConfiguration *model)
      const = 0;
};

}  // namespace configuration
}  // namespace sdk
OPENTELEMETRY_END_NAMESPACE
