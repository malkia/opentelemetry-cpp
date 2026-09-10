// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <string>

#include "opentelemetry/version.h"
#include "opentelemetry/exporters/otlp/otlp_environment.h"  // For OtlpHeaders
#include "opentelemetry/exporters/otlp/otlp_preferred_temporality.h"
#include "opentelemetry/sdk/configuration/headers_configuration.h"
#include "opentelemetry/sdk/configuration/temporality_preference.h"

OPENTELEMETRY_BEGIN_NAMESPACE
namespace exporter
{
namespace otlp
{

class OPENTELEMETRY_EXPORT_TYPE OtlpBuilderUtils
{
public:
  static OtlpHeaders ConvertHeadersConfigurationModel(
      const opentelemetry::sdk::configuration::HeadersConfiguration *model,
      const std::string &headers_list);

  static PreferredAggregationTemporality ConvertTemporalityPreference(
      opentelemetry::sdk::configuration::TemporalityPreference model);
};

}  // namespace otlp
}  // namespace exporter
OPENTELEMETRY_END_NAMESPACE
