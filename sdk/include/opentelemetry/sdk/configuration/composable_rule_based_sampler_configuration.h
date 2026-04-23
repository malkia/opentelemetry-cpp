// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <memory>
#include <vector>

#include "opentelemetry/version.h"
#include "opentelemetry/sdk/configuration/composable_rule_based_sampler_rule_configuration.h"
#include "opentelemetry/sdk/configuration/composable_sampler_configuration.h"
#include "opentelemetry/sdk/configuration/sampler_configuration_visitor.h"

OPENTELEMETRY_BEGIN_NAMESPACE
namespace sdk
{
namespace configuration
{

class OPENTELEMETRY_EXPORT_TYPE ComposableRuleBasedSamplerConfiguration : public ComposableSamplerConfiguration
{
public:
  ComposableRuleBasedSamplerConfiguration() = default;

  ComposableRuleBasedSamplerConfiguration(ComposableRuleBasedSamplerConfiguration&&) noexcept = default;
  ComposableRuleBasedSamplerConfiguration& operator=(ComposableRuleBasedSamplerConfiguration&&) noexcept = default;

  ComposableRuleBasedSamplerConfiguration(const ComposableRuleBasedSamplerConfiguration&) = delete;
  ComposableRuleBasedSamplerConfiguration& operator=(const ComposableRuleBasedSamplerConfiguration&) = delete;

  std::vector<std::unique_ptr<ComposableRuleBasedSamplerRuleConfiguration>> rules;
  void Accept(SamplerConfigurationVisitor *visitor) const override;
};

}  // namespace configuration
}  // namespace sdk
OPENTELEMETRY_END_NAMESPACE
