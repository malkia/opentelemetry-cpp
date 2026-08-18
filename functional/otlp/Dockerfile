# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

FROM otel/opentelemetry-collector:0.159.0@sha256:7725a7a10c87d8853208bdd4bb3439ad3c0d7b32b4292b9300ac07c8daba14a2
COPY . .
CMD ["--config", "/otel-cpp/otel-config.yaml"]
EXPOSE 4317
EXPOSE 4318
