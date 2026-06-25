# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

FROM otel/opentelemetry-collector:0.155.0@sha256:140cdb56eeea12ebc33bb4f7109fd4eef90391933f8d85b33384fcfe1cf040c4
COPY . .
CMD ["--config", "/otel-cpp/otel-config.yaml"]
EXPOSE 4317
EXPOSE 4318
