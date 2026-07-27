# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

load("//:dll_deps.bzl", "dll_deps")
load("//bazel:otel_cc.bzl", "otel_cc_test")

otel_cc_test(
    name = "metrics_ostream_example",
    size = "medium",
    srcs = [
        "metrics_ostream.cc",
    ],
    linkopts = select({
        "//bazel:windows": [],
        "//conditions:default": ["-pthread"],
    }),
    tags = [
        "ostream",
        "tested_example",
    ],
    deps = dll_deps([
        "//api",
        "//examples/common/metrics_foo_library:common_metrics_foo_library",
        "//exporters/ostream:ostream_metric_exporter",
        "//sdk/src/metrics",
    ]),
)
