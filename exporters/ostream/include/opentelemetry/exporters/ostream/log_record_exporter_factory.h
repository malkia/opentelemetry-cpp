// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <iostream>
#include <memory>

#include "opentelemetry/version.h"
#include "opentelemetry/sdk/logs/exporter.h"

OPENTELEMETRY_BEGIN_NAMESPACE
namespace exporter
{
namespace logs
{

/**
 * Factory class for OStreamLogRecordExporter.
 */
class OPENTELEMETRY_EXPORT_TYPE OStreamLogRecordExporterFactory
{
public:
  /**
   * Creates an OStreamLogRecordExporter writing to the default location.
   */
  static std::unique_ptr<opentelemetry::sdk::logs::LogRecordExporter> Create();

  /**
   * Creates an OStreamLogRecordExporter writing to the given location.
   */
  static std::unique_ptr<opentelemetry::sdk::logs::LogRecordExporter> Create(std::ostream &sout);
};

}  // namespace logs
}  // namespace exporter
OPENTELEMETRY_END_NAMESPACE
