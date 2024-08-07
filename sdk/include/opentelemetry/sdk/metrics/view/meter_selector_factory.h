// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <memory>
#include <string>

#include "opentelemetry/version.h"
#include "opentelemetry/sdk/metrics/view/meter_selector.h"

OPENTELEMETRY_BEGIN_NAMESPACE
namespace sdk
{
namespace metrics
{

class OPENTELEMETRY_EXPORT_TYPE MeterSelectorFactory
{
public:
  static std::unique_ptr<MeterSelector> Create(const std::string &name,
                                               const std::string &version,
                                               const std::string &schema);
};

}  // namespace metrics
}  // namespace sdk
OPENTELEMETRY_END_NAMESPACE
