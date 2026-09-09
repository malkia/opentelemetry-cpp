# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

load("//:dll_deps.bzl", "dll_deps")
load("//bazel:otel_cc.bzl", "otel_cc_test_combo")

otel_cc_test_combo(
    name = "example_explicit_parent",
    srcs = [
        "main.cc",
    ],
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
