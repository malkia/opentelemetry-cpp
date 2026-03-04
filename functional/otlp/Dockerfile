# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

FROM otel/opentelemetry-collector:0.147.0@sha256:b66294ff3a9eadc446ec4d0e78b6f4980c2a85b0ccc27f2cdc4641bd0fe401a7
COPY . .
CMD ["--config", "/otel-cpp/otel-config.yaml"]
EXPOSE 4317
EXPOSE 4318
