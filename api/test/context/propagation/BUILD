# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

load("//bazel:otel_cc.bzl", "otel_cc_test_combo")

otel_cc_test_combo(
    name = "composite_propagator_test",
    srcs = [
        "composite_propagator_test.cc",
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
    name = "global_propagator_test",
    srcs = [
        "global_propagator_test.cc",
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
