// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <memory>

#include "opentelemetry/version.h"
#include "opentelemetry/ext/http/client/http_client_factory.h"

OPENTELEMETRY_BEGIN_NAMESPACE
namespace ext
{
namespace http
{
namespace client
{
namespace curl
{

class OPENTELEMETRY_EXPORT_TYPE HttpCurlClientFactory : public HttpClientFactory
{
public:
  std::shared_ptr<opentelemetry::ext::http::client::HttpClientSync> CreateSync() override;

  std::shared_ptr<opentelemetry::ext::http::client::HttpClient> Create() override;
  std::shared_ptr<opentelemetry::ext::http::client::HttpClient> Create(
      const std::shared_ptr<sdk::common::ThreadInstrumentation> &thread_instrumentation) override;
};

}  // namespace curl
}  // namespace client
}  // namespace http
}  // namespace ext
OPENTELEMETRY_END_NAMESPACE
