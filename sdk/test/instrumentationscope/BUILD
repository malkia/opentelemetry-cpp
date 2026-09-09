# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

load("//bazel:otel_cc.bzl", "otel_cc_test_combo")

otel_cc_test_combo(
    name = "instrumentationscope_test",
    srcs = [
        "instrumentationscope_test.cc",
    ],
    tags = ["test"],
    deps = [
        "//api",
        "//sdk:headers",
        "//sdk/src/common:env_variables",
        "//sdk/src/instrumentationscope",
        "@googletest//:gtest_main",
    ],
)
