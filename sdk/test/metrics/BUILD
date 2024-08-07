# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

load("//bazel:otel_cc_benchmark.bzl", "otel_cc_benchmark")
load("//:dll_deps.bzl", "dll_deps")
load("//bazel:otel_cc.bzl", "otel_cc_binary", "otel_cc_import", "otel_cc_library", "otel_cc_shared_library", "otel_cc_test")

otel_cc_library(
    name = "metrics_common_test_utils",
    testonly = 1,
    srcs = [
        "common.cc",
    ],
    hdrs = ["common.h"],
    tags = [
        "metrics",
        "test",
    ],
    deps = dll_deps([
        "//sdk/src/metrics",
    ]),
)

otel_cc_test(
    name = "meter_test",
    srcs = [
        "meter_test.cc",
    ],
    tags = [
        "metrics",
        "test",
    ],
    deps = dll_deps([
        "metrics_common_test_utils",
        "@googletest//:gtest_main",
    ]),
)

otel_cc_test(
    name = "meter_provider_sdk_test",
    srcs = [
        "meter_provider_sdk_test.cc",
    ],
    tags = [
        "metrics",
        "test",
    ],
    deps = dll_deps([
        "metrics_common_test_utils",
        "//sdk/src/resource",
        "@googletest//:gtest_main",
    ]),
)

otel_cc_test(
    name = "metric_reader_test",
    srcs = [
        "metric_reader_test.cc",
    ],
    tags = [
        "metrics",
        "test",
    ],
    deps = dll_deps([
        "metrics_common_test_utils",
        "//sdk/src/resource",
        "@googletest//:gtest_main",
    ]),
)

otel_cc_test(
    name = "histogram_test",
    srcs = [
        "histogram_test.cc",
    ],
    tags = [
        "metrics",
        "test",
    ],
    deps = dll_deps([
        "metrics_common_test_utils",
        "//sdk/src/resource",
        "@googletest//:gtest_main",
    ]),
)

otel_cc_test(
    name = "view_registry_test",
    srcs = [
        "view_registry_test.cc",
    ],
    tags = [
        "metrics",
        "test",
    ],
    deps = dll_deps([
        "metrics_common_test_utils",
        "//sdk/src/resource",
        "@googletest//:gtest_main",
    ]),
)

otel_cc_test(
    name = "aggregation_test",
    srcs = [
        "aggregation_test.cc",
    ],
    tags = [
        "metrics",
        "test",
    ],
    deps = dll_deps([
        "metrics_common_test_utils",
        "//sdk/src/resource",
        "@googletest//:gtest_main",
    ]),
)

otel_cc_test(
    name = "sync_metric_storage_counter_test",
    srcs = [
        "sync_metric_storage_counter_test.cc",
    ],
    tags = [
        "metrics",
        "test",
    ],
    deps = dll_deps([
        "metrics_common_test_utils",
        "//sdk/src/resource",
        "@googletest//:gtest_main",
    ]),
)

otel_cc_test(
    name = "sync_metric_storage_up_down_counter_test",
    srcs = [
        "sync_metric_storage_up_down_counter_test.cc",
    ],
    tags = [
        "metrics",
        "test",
    ],
    deps = dll_deps([
        "metrics_common_test_utils",
        "//sdk/src/resource",
        "@googletest//:gtest_main",
    ]),
)

otel_cc_test(
    name = "sync_metric_storage_histogram_test",
    srcs = [
        "sync_metric_storage_histogram_test.cc",
    ],
    tags = [
        "metrics",
        "test",
    ],
    deps = dll_deps([
        "metrics_common_test_utils",
        "//sdk/src/resource",
        "@googletest//:gtest_main",
    ]),
)

otel_cc_test(
    name = "sync_instruments_test",
    srcs = [
        "sync_instruments_test.cc",
    ],
    tags = [
        "metrics",
        "test",
    ],
    deps = dll_deps([
        "metrics_common_test_utils",
        "//sdk/src/resource",
        "@googletest//:gtest_main",
    ]),
)

otel_cc_test(
    name = "async_instruments_test",
    srcs = [
        "async_instruments_test.cc",
    ],
    tags = [
        "metrics",
        "test",
    ],
    deps = dll_deps([
        "metrics_common_test_utils",
        "@googletest//:gtest_main",
    ]),
)

otel_cc_test(
    name = "async_metric_storage_test",
    srcs = [
        "async_metric_storage_test.cc",
    ],
    tags = [
        "metrics",
        "test",
    ],
    deps = dll_deps([
        "metrics_common_test_utils",
        "//sdk/src/resource",
        "@googletest//:gtest_main",
    ]),
)

otel_cc_test(
    name = "observer_result_test",
    srcs = [
        "observer_result_test.cc",
    ],
    tags = [
        "metrics",
        "test",
    ],
    deps = dll_deps([
        "metrics_common_test_utils",
        "//sdk/src/resource",
        "@googletest//:gtest_main",
    ]),
)

otel_cc_test(
    name = "multi_metric_storage_test",
    srcs = [
        "multi_metric_storage_test.cc",
    ],
    tags = [
        "metrics",
        "test",
    ],
    deps = dll_deps([
        "metrics_common_test_utils",
        "//sdk/src/resource",
        "@googletest//:gtest_main",
    ]),
)

otel_cc_test(
    name = "attributes_processor_test",
    srcs = [
        "attributes_processor_test.cc",
    ],
    tags = [
        "metrics",
        "test",
    ],
    deps = dll_deps([
        "metrics_common_test_utils",
        "@googletest//:gtest_main",
    ]),
)

otel_cc_test(
    name = "attributes_hashmap_test",
    srcs = [
        "attributes_hashmap_test.cc",
    ],
    tags = [
        "metrics",
        "test",
    ],
    deps = dll_deps([
        "metrics_common_test_utils",
        "@googletest//:gtest_main",
    ]),
)

otel_cc_test(
    name = "circular_buffer_counter_test",
    srcs = [
        "circular_buffer_counter_test.cc",
    ],
    tags = [
        "metrics",
        "test",
    ],
    deps = dll_deps([
        "//sdk/src/metrics",
        "@googletest//:gtest_main",
    ]),
)

otel_cc_test(
    #name = "base2_exponential_histogram_indexer_test",
    name = "b2exphist_idx_test",
    srcs = [
        "base2_exponential_histogram_indexer_test.cc",
    ],
    tags = [
        "metrics",
        "test",
    ],
    deps = dll_deps([
        "metrics_common_test_utils",
        "@googletest//:gtest_main",
    ]),
)

otel_cc_test(
    name = "histogram_aggregation_test",
    srcs = [
        "histogram_aggregation_test.cc",
    ],
    tags = [
        "metrics",
        "test",
    ],
    deps = dll_deps([
        "metrics_common_test_utils",
        "@googletest//:gtest_main",
    ]),
)

otel_cc_test(
    name = "sum_aggregation_test",
    srcs = [
        "sum_aggregation_test.cc",
    ],
    tags = [
        "metrics",
        "test",
    ],
    deps = dll_deps([
        "metrics_common_test_utils",
        "@googletest//:gtest_main",
    ]),
)

otel_cc_benchmark(
    name = "attributes_processor_benchmark",
    srcs = [
        "attributes_processor_benchmark.cc",
    ],
    tags = [
        "benchmark",
        "metrics",
        "test",
    ],
    deps = dll_deps([
        "metrics_common_test_utils",
    ]),
)

otel_cc_benchmark(
    name = "attributes_hashmap_benchmark",
    srcs = [
        "attributes_hashmap_benchmark.cc",
    ],
    tags = [
        "benchmark",
        "metrics",
        "test",
    ],
    deps = dll_deps([
        "metrics_common_test_utils",
    ]),
)

otel_cc_benchmark(
    #name = "base2_exponential_histogram_indexer_benchmark",
    name = "b2exphist_idx_benchmark",
    srcs = [
        "base2_exponential_histogram_indexer_benchmark.cc",
    ],
    tags = [
        "benchmark",
        "metrics",
        "test",
    ],
    deps = dll_deps([
        "metrics_common_test_utils",
    ]),
)

otel_cc_benchmark(
    name = "histogram_aggregation_benchmark",
    srcs = [
        "histogram_aggregation_benchmark.cc",
    ],
    tags = [
        "benchmark",
        "metrics",
        "test",
    ],
    deps = dll_deps([
        "metrics_common_test_utils",
        "//sdk/src/metrics",
        "//sdk/src/resource",
    ]),
)

otel_cc_benchmark(
    name = "sum_aggregation_benchmark",
    srcs = [
        "sum_aggregation_benchmark.cc",
    ],
    tags = [
        "benchmark",
        "metrics",
        "test",
    ],
    deps = dll_deps([
        "metrics_common_test_utils",
        "//sdk/src/metrics",
        "//sdk/src/resource",
    ]),
)

otel_cc_benchmark(
    name = "measurements_benchmark",
    srcs = [
        "measurements_benchmark.cc",
    ],
    tags = [
        "benchmark",
        "metrics",
        "test",
    ],
    deps = dll_deps([
        "//sdk/src/metrics",
        "//sdk/src/resource",
    ]),
)
