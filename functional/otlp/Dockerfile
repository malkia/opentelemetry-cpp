# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

FROM otel/opentelemetry-collector:0.141.0@sha256:b54b114431b2aa031c28f590507b4a17daabd59a4d797eb7fddd7988b4d3e3ea
COPY . .
CMD ["--config", "/otel-cpp/otel-config.yaml"]
EXPOSE 4317
EXPOSE 4318
