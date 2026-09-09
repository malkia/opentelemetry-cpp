# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

load("//bazel:otel_cc.bzl", "otel_cc_test_combo")

otel_cc_test_combo(
    name = "resource_test",
    srcs = [
        "resource_test.cc",
    ],
    tags = ["test"],
    deps = [
        "//api",
        "//sdk/src/resource",
        "//sdk/src/resource:percent_decode",
        "@googletest//:gtest_main",
    ],
)
