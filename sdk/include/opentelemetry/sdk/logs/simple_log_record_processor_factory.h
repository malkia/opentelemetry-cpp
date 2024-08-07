// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <memory>

#include "opentelemetry/version.h"
#include "opentelemetry/sdk/logs/processor.h"

OPENTELEMETRY_BEGIN_NAMESPACE
namespace sdk
{
namespace logs
{
class LogRecordExporter;

/**
 * Factory class for SimpleLogRecordProcessor.
 */
class OPENTELEMETRY_EXPORT_TYPE SimpleLogRecordProcessorFactory
{
public:
  /**
   * Create a SimpleLogRecordProcessor.
   */
  static std::unique_ptr<LogRecordProcessor> Create(std::unique_ptr<LogRecordExporter> &&exporter);
};

}  // namespace logs
}  // namespace sdk
OPENTELEMETRY_END_NAMESPACE
