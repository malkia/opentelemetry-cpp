# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

load("//bazel:otel_cc.bzl", "otel_cc_test_combo")

otel_cc_test_combo(
    name = "no_exemplar_reservoir_test",
    srcs = [
        "no_exemplar_reservoir_test.cc",
    ],
    tags = [
        "metrics",
        "test",
    ],
    deps = [
        "//api",
        "//sdk:headers",
        "//sdk/src/metrics",
        "@googletest//:gtest_main",
    ],
)

otel_cc_test_combo(
    name = "reservoir_cell_test",
    srcs = [
        "reservoir_cell_test.cc",
    ],
    tags = [
        "metrics",
        "test",
    ],
    deps = [
        "//api",
        "//sdk:headers",
        "//sdk/src/metrics",
        "@googletest//:gtest_main",
    ],
)

otel_cc_test_combo(
    # name = "aligned_histogram_bucket_exemplar_reservoir_test",
    name = "aligned_hist_bkt_exem_rsvr_test",
    srcs = [
        "aligned_histogram_bucket_exemplar_reservoir_test.cc",
    ],
    tags = [
        "metrics",
        "test",
    ],
    deps = [
        "//api",
        "//sdk:headers",
        "//sdk/src/metrics",
        "@googletest//:gtest_main",
    ],
)

otel_cc_test_combo(
    name = "filter_predicate_test",
    srcs = [
        "filter_predicate_test.cc",
    ],
    tags = [
        "metrics",
        "test",
    ],
    deps = [
        "//api",
        "//sdk:headers",
        "//sdk/src/metrics",
        "@googletest//:gtest_main",
    ],
)
