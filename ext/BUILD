# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

load("//bazel:otel_cc.bzl", "otel_cc_library")

package(default_visibility = ["//visibility:public"])

filegroup(
    name = "header_files",
    srcs = glob(["include/**/*.h"]),
)

otel_cc_library(
    name = "headers",
    hdrs = [":header_files"],
    linkopts = select({
        # socket_tools.h calls Winsock; declare it on the interface so consumers link it too.
        "//bazel:windows": ["-DEFAULTLIB:Ws2_32.lib"],
        "//conditions:default": [],
    }),
    strip_include_prefix = "include",
)
