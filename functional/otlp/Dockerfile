# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

FROM otel/opentelemetry-collector:0.152.1@sha256:c5cde41675a68e392322140d25fa232b4585e4e7fdc5f8c39d61d968bc13dae6
COPY . .
CMD ["--config", "/otel-cpp/otel-config.yaml"]
EXPOSE 4317
EXPOSE 4318
