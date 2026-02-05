# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

FROM otel/opentelemetry-collector:0.145.0@sha256:8cad95dd3fe0304fbc5652373cc392be4ac915c4c210d2c425d3f1a1f7c3c3ca
COPY . .
CMD ["--config", "/otel-cpp/otel-config.yaml"]
EXPOSE 4317
EXPOSE 4318
