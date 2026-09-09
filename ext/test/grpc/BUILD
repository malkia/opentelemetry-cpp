# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

load("//bazel:otel_cc.bzl", "otel_cc_test_combo")

otel_cc_test_combo(
    name = "grpc_config_test",
    srcs = ["grpc_config_test.cc"],
    env = {
        "GRPC_VERBOSITY": "debug",
        "GRPC_EXPERIMENTS": ",".join([
            "-event_engine_client",
            "-event_engine_listener",
            "-event_engine_dns,",
        ]),
    },
    deps = [
        "//ext/src/grpc:grpc_config",
        "@googletest//:gtest_main",
        "@grpc//:grpc++",
    ],
)
