# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

FROM otel/opentelemetry-collector:0.154.0@sha256:ea527f0f9a220c7b595863a658c262f31d08c07e034a16b502bfb2206aa987ff
COPY . .
CMD ["--config", "/otel-cpp/otel-config.yaml"]
EXPOSE 4317
EXPOSE 4318
