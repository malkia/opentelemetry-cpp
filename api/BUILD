# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

load("//bazel:otel_cc.bzl", "otel_cc_library")

package(default_visibility = ["//visibility:public"])

otel_cc_library(
    name = "api",
    defines = select({
        "//:with_dll_enabled": ["OPENTELEMETRY_DLL=-1"],
        "//conditions:default": ["OPENTELEMETRY_DLL=0"],
    }),
    tags = ["api"],
    deps = [
        "headers",
        "@abseil-cpp//absl/base",
        "@abseil-cpp//absl/strings",
        "@abseil-cpp//absl/types:variant",
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
