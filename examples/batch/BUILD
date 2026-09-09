# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

load("//bazel:otel_cc.bzl", "otel_cc_test_combo")

otel_cc_test_combo(
    name = "example_simple",
    size = "medium",
    srcs = [
        "main.cc",
    ],
    linkopts = select({
        "//bazel:windows": [],
        "//conditions:default": ["-pthread"],
    }),
    tags = [
        "ostream",
        "tested_example",
    ],
    deps = [
        "//api",
        "//exporters/ostream:ostream_span_exporter",
        "//sdk/src/trace",
    ],
)
