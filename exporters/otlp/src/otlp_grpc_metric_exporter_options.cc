// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#include "opentelemetry/version.h"
#include "opentelemetry/exporters/otlp/otlp_grpc_metric_exporter_options.h"

OPENTELEMETRY_BEGIN_NAMESPACE
namespace exporter
{
namespace otlp
{

OtlpGrpcMetricExporterOptions::OtlpGrpcMetricExporterOptions()
    : aggregation_temporality(PreferredAggregationTemporality::kCumulative)
{
  endpoint                    = GetOtlpDefaultGrpcMetricsEndpoint();
  use_ssl_credentials         = !GetOtlpDefaultGrpcMetricsIsInsecure(); /* negation intended. */
  ssl_credentials_cacert_path = GetOtlpDefaultMetricsSslCertificatePath();
  ssl_credentials_cacert_as_string = GetOtlpDefaultMetricsSslCertificateString();

#ifdef ENABLE_OTLP_GRPC_SSL_MTLS_PREVIEW
  ssl_client_key_path    = GetOtlpDefaultMetricsSslClientKeyPath();
  ssl_client_key_string  = GetOtlpDefaultMetricsSslClientKeyString();
  ssl_client_cert_path   = GetOtlpDefaultMetricsSslClientCertificatePath();
  ssl_client_cert_string = GetOtlpDefaultMetricsSslClientCertificateString();
#endif

  timeout    = GetOtlpDefaultMetricsTimeout();
  metadata   = GetOtlpDefaultMetricsHeaders();
  user_agent = GetOtlpDefaultUserAgent();

  max_threads = 0;

  compression = GetOtlpDefaultMetricsCompression();
#ifdef ENABLE_ASYNC_EXPORT
  max_concurrent_requests = 64;
#endif

  retry_policy_max_attempts       = GetOtlpDefaultMetricsRetryMaxAttempts();
  retry_policy_initial_backoff    = GetOtlpDefaultMetricsRetryInitialBackoff();
  retry_policy_max_backoff        = GetOtlpDefaultMetricsRetryMaxBackoff();
  retry_policy_backoff_multiplier = GetOtlpDefaultMetricsRetryBackoffMultiplier();
}

OtlpGrpcMetricExporterOptions::~OtlpGrpcMetricExporterOptions() {}

}  // namespace otlp
}  // namespace exporter
OPENTELEMETRY_END_NAMESPACE
