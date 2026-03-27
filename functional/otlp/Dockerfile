# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

FROM otel/opentelemetry-collector:0.148.0@sha256:1c7c8745b2f64fe1c4e4cd47afa77178e8efa22ecb756e788d7e0b74a316d88c
COPY . .
CMD ["--config", "/otel-cpp/otel-config.yaml"]
EXPOSE 4317
EXPOSE 4318
