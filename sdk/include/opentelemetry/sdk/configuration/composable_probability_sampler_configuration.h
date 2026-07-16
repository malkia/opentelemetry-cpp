// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "opentelemetry/version.h"
#include "opentelemetry/sdk/configuration/composable_sampler_configuration.h"

OPENTELEMETRY_BEGIN_NAMESPACE
namespace sdk
{
namespace configuration
{

class OPENTELEMETRY_EXPORT_TYPE ComposableProbabilitySamplerConfiguration : public ComposableSamplerConfiguration
{
public:
  static constexpr double kDefaultRatio = 1.0;

  ComposableProbabilitySamplerConfiguration() = default;
  double ratio{kDefaultRatio};
  void Accept(SamplerConfigurationVisitor *visitor) const override;
};

}  // namespace configuration
}  // namespace sdk
OPENTELEMETRY_END_NAMESPACE
