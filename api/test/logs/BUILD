# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

load("//:dll_deps.bzl", "dll_deps")
load("//bazel:otel_cc.bzl", "otel_cc_test")

otel_cc_test(
    name = "provider_test",
    srcs = [
        "provider_test.cc",
    ],
    tags = [
        "api",
        "logs",
        "test",
    ],
    deps = dll_deps([
        "//api",
        "@googletest//:gtest_main",
    ]),
)

otel_cc_test(
    name = "logger_test",
    srcs = [
        "logger_test.cc",
    ],
    tags = [
        "api",
        "logs",
        "test",
    ],
    deps = dll_deps([
        "//api",
        "@googletest//:gtest_main",
    ]),
)
