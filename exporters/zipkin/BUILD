package(default_visibility = ["//visibility:public"])

cc_library(
    name = "zipkin_recordable",
    srcs = [
        "src/recordable.cc",
    ],
    hdrs = [
        "include/opentelemetry/exporters/zipkin/recordable.h",
    ],
    strip_include_prefix = "include",
    deps = [
        "//sdk/src/resource",
        "//sdk/src/trace",
        "@github_nlohmann_json//:json",
    ],
)

cc_library(
    name = "zipkin_exporter",
    srcs = [
        "src/zipkin_exporter.cc",
    ],
    hdrs = [
        "include/opentelemetry/exporters/zipkin/zipkin_exporter.h",
    ],
    copts = [
        "-DCURL_STATICLIB",
    ],
    strip_include_prefix = "include",
    deps = [
        ":zipkin_recordable",
        "//ext/src/http/client/curl:http_client_curl",
    ],
)

cc_test(
    name = "zipkin_recordable_test",
    srcs = ["test/zipkin_recordable_test.cc"],
    deps = [
        ":zipkin_recordable",
        "@com_google_googletest//:gtest_main",
    ],
)