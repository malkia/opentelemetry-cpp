# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

load("//:dll_deps.bzl", "dll_deps")
load("//bazel:otel_cc.bzl", "otel_cc_test")

otel_cc_test(
    name = "example_simple",
    srcs = [
        "main.cc",
    ],
    tags = [
        "examples",
        "ostream",
        "tested_example",
    ],
    deps = dll_deps([
        "//api",
        "//examples/common/foo_library:common_foo_library",
        "//exporters/ostream:ostream_span_exporter",
    ]),
)
