# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

load("//:dll_deps.bzl", "dll_deps")
load("//bazel:otel_cc.bzl", "otel_cc_binary")

otel_cc_binary(
    name = "load_plugin",
    srcs = [
        "main.cc",
    ],
    args = [
        "$(rootpath //examples/plugin/plugin:example_plugin.so)",
        # This argument here is a dummy config file, that's been read and ignored
        "$(rootpath //examples/plugin/plugin:example_plugin.so)",
    ],
    linkopts = select({
        "//bazel:windows": [],
        "//conditions:default": ["-ldl"],
    }),
    deps = dll_deps([
        "//api",
        "//examples/plugin/plugin:example_plugin.so",
    ]),
)
