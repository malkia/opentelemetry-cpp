# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

FROM otel/opentelemetry-collector:0.135.0@sha256:6d260efde7406a1f7d731a5d9663cb6ce25fa634f3ef3ef4a69266aaae1680fd
COPY . .
CMD ["--config", "/otel-cpp/otel-config.yaml"]
EXPOSE 4317
EXPOSE 4318
