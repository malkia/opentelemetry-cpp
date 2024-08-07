// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "opentelemetry/version.h"
#include "opentelemetry/sdk/trace/id_generator.h"
#include "opentelemetry/trace/span_id.h"
#include "opentelemetry/trace/trace_id.h"

OPENTELEMETRY_BEGIN_NAMESPACE
namespace sdk
{
namespace trace
{

class OPENTELEMETRY_EXPORT_TYPE RandomIdGenerator : public IdGenerator
{
public:
  RandomIdGenerator() : IdGenerator(true) {}

  opentelemetry::trace::SpanId GenerateSpanId() noexcept override;

  opentelemetry::trace::TraceId GenerateTraceId() noexcept override;
};

}  // namespace trace
}  // namespace sdk
OPENTELEMETRY_END_NAMESPACE
