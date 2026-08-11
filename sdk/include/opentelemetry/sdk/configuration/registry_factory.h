// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <memory>

#include "opentelemetry/version.h"
#include "opentelemetry/sdk/configuration/registry.h"

OPENTELEMETRY_BEGIN_NAMESPACE
namespace sdk
{
namespace configuration
{

class OPENTELEMETRY_EXPORT_TYPE RegistryFactory
{
public:
  // Returns a Registry pre-populated with all default signal builders.
  static std::shared_ptr<Registry> Create();
};

}  // namespace configuration
}  // namespace sdk
OPENTELEMETRY_END_NAMESPACE
