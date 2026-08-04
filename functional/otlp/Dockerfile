# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

FROM otel/opentelemetry-collector:0.158.0@sha256:5b97e6e3550ec6e48a71dba6f6304d349a293af8df4ee1f51da67be94fce2ecd
COPY . .
CMD ["--config", "/otel-cpp/otel-config.yaml"]
EXPOSE 4317
EXPOSE 4318
