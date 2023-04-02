// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <memory>

#include "opentelemetry/sdk/trace/sampler.h"

OPENTELEMETRY_BEGIN_NAMESPACE
namespace sdk
{
namespace trace
{

/**
 * Factory class for AlwaysOnSampler.
 */
class OPENTELEMETRY_SDK_TRACE_EXPORT AlwaysOnSamplerFactory
{
public:
  /**
   * Create an AlwaysOnSampler.
   */
  static std::unique_ptr<Sampler> Create();
};

}  // namespace trace
}  // namespace sdk
OPENTELEMETRY_END_NAMESPACE
