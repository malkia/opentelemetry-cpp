// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <memory>

#include "opentelemetry/version.h"
#include "opentelemetry/sdk/configuration/service_resource_detector_builder.h"
#include "opentelemetry/sdk/configuration/service_resource_detector_configuration.h"
#include "opentelemetry/sdk/resource/resource_detector.h"

OPENTELEMETRY_BEGIN_NAMESPACE
namespace sdk
{
namespace configuration
{
class Registry;
}  // namespace configuration
}  // namespace sdk

namespace resource_detector
{

class OPENTELEMETRY_EXPORT_TYPE ServiceDetectorBuilder
    : public opentelemetry::sdk::configuration::ServiceResourceDetectorBuilder
{
public:
  static void Register(opentelemetry::sdk::configuration::Registry *registry);

  std::unique_ptr<opentelemetry::sdk::resource::ResourceDetector> Build(
      const opentelemetry::sdk::configuration::ServiceResourceDetectorConfiguration *model)
      const override;
};

}  // namespace resource_detector
OPENTELEMETRY_END_NAMESPACE
