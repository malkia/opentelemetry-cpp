// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "opentelemetry/version.h"
#include "opentelemetry/sdk/resource/resource.h"
#include "opentelemetry/sdk/resource/resource_detector.h"

OPENTELEMETRY_BEGIN_NAMESPACE
namespace resource_detector
{

/**
 * EnvEntityDetector detects entities defined in the OTEL_ENTITIES environment
 * variable as specified in the Entity Propagation spec:
 * https://opentelemetry.io/docs/specs/otel/entities/entity-propagation/
 */
class OPENTELEMETRY_EXPORT_TYPE EnvEntityDetector : public opentelemetry::sdk::resource::ResourceDetector
{
public:
  opentelemetry::sdk::resource::Resource Detect() noexcept override;
};

}  // namespace resource_detector
OPENTELEMETRY_END_NAMESPACE
