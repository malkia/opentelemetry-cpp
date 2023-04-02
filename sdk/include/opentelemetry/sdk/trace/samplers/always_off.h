// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "opentelemetry/sdk/trace/sampler.h"

OPENTELEMETRY_BEGIN_NAMESPACE
namespace sdk
{
namespace trace
{
/**
 * The always off sampler always returns DROP, effectively disabling
 * tracing functionality.
 */
class OPENTELEMETRY_SDK_TRACE_EXPORT AlwaysOffSampler : public Sampler
{
public:
  /**
   * @return Returns DROP always
   */
  SamplingResult ShouldSample(
      const opentelemetry::trace::SpanContext &parent_context,
      opentelemetry::trace::TraceId /*trace_id*/,
      nostd::string_view /*name*/,
      opentelemetry::trace::SpanKind /*span_kind*/,
      const opentelemetry::common::KeyValueIterable & /*attributes*/,
      const opentelemetry::trace::SpanContextKeyValueIterable & /*links*/) noexcept override
  {
    if (!parent_context.IsValid())
    {
      return {Decision::DROP, nullptr, opentelemetry::trace::TraceState::GetDefault()};
    }
    else
    {
      return {Decision::DROP, nullptr, parent_context.trace_state()};
    }
  }

  /**
   * @return Description MUST be AlwaysOffSampler
   */
  nostd::string_view GetDescription() const noexcept override { return "AlwaysOffSampler"; }
};
}  // namespace trace
}  // namespace sdk
OPENTELEMETRY_END_NAMESPACE
