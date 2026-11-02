// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <atomic>

#include "opentelemetry/version.h"
#include "opentelemetry/common/macros.h"

OPENTELEMETRY_BEGIN_NAMESPACE
namespace sdk
{
namespace metrics
{

/**
 * A Meter's enabled flag, shared with every instrument it creates so a configurator update
 * reaches instruments that already exist. Relaxed ordering: no dependent data, only visibility.
 * A plain bool, not std::atomic, because API instruments read it through Flag().
 */
class MeterEnabledState
{
public:
  explicit MeterEnabledState(bool enabled = true) noexcept : enabled_(enabled) { }

  ~MeterEnabledState()                                    = default;
  MeterEnabledState(const MeterEnabledState &)            = delete;
  MeterEnabledState(MeterEnabledState &&)                 = delete;
  MeterEnabledState &operator=(const MeterEnabledState &) = delete;
  MeterEnabledState &operator=(MeterEnabledState &&)      = delete;

  bool IsEnabled() const noexcept
  {
    return enabled_;
  }

  void SetEnabled(bool enabled) noexcept { enabled_ = enabled; }

  /** The flag itself, valid for the lifetime of this object. */
  const std::atomic<bool> *Flag() const noexcept { return &enabled_; }

private:
  std::atomic<bool> enabled_;
};

}  // namespace metrics
}  // namespace sdk
OPENTELEMETRY_END_NAMESPACE
