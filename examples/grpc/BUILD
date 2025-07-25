# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

load("@grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")
load("@protobuf//bazel:cc_proto_library.bzl", "cc_proto_library")
load("@rules_proto//proto:defs.bzl", "proto_library")
load("//:dll_deps.bzl", "dll_deps")
load("//bazel:otel_cc.bzl", "otel_cc_binary", "otel_cc_library")

package(default_visibility = ["//visibility:public"])

proto_library(
    name = "messages_proto",
    srcs = ["protos/messages.proto"],
)

cc_proto_library(
    name = "messages_cc_proto",
    deps = [":messages_proto"],
)

cc_grpc_library(
    name = "_messages_cc_grpc",
    srcs = [":messages_proto"],
    grpc_only = True,
    deps = [":messages_cc_proto"],
)

# Ideally we should not need this proxy otel_cc_library
# But neither cc_proto_library nor cc_grpc_library allow for
# include_prefix, includes or strip_include_prefix right now.
otel_cc_library(
    name = "messages_cc_grpc",
    includes = ["protos"],
    deps = ["_messages_cc_grpc"],
)

otel_cc_library(
    name = "tracer_common",
    srcs = ["tracer_common.h"],
    tags = ["ostream"],
    deps = dll_deps([
        "//exporters/ostream:ostream_span_exporter",
    ]),
)

otel_cc_binary(
    name = "client_grpc",
    srcs = [
        "client.cc",
    ],
    tags = ["ostream"],
    deps = dll_deps([
        "messages_cc_grpc",
        ":tracer_common",
        "//api",
        "//sdk/src/trace",
        "@grpc//:grpc++",
    ]),
)

otel_cc_binary(
    name = "server_grpc",
    srcs = [
        "server.cc",
    ],
    tags = ["ostream"],
    deps = dll_deps([
        "messages_cc_grpc",
        ":tracer_common",
        "//api",
        "//sdk/src/trace",
        "@grpc//:grpc++",
    ]),
)
