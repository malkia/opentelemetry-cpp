# Merge Strategy for OpenTelemetry C++ DLL Fork

This document outlines the custom merge rules for this soft fork, which focuses on creating a single monolithic DLL distribution (`otel_sdk_r.dll`) for Windows deployment.

## Overview

This fork diverges from upstream `github.com/open-telemetry/opentelemetry-cpp` by:
1. **Pre-defining compiler flags as preprocessor macros** in `opentelemetry/common/macros.h` instead of passing them via CMake command-line
2. **Baking opinionated configuration** directly into the DLL, eliminating the need for consumers to re-provide defines
3. **DLL-specific build artifacts** (`.bzl` files, build scripts, test utilities)

### Build System Reality

**Source of Truth: Bazel**
- Actual DLL builds use **Bazel exclusively**
- `.github/workflows/otel_sdk.yml` is the **only tested CI workflow** (Bazel-based)

**CMakeLists.txt: Maintenance Only**
- Kept in sync with upstream for long-term maintainability
- **NOT tested in CI** — changes here don't break the build
- Safe to merge upstream changes, but they won't be validated automatically

**Ignored Workflows**
- All other `.github/workflows/*.yml` files are **ignored and not run**
- Only `otel_sdk.yml` matters for this fork's DLL release cycle

## Critical Include Order

### Rule 1: `version.h` Must Be Included First

**File:** `opentelemetry/version.h`

This header:
- Includes `opentelemetry/common/macros.h` early (via IWYU pragma)
- Defines core namespace macros (`OPENTELEMETRY_BEGIN_NAMESPACE`, `OPENTELEMETRY_END_NAMESPACE`, etc.)
- Sets up the ABI version namespace

**Action:** In **all header files** within the OpenTelemetry API and SDK, ensure `#include "opentelemetry/version.h"` appears **before any other OpenTelemetry includes**.

### Rule 2: Custom Preprocessor Defines in `macros.h`

**File:** `opentelemetry/common/macros.h`

This file contains **dozens of custom preprocessor definitions** specific to this fork, including:
- Compiler feature detection macros (e.g., `OPENTELEMETRY_HAVE_FEATURE`, `OPENTELEMETRY_HAVE_ATTRIBUTE`)
- C++ standard feature checks (e.g., `OPENTELEMETRY_LIKELY_CONDITION` for C++20)
- Platform-specific behaviors

**Why it matters:** Unlike upstream (where these are CMake flags), we embed them in the DLL. All code that depends on these must see them **at compile time**.

**Action:** When merging upstream changes, verify that:
1. New header files include `opentelemetry/version.h` first
2. No upstream changes remove or reorder includes in `macros.h`
3. Any new feature detection macros are added to `macros.h`, not scattered across multiple files

## Merge Workflow

### Before Merge
1. Identify the upstream commit/tag to merge (e.g., `upstream/main`)
2. Create a merge branch: `git checkout -b merge/upstream-YYYYMMDD`

### During Merge
1. **Run conflict resolution** with your merge tool
2. **For each conflict in header files**, check the include order:
   ```cpp
   // ✓ CORRECT
   #include "opentelemetry/version.h"
   #include "opentelemetry/common/..." 
   #include "opentelemetry/api/..."
   
   // ✗ WRONG
   #include "opentelemetry/common/..."
   #include "opentelemetry/version.h"  // TOO LATE
   ```

### After Merge
1. **Validate with grep** (see [Validation](#validation) section below)
2. **Build and test**: Run `otel_sdk_build.cmd` to ensure DLL builds without preprocessor errors
3. **Run DLL tests**: Execute `dll_test.cc` to verify behavior

## Validation

### Grep Command: Find Headers Missing `version.h`

Check if any header file in `api/` or `sdk/` is missing the expected first include:

```powershell
# Find all .h files that don't start with version.h
git grep -L "#include.*opentelemetry/version.h" -- "api/include/**/*.h" "sdk/include/**/*.h"
```

### Grep Command: Find Incorrect Include Order

```powershell
# Look for version.h appearing after other otel includes (rough check)
git grep -n "#include.*opentelemetry/common\|#include.*opentelemetry/api" -- "api/include/**/*.h" "sdk/include/**/*.h" | grep -v "version.h"
```

### Build Validation

```powershell
# In the Windows environment, build the DLL
.\otel_sdk_build.cmd

# Run DLL tests
.\dll_test.cc
```

## Common Merge Scenarios

### Scenario 1: Upstream Adds New Header Files

**Expected**: New headers follow the include order rule.

```cpp
// NEW FILE: api/include/opentelemetry/new_feature/something.h
#pragma once

#include "opentelemetry/version.h"  // ← Always first
#include "opentelemetry/common/macros.h"
#include <vector>

// ... rest of header
```

**Action during merge**: Add the include if missing.

### Scenario 2: Upstream Reorganizes `macros.h`

**Expected**: Changes are merged, but **local custom defines remain**.

**Action during merge**:
1. Accept upstream version first
2. Re-add your custom defines at appropriate sections
3. Verify with grep that all custom macros are present

### Scenario 3: Upstream Changes CMake Build System

**Expected**: Changes to `CMakeLists.txt` or `.cmake` files may add new compile flags.

**Action during merge**:
1. Review the new CMake flags (e.g., `-DSOMETHING=value`)
2. **Check if they should be preprocessor macros instead** in `macros.h`
3. If yes, add them as `#define` statements in `macros.h` with appropriate conditions
4. Remove the CMake command-line define (since it's now baked into the DLL)

## Files to Watch During Merges

### Critical (Tested in CI via Bazel)
- `api/include/opentelemetry/version.h` — Core include hierarchy
- `api/include/opentelemetry/common/macros.h` — All custom defines
- `api/include/opentelemetry/` — Any new `.h` files added upstream
- `sdk/include/opentelemetry/` — SDK headers following the same rules
- `BUILD` and `*.bzl` — Bazel build files (source of truth for DLL builds)
- `.github/workflows/otel_sdk.yml` — The only tested workflow

### Important (Maintained for Upstream Alignment)
- `CMakeLists.txt` — Changes to compile flags; **merge but don't test**
  - Not used in your CI, so upstream changes here won't break the build
  - Keep in sync anyway for potential future adoption or community alignment
  - If it defines new compile flags, consider whether they should be in `macros.h`

### Ignored (Safe to Merge, Never Tested)
- `.github/workflows/` (except `otel_sdk.yml`) — All other CI workflows are ignored
- Any CMake-specific configuration files
- `cmake/` — Safe to merge, won't affect your builds

## References

- **Upstream repository**: https://github.com/open-telemetry/opentelemetry-cpp
- **DLL documentation**: See `dll.md` in repository root
- **Version header**: `api/include/opentelemetry/version.h`
- **Macros header**: `api/include/opentelemetry/common/macros.h`
