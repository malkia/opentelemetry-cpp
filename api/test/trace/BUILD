# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

load("//:dll_deps.bzl", "dll_deps")
load("//bazel:otel_cc.bzl", "otel_cc_test_combo")
load("//bazel:otel_cc_benchmark.bzl", "otel_cc_benchmark")

otel_cc_test_combo(
    name = "default_span_test",
    srcs = [
        "default_span_test.cc",
    ],
    tags = [
        "api",
        "test",
        "trace",
    ],
    deps = [
        "//api",
        "@googletest//:gtest_main",
    ],
)

otel_cc_test_combo(
    name = "context_test",
    srcs = [
        "context_test.cc",
    ],
    tags = [
        "api",
        "test",
        "trace",
    ],
    deps = [
        "//api",
        "@googletest//:gtest_main",
    ],
)

otel_cc_test_combo(
    name = "noop_test",
    srcs = [
        "noop_test.cc",
    ],
    tags = [
        "api",
        "test",
        "trace",
    ],
    deps = [
        "//api",
        "@googletest//:gtest_main",
    ],
)

otel_cc_test_combo(
    name = "key_value_iterable_view_test",
    srcs = [
        "key_value_iterable_view_test.cc",
    ],
    tags = [
        "api",
        "test",
        "trace",
    ],
    deps = [
        "//api",
        "@googletest//:gtest_main",
    ],
)

otel_cc_benchmark(
    name = "span_id_benchmark",
    srcs = ["span_id_benchmark.cc"],
    tags = [
        "api",
        "benchmark",
        "test",
        "trace",
    ],
    deps = [
        "//api",
    ],
)

otel_cc_benchmark(
    name = "span_benchmark",
    srcs = ["span_benchmark.cc"],
    tags = [
        "api",
        "benchmark",
        "test",
        "trace",
    ],
    deps = [
        "//api",
    ],
)

otel_cc_test_combo(
    name = "provider_test",
    srcs = [
        "provider_test.cc",
    ],
    tags = [
        "api",
        "test",
        "trace",
    ],
    deps = [
        "//api",
        "@googletest//:gtest_main",
    ],
)

otel_cc_test_combo(
    name = "span_id_test",
    srcs = [
        "span_id_test.cc",
    ],
    tags = [
        "api",
        "test",
        "trace",
    ],
    deps = [
        "//api",
        "@googletest//:gtest_main",
    ],
)

otel_cc_test_combo(
    name = "trace_flags_test",
    srcs = [
        "trace_flags_test.cc",
    ],
    tags = [
        "api",
        "test",
        "trace",
    ],
    deps = [
        "//api",
        "@googletest//:gtest_main",
    ],
)

otel_cc_test_combo(
    name = "trace_id_test",
    srcs = [
        "trace_id_test.cc",
    ],
    tags = [
        "api",
        "test",
        "trace",
    ],
    deps = [
        "//api",
        "@googletest//:gtest_main",
    ],
)

otel_cc_test_combo(
    name = "span_context_test",
    srcs = [
        "span_context_test.cc",
    ],
    tags = [
        "api",
        "test",
        "trace",
    ],
    deps = [
        "//api",
        "@googletest//:gtest_main",
    ],
)

otel_cc_test_combo(
    name = "trace_state_test",
    srcs = [
        "trace_state_test.cc",
    ],
    tags = [
        "api",
        "test",
        "trace",
    ],
    deps = [
        "//api",
        "@googletest//:gtest_main",
    ],
)

otel_cc_test_combo(
    name = "scope_test",
    srcs = [
        "scope_test.cc",
    ],
    tags = [
        "api",
        "test",
        "trace",
    ],
    deps = [
        "//api",
        "@googletest//:gtest_main",
    ],
)

otel_cc_test_combo(
    name = "tracer_test",
    srcs = [
        "tracer_test.cc",
    ],
    tags = [
        "api",
        "test",
        "trace",
    ],
    deps = [
        "//api",
        "@googletest//:gtest_main",
    ],
)
