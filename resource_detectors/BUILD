# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

load("//bazel:otel_cc.bzl", "otel_cc_library")

package(default_visibility = ["//visibility:public"])

otel_cc_library(
    name = "resource_detectors",
    srcs = [
        "src/container_detector.cc",
        "src/container_detector_utils.cc",
        "src/env_entity_detector.cc",
        "src/process_detector.cc",
        "src/process_detector_utils.cc",
    ],
    copts = ["-fexceptions"],
    linkopts = select({
        "//bazel:windows": [
            "-DEFAULTLIB:shell32.lib",
        ],
        "//conditions:default": [],
    }),
    deps = [
        "//api",
        "//resource_detectors:headers",
        "//sdk:headers",
        "//sdk/src/resource",
    ],
)

filegroup(
    name = "header_files",
    srcs = glob(["include/**/*.h"]),
)

otel_cc_library(
    name = "headers",
    hdrs = [":header_files"],
    strip_include_prefix = "include",
)
