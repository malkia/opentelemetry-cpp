# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

load("//bazel:otel_cc_benchmark.bzl", "otel_cc_benchmark")
load("//:dll_deps.bzl", "dll_deps")
load("//bazel:otel_cc.bzl", "otel_cc_binary", "otel_cc_import", "otel_cc_library", "otel_cc_shared_library", "otel_cc_test")

otel_cc_test(
    name = "hex_test",
    srcs = [
        "hex_test.cc",
    ],
    tags = [
        "api",
        "test",
        "trace",
    ],
    deps = dll_deps([
        "//api",
        "@googletest//:gtest_main",
    ]),
)
