// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "opentelemetry/common/spin_lock_mutex.h"
#include "opentelemetry/sdk/metrics/aggregation/aggregation.h"

#include <mutex>

OPENTELEMETRY_BEGIN_NAMESPACE
namespace sdk
{
namespace metrics
{
class OPENTELEMETRY_SDK_METRICS_EXPORT LongLastValueAggregation : public Aggregation
{
public:
  LongLastValueAggregation();
  LongLastValueAggregation(LastValuePointData &&);
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

class OPENTELEMETRY_SDK_METRICS_EXPORT DoubleLastValueAggregation : public Aggregation
{
public:
  DoubleLastValueAggregation();
  DoubleLastValueAggregation(LastValuePointData &&);
  DoubleLastValueAggregation(const LastValuePointData &);

  void Aggregate(int64_t /* value */, const PointAttributes & /* attributes */) noexcept override {}

  void Aggregate(double value, const PointAttributes &attributes = {}) noexcept override;

  virtual std::unique_ptr<Aggregation> Merge(const Aggregation &delta) const noexcept override;

  virtual std::unique_ptr<Aggregation> Diff(const Aggregation &next) const noexcept override;

  PointType ToPoint() const noexcept override;

private:
  mutable opentelemetry::common::SpinLockMutex lock_;
  mutable LastValuePointData point_data_;
};

}  // namespace metrics
}  // namespace sdk
OPENTELEMETRY_END_NAMESPACE
