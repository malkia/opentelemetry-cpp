// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <memory>

#include "opentelemetry/version.h"
#include "opentelemetry/sdk/configuration/console_push_metric_exporter_configuration.h"

OPENTELEMETRY_BEGIN_NAMESPACE
namespace sdk
{
namespace metrics
{
class PushMetricExporter;
}  // namespace metrics

namespace configuration
{

class ConsolePushMetricExporterBuilder
{
public:
  ConsolePushMetricExporterBuilder()                                               = default;
  ConsolePushMetricExporterBuilder(ConsolePushMetricExporterBuilder &&)            = default;
  ConsolePushMetricExporterBuilder(const ConsolePushMetricExporterBuilder &)       = default;
  ConsolePushMetricExporterBuilder &operator=(ConsolePushMetricExporterBuilder &&) = default;
  ConsolePushMetricExporterBuilder &operator=(const ConsolePushMetricExporterBuilder &other) =
      default;
  virtual ~ConsolePushMetricExporterBuilder() = default;

  virtual std::unique_ptr<opentelemetry::sdk::metrics::PushMetricExporter> Build(
      const opentelemetry::sdk::configuration::ConsolePushMetricExporterConfiguration *model)
      const = 0;
};

}  // namespace configuration
}  // namespace sdk
OPENTELEMETRY_END_NAMESPACE
