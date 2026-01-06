# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

load("//bazel:otel_cc.bzl", "otel_cc_library")

package(default_visibility = ["//visibility:public"])

otel_cc_library(
    name = "resource_detectors",
    srcs = [
        "container_detector.cc",
        "container_detector_utils.cc",
        "env_entity_detector.cc",
        "process_detector.cc",
        "process_detector_utils.cc",
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
