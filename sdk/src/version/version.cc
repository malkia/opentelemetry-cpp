// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

// Please DONOT touch this file.
// Any changes done here would be overwritten by pre-commit git hook

#include "opentelemetry/sdk/version/version.h"

OPENTELEMETRY_BEGIN_NAMESPACE
namespace sdk
{
namespace version
{
const int major_version    = 1;
const int minor_version    = 22;
const int patch_version    = 0;
const char *pre_release    = "NONE";
const char *build_metadata = "NONE";
const char *short_version  = "1.22.0";
const char *full_version   = "1.22.0-NONE-NONE";
const char *build_date     = "Fri Jul 11 08:13:24 PM UTC 2025";
}  // namespace version
}  // namespace sdk
OPENTELEMETRY_END_NAMESPACE
