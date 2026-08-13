# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

load("//:dll_deps.bzl", "dll_deps")
load("//bazel:otel_cc.bzl", "otel_cc_test")

otel_cc_test(
    name = "resource_detector_test",
    srcs = [
        "container_detector_test.cc",
        "env_entity_detector_test.cc",
        "host_detector_test.cc",
        "process_detector_test.cc",
    ],
    linkopts = select({
        "//bazel:windows": [
            "-DEFAULTLIB:shell32.lib",
        ],
        "//conditions:default": [],
    }),
    tags = ["test"],
    deps = dll_deps([
        "//api",
        "//resource_detectors",
        "//sdk/src/resource",
        "@googletest//:gtest_main",
    ]),
)

# Kept separate from resource_detector_test: linking configuration_core pulls in
# sdk_builder.cc, which requires exception support, so this target is excluded
# from the bazel.noexcept build in ci/do_ci.sh.
otel_cc_test(
    name = "resource_detector_builder_test",
    srcs = [
        "container_detector_builder_test.cc",
        "process_detector_builder_test.cc",
    ],
    tags = ["test"],
    deps = dll_deps([
        "//api",
        "//resource_detectors",
        "//resource_detectors:resource_detectors_builders",
        "//sdk/src/configuration:configuration_core",
        "//sdk/src/resource",
        "@googletest//:gtest_main",
    ]),
)
