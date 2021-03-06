/**
 * This file is part of the "FnordMetric" project
 *   Copyright (c) 2011-2014 Paul Asmuth, Google Inc.
 *
 * FnordMetric is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License v3.0. You should have received a
 * copy of the GNU General Public License along with this program. If not, see
 * <http://www.gnu.org/licenses/>.
 */
#include <fnordmetric/ui/domain.h>
#include <fnordmetric/ui/continuousdomain.h>
#include <fnordmetric/ui/discretedomain.h>
#include <fnordmetric/ui/timedomain.h>

using namespace fnord;
namespace fnordmetric {
namespace ui {

const char AnyDomain::kDimensionLetters[] = "xyz";
const int AnyDomain::kDefaultNumTicks = 8;
const double AnyDomain::kDefaultDomainPadding = 0.1;

template <> Domain<fnordmetric::IntegerType>*
    Domain<fnordmetric::IntegerType>::mkDomain() {
  return new ContinuousDomain<fnordmetric::IntegerType>();
}

template <> Domain<fnordmetric::FloatType>*
    Domain<fnordmetric::FloatType>::mkDomain() {
  return new ContinuousDomain<fnordmetric::FloatType>();
}

template <> Domain<fnordmetric::TimeType>*
    Domain<fnordmetric::TimeType>::mkDomain() {
  return new TimeDomain();
}

template <> Domain<std::string>* Domain<std::string>::mkDomain() {
  return new DiscreteDomain<std::string>();
}

}
}

