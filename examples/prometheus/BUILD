# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

load("//bazel:otel_cc.bzl", "otel_cc_binary_combo")

otel_cc_binary_combo(
    name = "prometheus_example",
    srcs = [
        "main.cc",
    ],
    linkopts = select({
        "//bazel:windows": [],
        "//conditions:default": ["-pthread"],
    }),
    tags = ["prometheus"],
    deps = [
        "//api",
        "//examples/common/metrics_foo_library:common_metrics_foo_library",
        "//exporters/prometheus:prometheus_exporter",
        "//sdk/src/metrics",
        # These are not exported in the "dll" version, hence they need to be linked in statically
        # In the non-dll version, these are just duplicate deps, and would be ignored
        "@prometheus-cpp//core",
        "@prometheus-cpp//pull",
    ],
)
