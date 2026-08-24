# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

load("//:dll_deps.bzl", "dll_deps")
load("//bazel:otel_cc.bzl", "otel_cc_test")

otel_cc_test(
    name = "resource_test",
    srcs = [
        "resource_test.cc",
    ],
    tags = ["test"],
    deps = dll_deps([
        "//api",
        "//sdk/src/resource",
        "//sdk/src/resource:percent_decode",
        "@googletest//:gtest_main",
    ]),
)
