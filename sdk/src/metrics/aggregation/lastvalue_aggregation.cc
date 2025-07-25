// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#include <stdint.h>
#include <chrono>
#include <memory>
#include <mutex>

#include "opentelemetry/version.h"
#include "opentelemetry/common/spin_lock_mutex.h"
#include "opentelemetry/common/timestamp.h"
#include "opentelemetry/nostd/variant.h"
#include "opentelemetry/sdk/metrics/aggregation/aggregation.h"
#include "opentelemetry/sdk/metrics/aggregation/lastvalue_aggregation.h"
#include "opentelemetry/sdk/metrics/data/metric_data.h"
#include "opentelemetry/sdk/metrics/data/point_data.h"

OPENTELEMETRY_BEGIN_NAMESPACE
namespace sdk
{
namespace metrics
{

LongLastValueAggregation::LongLastValueAggregation()
{
  point_data_.is_lastvalue_valid_ = false;
  point_data_.value_              = static_cast<int64_t>(0);
}

LongLastValueAggregation::LongLastValueAggregation(const LastValuePointData &data)
    : point_data_{data}
{}

void LongLastValueAggregation::Aggregate(int64_t value,
                                         const PointAttributes & /* attributes */) noexcept
{
  const std::lock_guard<opentelemetry::common::SpinLockMutex> locked(lock_);
  point_data_.is_lastvalue_valid_ = true;
  point_data_.value_              = value;
  point_data_.sample_ts_          = std::chrono::system_clock::now();
}

std::unique_ptr<Aggregation> LongLastValueAggregation::Merge(
    const Aggregation &delta) const noexcept
{
  if (nostd::get<LastValuePointData>(ToPoint()).sample_ts_.time_since_epoch() >
      nostd::get<LastValuePointData>(delta.ToPoint()).sample_ts_.time_since_epoch())
  {
    LastValuePointData merge_data = nostd::get<LastValuePointData>(ToPoint());
    return std::unique_ptr<Aggregation>(new LongLastValueAggregation(merge_data));
  }
  else
  {
    LastValuePointData merge_data = nostd::get<LastValuePointData>(delta.ToPoint());
    return std::unique_ptr<Aggregation>(new LongLastValueAggregation(merge_data));
  }
}

std::unique_ptr<Aggregation> LongLastValueAggregation::Diff(const Aggregation &next) const noexcept
{
  if (nostd::get<LastValuePointData>(ToPoint()).sample_ts_.time_since_epoch() >
      nostd::get<LastValuePointData>(next.ToPoint()).sample_ts_.time_since_epoch())
  {
    LastValuePointData diff_data = nostd::get<LastValuePointData>(ToPoint());
    return std::unique_ptr<Aggregation>(new LongLastValueAggregation(diff_data));
  }
  else
  {
    LastValuePointData diff_data = nostd::get<LastValuePointData>(next.ToPoint());
    return std::unique_ptr<Aggregation>(new LongLastValueAggregation(diff_data));
  }
}

PointType LongLastValueAggregation::ToPoint() const noexcept
{
  const std::lock_guard<opentelemetry::common::SpinLockMutex> locked(lock_);
  return point_data_;
}

DoubleLastValueAggregation::DoubleLastValueAggregation()
{
  point_data_.is_lastvalue_valid_ = false;
  point_data_.value_              = 0.0;
}

DoubleLastValueAggregation::DoubleLastValueAggregation(const LastValuePointData &data)
    : point_data_{data}
{}

void DoubleLastValueAggregation::Aggregate(double value,
                                           const PointAttributes & /* attributes */) noexcept
{
  const std::lock_guard<opentelemetry::common::SpinLockMutex> locked(lock_);
  point_data_.is_lastvalue_valid_ = true;
  point_data_.value_              = value;
  point_data_.sample_ts_          = std::chrono::system_clock::now();
}

std::unique_ptr<Aggregation> DoubleLastValueAggregation::Merge(
    const Aggregation &delta) const noexcept
{
  if (nostd::get<LastValuePointData>(ToPoint()).sample_ts_.time_since_epoch() >
      nostd::get<LastValuePointData>(delta.ToPoint()).sample_ts_.time_since_epoch())
  {
    LastValuePointData merge_data = nostd::get<LastValuePointData>(ToPoint());
    return std::unique_ptr<Aggregation>(new DoubleLastValueAggregation(merge_data));
  }
  else
  {
    LastValuePointData merge_data = nostd::get<LastValuePointData>(delta.ToPoint());
    return std::unique_ptr<Aggregation>(new DoubleLastValueAggregation(merge_data));
  }
}

std::unique_ptr<Aggregation> DoubleLastValueAggregation::Diff(
    const Aggregation &next) const noexcept
{
  if (nostd::get<LastValuePointData>(ToPoint()).sample_ts_.time_since_epoch() >
      nostd::get<LastValuePointData>(next.ToPoint()).sample_ts_.time_since_epoch())
  {
    LastValuePointData diff_data = nostd::get<LastValuePointData>(ToPoint());
    return std::unique_ptr<Aggregation>(new DoubleLastValueAggregation(diff_data));
  }
  else
  {
    LastValuePointData diff_data = nostd::get<LastValuePointData>(next.ToPoint());
    return std::unique_ptr<Aggregation>(new DoubleLastValueAggregation(diff_data));
  }
}

PointType DoubleLastValueAggregation::ToPoint() const noexcept
{
  const std::lock_guard<opentelemetry::common::SpinLockMutex> locked(lock_);
  return point_data_;
}
}  // namespace metrics
}  // namespace sdk
OPENTELEMETRY_END_NAMESPACE
