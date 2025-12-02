# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

FROM otel/opentelemetry-collector:0.141.0@sha256:2231b48a2ea0f18f50ae6adcda04474e71ff8b236a1195a398c3717c0ba692c5
COPY . .
CMD ["--config", "/otel-cpp/otel-config.yaml"]
EXPOSE 4317
EXPOSE 4318
