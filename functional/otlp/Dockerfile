# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

FROM otel/opentelemetry-collector:0.157.0@sha256:4019ce4d7e7791a1a255fffb2f407af66d5017cc65543469ba565c4f47f795b8
COPY . .
CMD ["--config", "/otel-cpp/otel-config.yaml"]
EXPOSE 4317
EXPOSE 4318
