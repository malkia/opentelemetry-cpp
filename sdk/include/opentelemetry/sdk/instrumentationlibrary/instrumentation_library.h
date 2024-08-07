// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "opentelemetry/version.h"
#include "opentelemetry/sdk/instrumentationscope/instrumentation_scope.h"

OPENTELEMETRY_BEGIN_NAMESPACE

namespace sdk
{
namespace instrumentationlibrary
{

using InstrumentationLibrary = instrumentationscope::InstrumentationScope;

}  // namespace instrumentationlibrary
}  // namespace sdk

OPENTELEMETRY_END_NAMESPACE
