// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <cstdint>
#include <memory>

#include "opentelemetry/version.h"
#include "opentelemetry/nostd/string_view.h"
#include "opentelemetry/sdk/metrics/view/predicate.h"

OPENTELEMETRY_BEGIN_NAMESPACE
namespace sdk
{
namespace metrics
{

enum class PredicateType : uint8_t
{
  kPattern,
  kExact,
  kWildcard
};

class OPENTELEMETRY_EXPORT_TYPE PredicateFactory
{
public:
  static std::unique_ptr<Predicate> GetPredicate(opentelemetry::nostd::string_view pattern,
                                                 PredicateType type);
};
}  // namespace metrics
}  // namespace sdk
OPENTELEMETRY_END_NAMESPACE
