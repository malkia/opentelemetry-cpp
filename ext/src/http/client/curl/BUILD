# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

load("//bazel:otel_cc.bzl", "otel_cc_library")

package(default_visibility = ["//visibility:public"])

otel_cc_library(
    name = "http_client_curl",
    srcs = [
        "http_client_curl.cc",
        "http_client_factory_curl.cc",
        "http_operation_curl.cc",
    ],
    include_prefix = "src/http/client/curl",
    linkopts = select({
        "//bazel:windows": [
            "-DEFAULTLIB:advapi32.lib",
            "-DEFAULTLIB:crypt32.lib",
            "-DEFAULTLIB:Normaliz.lib",
            "-DEFAULTLIB:Ws2_32.lib",
        ],
        "//conditions:default": [],
    }),
    local_defines = [
        "ENABLE_CURL_LOGGING",
    ],
    deps = [
        "//api",
        "//ext:headers",
        "//sdk:headers",
        "//sdk/src/common:random",
        "@curl",
        "@zlib",
    ],
)
