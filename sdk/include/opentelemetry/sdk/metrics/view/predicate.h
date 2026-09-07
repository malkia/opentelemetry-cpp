// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <memory>
#include <string>

#include "opentelemetry/version.h"
#include "opentelemetry/nostd/string_view.h"

OPENTELEMETRY_BEGIN_NAMESPACE
namespace sdk
{
namespace metrics
{
class Predicate
{
public:
  Predicate() = default;

  Predicate(const Predicate &)            = delete;
  Predicate(Predicate &&)                 = delete;
  Predicate &operator=(const Predicate &) = delete;
  Predicate &operator=(Predicate &&)      = delete;

  virtual ~Predicate() = default;

  virtual bool Match(opentelemetry::nostd::string_view string) const noexcept = 0;
};

class OPENTELEMETRY_EXPORT_TYPE PatternPredicate : public Predicate
{
public:
  explicit PatternPredicate(opentelemetry::nostd::string_view pattern);

  PatternPredicate(const PatternPredicate &)            = delete;
  PatternPredicate(PatternPredicate &&)                 = delete;
  PatternPredicate &operator=(const PatternPredicate &) = delete;
  PatternPredicate &operator=(PatternPredicate &&)      = delete;

  ~PatternPredicate() override;

  bool Match(opentelemetry::nostd::string_view str) const noexcept override;

private:
  class Impl;
  std::unique_ptr<Impl> impl_;
};

class OPENTELEMETRY_EXPORT_TYPE WildcardPredicate : public Predicate
{
public:
  explicit WildcardPredicate(opentelemetry::nostd::string_view pattern);

  bool Match(opentelemetry::nostd::string_view str) const noexcept override;

private:
  std::string pattern_;
};

class OPENTELEMETRY_EXPORT_TYPE ExactPredicate : public Predicate
{
public:
  explicit ExactPredicate(opentelemetry::nostd::string_view pattern);

  bool Match(opentelemetry::nostd::string_view str) const noexcept override;

private:
  std::string pattern_;
};

class OPENTELEMETRY_EXPORT_TYPE MatchEverythingPattern : public Predicate
{
public:
  bool Match(opentelemetry::nostd::string_view str) const noexcept override;
};

class OPENTELEMETRY_EXPORT_TYPE MatchNothingPattern : public Predicate
{
public:
  bool Match(opentelemetry::nostd::string_view str) const noexcept override;
};
}  // namespace metrics
}  // namespace sdk
OPENTELEMETRY_END_NAMESPACE
