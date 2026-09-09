# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

load("//bazel:otel_cc.bzl", "otel_cc_test_combo")

otel_cc_test_combo(
    name = "context_test",
    srcs = [
        "context_test.cc",
    ],
    tags = [
        "api",
        "test",
    ],
    deps = [
        "//api",
        "@googletest//:gtest_main",
    ],
)

otel_cc_test_combo(
    name = "runtime_context_test",
    srcs = [
        "runtime_context_test.cc",
    ],
    tags = [
        "api",
        "test",
    ],
    deps = [
        "//api",
        "@googletest//:gtest_main",
    ],
)
