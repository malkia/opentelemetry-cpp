# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

load("//:dll_deps.bzl", "dll_deps")
load("//bazel:otel_cc.bzl", "otel_cc_test")
load("//bazel:otel_cc_benchmark.bzl", "otel_cc_benchmark")

otel_cc_test(
    name = "baggage_test",
    srcs = [
        "baggage_test.cc",
    ],
    tags = [
        "api",
        "test",
    ],
    deps = dll_deps([
        "//api",
        "@googletest//:gtest_main",
    ]),
)

otel_cc_benchmark(
    name = "baggage_benchmark",
    srcs = ["baggage_benchmark.cc"],
    tags = [
        "api",
        "benchmark",
        "test",
    ],
    deps = dll_deps(["//api"]),
)
