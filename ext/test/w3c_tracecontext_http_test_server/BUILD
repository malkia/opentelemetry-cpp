# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

load("//bazel:otel_cc.bzl", "otel_cc_binary_combo")

otel_cc_binary_combo(
    name = "w3c_tracecontext_http_test_server",
    srcs = [
        "main.cc",
    ],
    linkopts = select({
        "//bazel:windows": [
            "-DEFAULTLIB:advapi32.lib",
            "-DEFAULTLIB:crypt32.lib",
            "-DEFAULTLIB:Normaliz.lib",
        ],
        "//conditions:default": [],
    }),
    deps = [
        "//api",
        "//exporters/ostream:ostream_span_exporter",
        "//ext:headers",
        "//ext/src/http/client/curl:http_client_curl",
        "//sdk/src/trace",
        "@curl",
        "@nlohmann_json//:json",
    ],
)
