# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

load("//bazel:otel_cc.bzl", "otel_cc_test_combo")

otel_cc_test_combo(
    name = "provider_test",
    srcs = [
        "provider_test.cc",
    ],
    tags = [
        "api",
        "logs",
        "test",
    ],
    deps = [
        "//api",
        "@googletest//:gtest_main",
    ],
)

otel_cc_test_combo(
    name = "logger_test",
    srcs = [
        "logger_test.cc",
    ],
    tags = [
        "api",
        "logs",
        "test",
    ],
    deps = [
        "//api",
        "@googletest//:gtest_main",
    ],
)
