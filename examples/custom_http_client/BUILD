# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

load("//:dll_deps.bzl", "dll_deps")
load("//bazel:otel_cc.bzl", "otel_cc_library", "otel_cc_test")

otel_cc_library(
    name = "custom_http_client_stub",
    srcs = [
        "custom_http_client.cc",
    ],
    hdrs = [
        "custom_http_client.h",
    ],
    deps = [
        "//api",
        "//ext:headers",
        "//sdk:headers",
    ],
)

otel_cc_test(
    name = "example_custom_http_client",
    srcs = [
        "main.cc",
    ],
    tags = [
        "otlp",
        "otlp_http",
        "tested_example",
    ],
    deps = dll_deps([
        ":custom_http_client_stub",
        "//api",
        "//exporters/otlp:otlp_http_exporter",
        "//sdk/src/metrics",
        "//sdk/src/trace",
    ]),
)
