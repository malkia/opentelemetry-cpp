# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

FROM otel/opentelemetry-collector:0.142.0@sha256:27e249dac470545ed31beefc86f9e1dc260a21e85aaa256903a2b6e0393a2d91
COPY . .
CMD ["--config", "/otel-cpp/otel-config.yaml"]
EXPOSE 4317
EXPOSE 4318
