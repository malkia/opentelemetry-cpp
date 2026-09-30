# OpenTelemetry C++

OpenTelemetry C++ is a comprehensive telemetry SDK providing APIs and
implementations for traces, metrics, and logs.

**This fork (`malkia/opentelemetry-cpp`) is an experimental Windows-only branch
(see [dll.md](../dll.md)) that builds a single combined `otel_sdk_r.dll`,
instead of upstream's separate api/sdk static libraries.** This fork:

- **Only uses Bazel.** There is no supported CMake workflow here (unlike
  upstream `open-telemetry/opentelemetry-cpp`); ignore `CMakeLists.txt`,
  `cmake/`, and any CMake instructions found elsewhere (including upstream
  docs and stale content in this fork).
- **Does not use the `ci/` folder.** `ci/do_ci.sh`, `ci/do_ci.ps1`, and
  everything else under `ci/` are unused leftovers from upstream. The only
  CI workflow that matters is
  [`.github/workflows/otel_sdk.yml`](workflows/otel_sdk.yml), which drives
  builds through **`otel_sdk_build.cmd`** at the repo root.

Always reference these instructions first and fall back to search only when
you encounter something that doesn't match the info here.

## Working Effectively

### Build, Test, and Package (`otel_sdk_build.cmd`)

`otel_sdk_build.cmd` (Windows `cmd.exe` batch script) is the single entry
point used by CI and should be used for local development too. It wraps
`bazel`/`bazelisk` (auto-detected from winget install paths, or falls back to
`bazel` on PATH). Run from the repo root:

```bat
:: Minimal sanity build: builds the DLL variants and runs the //install/... tests
:: with_dll both true and false. Fastest way to check a change builds.
otel_sdk_build.cmd minimal

:: Full test matrix: builds "..." (all targets) with --//:with_dll=true, then
:: runs bazel test in dbg, fastbuild, and opt compilation modes.
otel_sdk_build.cmd test

:: Packages otel_sdk.zip (include/, lib/, bin/ per config) via the
:: make_otel_sdk bazel run target.
otel_sdk_build.cmd zip

:: Runs everything: test-with-dll=false, then test, then zip, then shutdown.
otel_sdk_build.cmd

:: Stops the Bazel server (frees disk cache locks, useful between runs).
otel_sdk_build.cmd shutdown
```

Each step is a thin wrapper around plain Bazel invocations, e.g.:

```bat
bazel build --//:with_dll=true otel_sdk_d otel_sdk_rd otel_sdk_r
bazel test --//:with_dll=true -c dbg -- ... -otel_sdk_zip
bazel run --//:with_dll=true make_otel_sdk
```

The `--//:with_dll` flag (defined in the root `BUILD` file) toggles between
the combined-DLL build (`true`, this fork's main scenario) and a
static/no-DLL build (`false`, closer to upstream behavior) — pass whichever
matches the scenario you're validating. `-c dbg|fastbuild|opt` selects the
Bazel compilation mode.

**NEVER CANCEL** Bazel builds/tests; the first run in particular can take a
long time as it downloads and compiles dependencies. Set generous timeouts
(15+ minutes) instead of assuming a hang.

### Ad-hoc Bazel Commands

For iterating on a single target instead of the full `otel_sdk_build.cmd`
matrix:

```bat
:: Build/run a single example
bazel build --//:with_dll=true //examples/simple:example_simple
bazel-bin\examples\simple\example_simple.exe

:: Run a subset of tests
bazel test --//:with_dll=true -- //api/... //sdk/...
bazel test --//:with_dll=true //sdk/test/trace:some_specific_test
```

### CI Workflow Reference

`.github/workflows/otel_sdk.yml` runs on `windows-2025-vs2026` runners and:

1. Installs/updates `bazelisk` and LLVM via `winget`/`choco`.
2. Mounts a ReFS-formatted VHDX disk cache (`d:/d.vhdx`) used for Bazel's
   `--disk_cache` and `--repository_cache`.
3. Appends build flags to `../top.bazelrc` (a file *outside* the repo, which
   `.bazelrc` `try-import`s) — e.g. `--disk_cache`, `--repository_cache`,
   `--output_user_root`.
4. Runs `otel_sdk_build.cmd minimal`, then `shutdown`, then `test`, then
   `zip`, then `shutdown` again.
5. Uploads `otel_sdk.zip` and `*.tracing.json` Bazel profiles as artifacts,
   and attaches them to GitHub Releases when the trigger is a tag push.

If you need to reproduce CI locally, replicate the `top.bazelrc` disk/repo
cache lines (or omit them for a plain local build) and run the same
`otel_sdk_build.cmd` steps.

## Architecture

- **Header-only API, compiled SDK**: `api/` is a header-only library
  (`opentelemetry::trace`, `opentelemetry::metrics`, `opentelemetry::logs`,
  `opentelemetry::context`, `opentelemetry::nostd`) that instrumented
  libraries depend on with minimal footprint. `sdk/` provides the actual
  implementation (processors, providers, resource detection). In this fork,
  api + sdk (+ exporters, ext) are linked into one `otel_sdk_r.dll` instead
  of separate libraries — see `dll.md` for the rationale and limitations.
- **ABI/namespace versioning**: every public header wraps its contents in
  `OPENTELEMETRY_BEGIN_NAMESPACE` / `OPENTELEMETRY_END_NAMESPACE`
  (`api/include/opentelemetry/version.h`), which expands to
  `opentelemetry::v1` (an inline namespace) based on
  `OPENTELEMETRY_ABI_VERSION_NO`. Do not hardcode `opentelemetry::v1::...`;
  always go through these macros or plain `opentelemetry::...`.
- **Exporter factory pattern**: each exporter under `exporters/<name>/` (e.g.
  `exporters/otlp`, `exporters/ostream`, `exporters/prometheus`) exposes a
  `*Factory::Create(...)` static class (see
  `exporters/ostream/include/.../span_exporter_factory.h`) returning a
  `std::unique_ptr` to the SDK interface type. New exporters should follow
  this same Factory + interface split rather than exposing constructors
  directly, so the SDK core doesn't need exporter-specific headers.
- **DLL export macros**: symbols crossing shared-library boundaries use
  `OPENTELEMETRY_EXPORT` / `OPENTELEMETRY_EXPORT_TYPE` /
  `OPENTELEMETRY_API_SINGLETON`, which become `__declspec(dllexport)` /
  `dllimport` only when `OPENTELEMETRY_DLL` is defined (see `dll.md`).
  Consumers must `#define OPENTELEMETRY_DLL 1` and include
  `<opentelemetry/version.h>` before any other OpenTelemetry header. When
  adding new public classes/static members, check whether similar existing
  classes annotate them, especially anything holding process-wide singleton
  state.
- Each buildable unit (api, sdk, each exporter, each example) has its own
  Bazel `BUILD` file; a change to public headers or dependencies usually
  needs a corresponding `deps`/`srcs` update there, plus `MODULE.bazel` /
  `MODULE.bazel.lock` if an external dependency version changes.
- `dll_deps.bzl` / `dll_deps_generated.bzl` (regenerated via
  `dll_deps_update.cc`) enumerate the symbols/objects folded into the
  combined DLL — touch these if you add a new top-level library that must be
  bundled into `otel_sdk_r.dll`.

## Key Conventions

- Naming follows the [Google C++ Style
  Guide](https://google.github.io/styleguide/cppguide.html#Naming).
- All source files carry the `// Copyright The OpenTelemetry Authors` /
  `// SPDX-License-Identifier: Apache-2.0` header — copy it from a sibling
  file when creating new files.
- Formatting is enforced by `tools/format.sh` (clang-format for C++,
  buildifier for Bazel `BUILD`/`.bzl` files); run it before committing.
- Bazel `BUILD` files use the fork's own `otel_cc_binary` / `otel_cc_library`
  / `otel_cc_shared_library` / `otel_cc_test` macros (from
  `@otel_sdk_dev//bazel:otel_cc.bzl`) rather than native `cc_*` rules, so the
  `with_dll` config setting is applied consistently.
- Non-trivial PRs should update `CHANGELOG.md`.
