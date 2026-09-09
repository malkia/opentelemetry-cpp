# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

load("//bazel:otel_cc.bzl", "otel_cc_test_combo")

otel_cc_test_combo(
    name = "example_logger_configurator",
    srcs = [
        "main.cc",
    ],
    tags = [
        "ostream",
        "tested_example",
    ],
    deps = [ 
        "//api",
        "//exporters/ostream:ostream_log_record_exporter",
        "//sdk/src/logs",
    ],
)
