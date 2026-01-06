# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

load("//:dll_deps.bzl", "dll_deps")
load("//bazel:otel_cc.bzl", "otel_cc_test")

otel_cc_test(
    name = "resource_detector_test",
    srcs = [
        "container_detector_test.cc",
        "process_detector_test.cc",
    ],
    linkopts = select({
        "//bazel:windows": [
            "-DEFAULTLIB:shell32.lib",
        ],
        "//conditions:default": [],
    }),
    tags = ["test"],
    deps = dll_deps([
        "//api",
        "//resource_detectors",
        "@googletest//:gtest_main",
    ]),
)
