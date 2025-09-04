# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

FROM otel/opentelemetry-collector:0.134.1@sha256:c8e0fde6d4d8dd17da0d2a6a3c882a894718ad5cde64aa516dc46ab6385fe42b
COPY . .
CMD ["--config", "/otel-cpp/otel-config.yaml"]
EXPOSE 4317
EXPOSE 4318
