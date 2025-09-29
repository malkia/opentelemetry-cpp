# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

load("//bazel:otel_cc.bzl", "otel_cc_library")

package(default_visibility = ["//visibility:public"])

otel_cc_library(
    name = "configuration",
    srcs = glob(["**/*.cc"]),
    deps = [
        "//api",
        "//sdk:headers",
        "//sdk/src/common:env_variables",
        "@rapidyaml",
    ],
)
