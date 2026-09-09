# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

load("//:dll_deps.bzl", "dll_deps", "dll_deps_forced")
load("@rules_cc//cc:cc_shared_library.bzl", "cc_shared_library")
load(
    "@rules_cc//cc:defs.bzl",
    rules_cc_binary = "cc_binary",
    rules_cc_import = "cc_import",
    rules_cc_library = "cc_library",
    rules_cc_test = "cc_test",
)

def if_asanwin(a):
    return select({
        "@otel_sdk_dev//:asanwin_enabled": a,
        "//conditions:default": [],
    })

def otel_cc_library(**kwargs):
    # Link as .o (.obj) files, not .a (.lib)
    kwargs["alwayslink"] = kwargs.get("alwayslink", True)

    # Don't create .so files for dbg/fastbuild, always create static libs
    kwargs["linkstatic"] = kwargs.get("linkstatic", True)
    rules_cc_library(**kwargs)

def otel_cc_test_library(**kwargs):
    kwargs["testonly"] = kwargs.get("testonly", True)
    otel_cc_library(**kwargs)

def otel_cc_binary(**kwargs):
    kwargs["deps"] = kwargs.get("deps", []) + if_asanwin(["@llvm_windows_install//:asan"])
    rules_cc_binary(**kwargs)

def otel_cc_test(**kwargs):
    kwargs["deps"] = kwargs.get("deps", []) + if_asanwin(["@llvm_windows_install//:asan"])
    rules_cc_test(**kwargs)

def otel_cc_test_combo(name,deps,**kwargs):
    rules_cc_test(
        # link to the static opentelemetry lib
        name = name + ".a",    
        target_compatible_with = select({
            "@otel_sdk_dev//:with_dll_enabled": ["@platforms//:incompatible"],
            "//conditions:default": None,
        }),
        deps = deps,
        **kwargs
    )
    rules_cc_test(
        # link to the dynamic opentelemetry shared lib
        name = name + ".d",    
        target_compatible_with = select({
            "@otel_sdk_dev//:with_dll_enabled": None, 
            "//conditions:default": ["@platforms//:incompatible"],
        }),
        deps = dll_deps_forced(deps),
        **kwargs
    )
    
def otel_cc_import(**kwargs):
    rules_cc_import(**kwargs)

def otel_cc_shared_library(**kwargs):
    kwargs["deps"] = kwargs.get("deps", []) + if_asanwin(["@llvm_windows_install//:asan"])
    cc_shared_library(**kwargs)
