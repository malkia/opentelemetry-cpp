# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

load("//:dll_deps.bzl", "dll_deps")
load("//bazel:otel_cc.bzl", "otel_cc_library")

package(default_visibility = ["//visibility:public"])

otel_cc_library(
    name = "common_foo_library",
    srcs = [
        "foo_library.cc",
    ],
    hdrs = [
        "foo_library.h",
    ],
    # TODO(malkia): Find out why include_prefix / strip_include_prefix do not work here!
    includes = [".."],
    deps = dll_deps([
        "//api",
        "//sdk:headers",
    ]),
)
