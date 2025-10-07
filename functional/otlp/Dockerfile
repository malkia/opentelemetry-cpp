# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

FROM otel/opentelemetry-collector:0.137.0@sha256:089a8b3c81d328a190f6f0740b30c15b0c7f1f2cfeadeb810355574d5158b31c
COPY . .
CMD ["--config", "/otel-cpp/otel-config.yaml"]
EXPOSE 4317
EXPOSE 4318
