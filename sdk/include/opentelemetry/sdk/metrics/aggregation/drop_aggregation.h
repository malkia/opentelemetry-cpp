// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <memory>

#include "opentelemetry/version.h"
#include "opentelemetry/sdk/metrics/aggregation/aggregation.h"
#include "opentelemetry/sdk/metrics/data/point_data.h"

OPENTELEMETRY_BEGIN_NAMESPACE
namespace sdk
{
namespace metrics
{

/**
 * A null Aggregation which denotes no aggregation should occur.
 */

class OPENTELEMETRY_EXPORT_TYPE DropAggregation : public Aggregation
{
public:
  DropAggregation() = default;

  DropAggregation(const DropPointData &);

  void Aggregate(int64_t /* value */, const PointAttributes & /* attributes */) noexcept override {}

  void Aggregate(double /* value */, const PointAttributes & /* attributes */) noexcept override {}

  std::unique_ptr<Aggregation> Merge(const Aggregation &) const noexcept override;

  std::unique_ptr<Aggregation> Diff(const Aggregation &) const noexcept override;

  PointType ToPoint() const noexcept override;
};
}  // namespace metrics
}  // namespace sdk
OPENTELEMETRY_END_NAMESPACE
