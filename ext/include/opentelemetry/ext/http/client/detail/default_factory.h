// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <memory>

#include "opentelemetry/ext/http/client/http_client_factory.h"
#include "opentelemetry/ext/http/client/curl/http_client_factory_curl.h"

OPENTELEMETRY_BEGIN_NAMESPACE
namespace ext
{
namespace http
{
namespace client
{
namespace detail
{

std::shared_ptr<HttpClientFactory> OPENTELEMETRY_EXPORT GetDefaultHttpClientFactory();

}  // namespace detail
}  // namespace client
}  // namespace http
}  // namespace ext
OPENTELEMETRY_END_NAMESPACE
