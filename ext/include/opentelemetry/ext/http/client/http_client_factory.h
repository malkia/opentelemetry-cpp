// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "opentelemetry/version.h"
#include "opentelemetry/ext/http/client/http_client.h"
#include "opentelemetry/sdk/common/thread_instrumentation.h"

OPENTELEMETRY_BEGIN_NAMESPACE
namespace ext
{
namespace http
{
namespace client
{
class OPENTELEMETRY_EXPORT_TYPE HttpClientFactory
{
public:
  static std::shared_ptr<HttpClientSync> CreateSync();

  static std::shared_ptr<HttpClient> Create();
  static std::shared_ptr<HttpClient> Create(
      const std::shared_ptr<sdk::common::ThreadInstrumentation> &thread_instrumentation);
};
}  // namespace client
}  // namespace http
}  // namespace ext
OPENTELEMETRY_END_NAMESPACE
