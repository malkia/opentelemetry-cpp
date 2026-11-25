# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

FROM otel/opentelemetry-collector:0.166.0@sha256:98e7207b64b223de07e04b886ec04a72a9eedb1ef420131fba7b9f0390a3476a
COPY . .
CMD ["--config", "/otel-cpp/otel-config.yaml"]
EXPOSE 4317
EXPOSE 4318
