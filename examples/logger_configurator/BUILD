# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

load("//:dll_deps.bzl", "dll_deps")
load("//bazel:otel_cc.bzl", "otel_cc_test")

otel_cc_test(
    name = "example_logger_configurator",
    srcs = [
        "main.cc",
    ],
    tags = [
        "ostream",
        "tested_example",
    ],
    deps = dll_deps([
        "//api",
        "//exporters/ostream:ostream_log_record_exporter",
        "//sdk/src/logs",
    ]),
)
