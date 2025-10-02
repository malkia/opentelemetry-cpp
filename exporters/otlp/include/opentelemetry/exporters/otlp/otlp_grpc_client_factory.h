// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <memory>

// IWYU pragma: no_include "opentelemetry/exporters/otlp/otlp_grpc_client.h"
#include "opentelemetry/version.h"
#include "opentelemetry/exporters/otlp/otlp_grpc_client_options.h"

OPENTELEMETRY_BEGIN_NAMESPACE
namespace exporter
{
namespace otlp
{

class OtlpGrpcClient;                // IWYU pragma: keep
class OtlpGrpcClientReferenceGuard;  // IWYU pragma: keep

/**
 * Factory class for OtlpGrpcClient.
 */
class OPENTELEMETRY_EXPORT_TYPE OtlpGrpcClientFactory
{
public:
  /**
   * Create an OtlpGrpcClient using all default options.
   */
  static std::shared_ptr<OtlpGrpcClient> Create(const OtlpGrpcClientOptions &options);

  static std::shared_ptr<OtlpGrpcClientReferenceGuard> CreateReferenceGuard();
};

}  // namespace otlp
}  // namespace exporter
OPENTELEMETRY_END_NAMESPACE
