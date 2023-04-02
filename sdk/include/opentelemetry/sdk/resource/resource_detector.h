// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "opentelemetry/nostd/unique_ptr.h"
#include "opentelemetry/version.h"

OPENTELEMETRY_BEGIN_NAMESPACE
namespace sdk
{
namespace resource
{

class OPENTELEMETRY_SDK_RESOURCE_EXPORT Resource;

/**
 * Interface for a Resource Detector
 */
class OPENTELEMETRY_SDK_RESOURCE_EXPORT ResourceDetector
{
public:
  ResourceDetector()          = default;
  virtual ~ResourceDetector() = default;
  virtual Resource Detect()   = 0;
};

/**
 * OTelResourceDetector to detect the presence of and create a Resource
 * from the OTEL_RESOURCE_ATTRIBUTES environment variable.
 */
class OPENTELEMETRY_SDK_RESOURCE_EXPORT OTELResourceDetector : public ResourceDetector
{
public:
  Resource Detect() noexcept override;
};

}  // namespace resource
}  // namespace sdk
OPENTELEMETRY_END_NAMESPACE
