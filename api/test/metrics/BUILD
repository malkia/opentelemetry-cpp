# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

load("//bazel:otel_cc.bzl", "otel_cc_test_combo")

otel_cc_test_combo(
    name = "noop_sync_instrument_test",
    srcs = [
        "noop_sync_instrument_test.cc",
    ],
    tags = [
        "metrics",
        "test",
    ],
    deps = [
        "//api",
        "@googletest//:gtest_main",
    ],
)

otel_cc_test_combo(
    name = "meter_provider_test",
    srcs = [
        "meter_provider_test.cc",
    ],
    tags = [
        "metrics",
        "test",
    ],
    deps = [
        "//api",
        "@googletest//:gtest_main",
    ],
)
