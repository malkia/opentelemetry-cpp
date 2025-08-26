# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

FROM otel/opentelemetry-collector:0.133.0@sha256:01268c1bf7f561f1df20a0ea2875db8cb388508f1845a96c8e9ff83efe970a80
COPY . .
CMD ["--config", "/otel-cpp/otel-config.yaml"]
EXPOSE 4317
EXPOSE 4318
