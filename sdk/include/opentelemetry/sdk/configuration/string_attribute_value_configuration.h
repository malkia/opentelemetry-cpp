// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <string>

#include "opentelemetry/version.h"
#include "opentelemetry/sdk/configuration/attribute_value_configuration.h"
#include "opentelemetry/sdk/configuration/attribute_value_configuration_visitor.h"

OPENTELEMETRY_BEGIN_NAMESPACE
namespace sdk
{
namespace configuration
{

// YAML-SCHEMA: schema/resource.json
// YAML-NODE: AttributeNameValue
class StringAttributeValueConfiguration : public AttributeValueConfiguration
{
public:
  void Accept(AttributeValueConfigurationVisitor *visitor) const override
  {
    visitor->VisitString(this);
  }

  std::string value;
};

}  // namespace configuration
}  // namespace sdk
OPENTELEMETRY_END_NAMESPACE
