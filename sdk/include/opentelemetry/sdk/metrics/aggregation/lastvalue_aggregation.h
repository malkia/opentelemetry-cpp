// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <stdint.h>
#include <memory>

#include "opentelemetry/version.h"
#include "opentelemetry/common/spin_lock_mutex.h"
#include "opentelemetry/sdk/metrics/aggregation/aggregation.h"
#include "opentelemetry/sdk/metrics/data/metric_data.h"
#include "opentelemetry/sdk/metrics/data/point_data.h"

OPENTELEMETRY_BEGIN_NAMESPACE
namespace sdk
{
namespace metrics
{
class OPENTELEMETRY_EXPORT_TYPE LongLastValueAggregation : public Aggregation
{
public:
  LongLastValueAggregation();
  LongLastValueAggregation(const LastValuePointData &);

  void Aggregate(int64_t value, const PointAttributes &attributes = {}) noexcept override;

  void Aggregate(double /* value */, const PointAttributes & /* attributes */) noexcept override {}

  std::unique_ptr<Aggregation> Merge(const Aggregation &delta) const noexcept override;

  std::unique_ptr<Aggregation> Diff(const Aggregation &next) const noexcept override;

  PointType ToPoint() const noexcept override;

private:
  mutable opentelemetry::common::SpinLockMutex lock_;
  LastValuePointData point_data_;
};

class OPENTELEMETRY_EXPORT_TYPE DoubleLastValueAggregation : public Aggregation
{
public:
  DoubleLastValueAggregation();
  DoubleLastValueAggregation(const LastValuePointData &);

  void Aggregate(int64_t /* value */, const PointAttributes & /* attributes */) noexcept override {}

  void Aggregate(double value, const PointAttributes &attributes = {}) noexcept override;

  std::unique_ptr<Aggregation> Merge(const Aggregation &delta) const noexcept override;

  std::unique_ptr<Aggregation> Diff(const Aggregation &next) const noexcept override;

  PointType ToPoint() const noexcept override;

private:
  mutable opentelemetry::common::SpinLockMutex lock_;
  mutable LastValuePointData point_data_;
};

}  // namespace metrics
}  // namespace sdk
OPENTELEMETRY_END_NAMESPACE
