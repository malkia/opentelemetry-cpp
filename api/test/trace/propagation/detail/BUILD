# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

load("//:dll_deps.bzl", "dll_deps")
load("//bazel:otel_cc.bzl", "otel_cc_test_combo")

otel_cc_test_combo(
    name = "hex_test",
    srcs = [
        "hex_test.cc",
    ],
    tags = [
        "api",
        "test",
        "trace",
    ],
    deps = [
        "//api",
        "@googletest//:gtest_main",
    ],
)

otel_cc_test_combo(
    name = "string_test",
    srcs = [
        "string_test.cc",
    ],
    tags = [
        "api",
        "test",
        "trace",
    ],
    deps = [
        "//api",
        "@googletest//:gtest_main",
    ],
)
