# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive", "http_file")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def _deps1(mod_ext):
    maybe(
        http_file,
        name = "sentry_cli_windows_amd64",
        downloaded_file_path = "sentry-cli.exe",
        executable = True,
        sha256 = "bc51a87a60fa13a619ecaa93f9d442ae7e638a1718cb4616c6595ce7ab02ab25",
        urls = [
            "https://github.com/getsentry/sentry-cli/releases/download/2.23.0/sentry-cli-Windows-x86_64.exe",
        ],
    )

    maybe(
        http_archive,
        name = "loki_w64",
        integrity = "sha256-WHHTfjECfVv7Arj2xDoZLQH/qwQzxN59fe/F7duw3NQ=",
        urls = [
            "https://github.com/grafana/loki/releases/download/v2.8.7/loki-windows-amd64.exe.zip",
        ],
        build_file_content = """exports_files(["loki-windows-amd64.exe"],visibility=["//visibility:public"])""",
    )

    maybe(
        http_archive,
        name = "tempo_w64",
        integrity = "sha256-wx/dRthhU3jN5TIslzA+TfkTq33FfCdeqOhrWTwRTeY=",
        urls = [
            "https://github.com/grafana/tempo/releases/download/v2.3.1/tempo_2.3.1_windows_amd64.tar.gz",
        ],
        build_file_content = """exports_files(["tempo.exe", "temp-cli.exe", "tempo-query.exe"],visibility=["//visibility:public"])""",
    )

    maybe(
        http_archive,
        name = "otel_w64",
        integrity = "sha256-Uw7ZNY7PUEpsq2I5zRfeAjWIV09V5DP/E0/ZFYmKDbY=",
        urls = [
            "https://github.com/open-telemetry/opentelemetry-collector-releases/releases/download/v0.91.0/otelcol-contrib_0.91.0_windows_amd64.tar.gz",
        ],
        build_file_content = """exports_files(["otelcol-contrib.exe"],visibility=["//visibility:public"])""",
    )

    maybe(
        http_archive,
        name = "prom_w64",
        integrity = "sha256-RRm4zod7IKcTfcsaBFiEOYlYy3CpSG+px74FpeM4lus=",
        urls = [
            "https://github.com/prometheus/prometheus/releases/download/v2.48.1/prometheus-2.48.1.windows-amd64.tar.gz",
        ],
        strip_prefix = "prometheus-2.48.1.windows-amd64",
        build_file_content = """exports_files(["prometheus.exe","prometheus.yml","promtool.exe"],visibility=["//visibility:public"])""",
    )

    maybe(
        http_archive,
        name = "graf_w64",
        integrity = "sha256-Fq71INEDaRciK/Fj+Y+c16FYZnQnQMUe67rSxD7MPJA=",
        urls = [
            "https://dl.grafana.com/oss/release/grafana-10.2.3.windows-amd64.zip",
        ],
        strip_prefix = "grafana-v10.2.3",
        build_file_content = """
exports_files(glob(["**/*"]),visibility=["//visibility:public"])
filegroup(name="files",srcs=glob(["**/*"]),visibility=["//visibility:public"])
""",
    )

    maybe(
        http_archive,
        name = "ftxui",
        strip_prefix = "FTXUI-8178c7ac3adb9a14d76589126d611b10e1c45a97",
        integrity = "sha256-muqkm+RrpTI0MpOcQ455vRXwrOm0rs5rUfvI3BXHwGk=",
        type = "zip",
        urls = [
            "https://codeload.github.com/malkia/FTXUI/zip/8178c7ac3adb9a14d76589126d611b10e1c45a97",
        ],
    )

deps1 = module_extension(implementation = _deps1)
