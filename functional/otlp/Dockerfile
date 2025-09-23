# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

FROM otel/opentelemetry-collector:0.136.0@sha256:98fd3b410ae8a939be9588f1580c4b7c3da6ebba49f5363df4259a827aabb779
COPY . .
CMD ["--config", "/otel-cpp/otel-config.yaml"]
EXPOSE 4317
EXPOSE 4318
