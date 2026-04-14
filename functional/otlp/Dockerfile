# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

FROM otel/opentelemetry-collector:0.150.1@sha256:618f7867e49fdb173d9b46d535b01f82254b0b14beac6ab1f6f2eb8cf62c5d42
COPY . .
CMD ["--config", "/otel-cpp/otel-config.yaml"]
EXPOSE 4317
EXPOSE 4318
