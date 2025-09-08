# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

load("//:dll_deps.bzl", "dll_deps")
load("//bazel:otel_cc.bzl", "otel_cc_test")

otel_cc_test(
    name = "yaml_test",
    srcs = [
        "yaml_test.cc",
    ],
    tags = ["test"],
    deps = dll_deps([
        "//api",
        "//sdk/src/resource",
        "@googletest//:gtest_main",
    ]),
)
