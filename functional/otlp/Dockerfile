# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

FROM otel/opentelemetry-collector:0.139.0@sha256:8ac5df2a931e9264667b236d65bf7591fa4ba633a7a634e6caa2f0a4fc549c07
COPY . .
CMD ["--config", "/otel-cpp/otel-config.yaml"]
EXPOSE 4317
EXPOSE 4318
