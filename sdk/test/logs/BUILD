# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

load("//bazel:otel_cc.bzl", "otel_cc_test_combo")

otel_cc_test_combo(
    name = "logger_provider_sdk_test",
    srcs = [
        "logger_provider_sdk_test.cc",
    ],
    tags = [
        "logs",
        "test",
    ],
    deps = [
        "//api",
        "//sdk/src/logs",
        "@googletest//:gtest_main",
    ],
)

otel_cc_test_combo(
    name = "logger_provider_set_test",
    srcs = [
        "logger_provider_set_test.cc",
    ],
    tags = [
        "logs",
        "test",
    ],
    deps = [
        "//api",
        "//sdk/src/logs",
        "@googletest//:gtest_main",
    ],
)

otel_cc_test_combo(
    name = "logger_sdk_test",
    srcs = [
        "logger_sdk_test.cc",
    ],
    tags = [
        "logs",
        "test",
    ],
    deps = [
        "//sdk/src/logs",
        "//sdk/src/trace",
        "@googletest//:gtest_main",
    ],
)

otel_cc_test_combo(
    name = "simple_log_record_processor_test",
    srcs = [
        "simple_log_record_processor_test.cc",
    ],
    tags = [
        "logs",
        "test",
    ],
    deps = [
        "//sdk/src/logs",
        "@googletest//:gtest_main",
    ],
)

otel_cc_test_combo(
    name = "multi_log_record_processor_test",
    srcs = [
        "multi_log_record_processor_test.cc",
    ],
    tags = [
        "logs",
        "test",
    ],
    deps = [
        "//sdk/src/logs",
        "@googletest//:gtest_main",
    ],
)

otel_cc_test_combo(
    name = "log_record_test",
    srcs = [
        "log_record_test.cc",
    ],
    tags = [
        "logs",
        "test",
    ],
    deps = [
        "//sdk/src/logs",
        "@googletest//:gtest_main",
    ],
)

otel_cc_test_combo(
    name = "log_record_limits_test",
    srcs = [
        "log_record_limits_test.cc",
    ],
    tags = [
        "logs",
        "test",
    ],
    deps = [
        "//api",
        "//sdk/src/logs",
        "@googletest//:gtest_main",
    ],
)

otel_cc_test_combo(
    name = "batch_log_record_processor_test",
    srcs = [
        "batch_log_record_processor_test.cc",
    ],
    tags = [
        "logs",
        "test",
    ],
    deps = [
        "//sdk/src/logs",
        "@googletest//:gtest_main",
    ],
)

otel_cc_test_combo(
    name = "batch_log_record_processor_test_stress",
    srcs = glob(["*_test_stress.cc"]),
    tags = [
        "logs",
        "test",
    ],
    deps = [
        "//sdk/src/logs",
        "@googletest//:gtest_main",
    ],
)

otel_cc_test_combo(
    name = "logger_config_test",
    srcs = [
        "logger_config_test.cc",
    ],
    tags = [
        "logs",
        "test",
    ],
    deps = [
        "//sdk/src/logs",
        "@googletest//:gtest_main",
    ],
)
