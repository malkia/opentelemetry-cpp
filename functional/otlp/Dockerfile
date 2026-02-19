# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

FROM otel/opentelemetry-collector:0.146.1@sha256:23f75833cfcf0ebdde9b2e1ba41616b9092294af6947f2feea1b4ebc393030f5
COPY . .
CMD ["--config", "/otel-cpp/otel-config.yaml"]
EXPOSE 4317
EXPOSE 4318
