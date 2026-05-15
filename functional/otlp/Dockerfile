# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

FROM otel/opentelemetry-collector:0.152.0@sha256:f358f8028c6eb44f765444de1c8899b4f97d7ba54be5264a8753f2c182bc5757
COPY . .
CMD ["--config", "/otel-cpp/otel-config.yaml"]
EXPOSE 4317
EXPOSE 4318
