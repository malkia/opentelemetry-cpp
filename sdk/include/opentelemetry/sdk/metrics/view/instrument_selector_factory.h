// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <memory>
#include <string>

#include "opentelemetry/version.h"
#include "opentelemetry/sdk/metrics/instruments.h"
#include "opentelemetry/sdk/metrics/view/instrument_selector.h"

OPENTELEMETRY_BEGIN_NAMESPACE
namespace sdk
{
namespace metrics
{

class OPENTELEMETRY_EXPORT_TYPE InstrumentSelectorFactory
{
public:
  static std::unique_ptr<InstrumentSelector> Create(
      opentelemetry::sdk::metrics::InstrumentType instrument_type,
      const std::string &name,
      const std::string &unit);
};

}  // namespace metrics
}  // namespace sdk
OPENTELEMETRY_END_NAMESPACE
