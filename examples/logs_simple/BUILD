# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

load("//:dll_deps.bzl", "dll_deps")
load("//bazel:otel_cc.bzl", "otel_cc_binary")

otel_cc_binary(
    name = "example_logs_simple",
    srcs = [
        "main.cc",
    ],
    tags = [
        "examples",
        "ostream",
    ],
    deps = dll_deps([
        "//api",
        "//examples/common/logs_foo_library:common_logs_foo_library",
        "//exporters/ostream:ostream_log_record_exporter",
        "//exporters/ostream:ostream_span_exporter",
    ]),
)
