load("@depend_on_what_you_use//:defs.bzl", "dwyu_aspect_factory")

# bazel build --aspects=//:dwyu.bzl%dwyu_aspect --output_groups=dwyu ...

# Options listed here https://github.com/martis42/depend_on_what_you_use/blob/main/docs/dwyu_aspect.md
dwyu_aspect = dwyu_aspect_factory(
    analysis_optimizes_impl_deps = True,
    analysis_reports_missing_direct_deps = True,
    analysis_reports_unused_deps = True,
    ignored_includes = None, 
    no_preprocessor = True,
    recursive = True,
    skip_external_targets = False,
    skipped_tags = [],
    target_mapping = None,
    verbose = False,
)


