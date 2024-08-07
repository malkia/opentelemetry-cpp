// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <stddef.h>
#include <memory>

#include "opentelemetry/version.h"
#include "opentelemetry/exporters/memory/in_memory_span_data.h"
#include "opentelemetry/sdk/trace/exporter.h"

OPENTELEMETRY_BEGIN_NAMESPACE
namespace exporter
{
namespace memory
{

/**
 * Factory class for InMemorySpanExporter.
 */
class OPENTELEMETRY_EXPORT_TYPE InMemorySpanExporterFactory
{
public:
  /**
   * Create a InMemorySpanExporter with a default buffer size.
   * @param [out] data the InMemorySpanData the exporter will write to,
   *                   for the caller to inspect
   */
  static std::unique_ptr<opentelemetry::sdk::trace::SpanExporter> Create(
      std::shared_ptr<InMemorySpanData> &data);

  /**
   * Create a InMemorySpanExporter with a default buffer size.
   * @param [out] data the InMemorySpanData the exporter will write to,
   *                   for the caller to inspect
   * @param [in] buffer_size size of the underlying InMemorySpanData
   */
  static std::unique_ptr<opentelemetry::sdk::trace::SpanExporter> Create(
      std::shared_ptr<InMemorySpanData> &data,
      size_t buffer_size);
};

}  // namespace memory
}  // namespace exporter
OPENTELEMETRY_END_NAMESPACE
