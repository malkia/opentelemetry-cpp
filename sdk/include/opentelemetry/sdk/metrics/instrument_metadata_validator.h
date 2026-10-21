// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "opentelemetry/version.h"
#include "opentelemetry/nostd/string_view.h"

OPENTELEMETRY_BEGIN_NAMESPACE
namespace sdk
{
namespace metrics
{
class OPENTELEMETRY_EXPORT_TYPE InstrumentMetaDataValidator
{
public:
  InstrumentMetaDataValidator();
  bool ValidateName(nostd::string_view name) const;
  bool ValidateUnit(nostd::string_view unit) const;
  bool ValidateDescription(nostd::string_view description) const;
};

}  // namespace metrics
}  // namespace sdk
OPENTELEMETRY_END_NAMESPACE
