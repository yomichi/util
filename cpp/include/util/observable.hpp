/**
 * observable.hpp
 *
 * Minimal Monte Carlo observable.
 * 
 * Copyright (c) 2013 by Yuichi Motoyama <yomichi@tsg.jp>
 *
 * Distributed under the Boost Software License version 1.0.
 * (See acompanied file License.txt or http://www.boost.org/LICENSE_1_0.txt)
 *
 */


#ifndef OBSERVABLE_HPP
#define OBSERVABLE_HPP

#include "pow2.hpp"

namespace util{

template <class T>
class Obs{
public:
  typedef T value_type;

  Obs():num_(0),sum_(value_type()),sum2_(value_type()){}
  Obs& operator<<(value_type const &val)
  {
    ++num_;
    sum_ += val;
    sum2_ += val*val;
    return *this;
  }
  value_type mean() const { return sum_/num_; }
  value_type var()  const { return sum2_/num_ - pow2(mean()); }
  value_type error()const { return std::sqrt(var()/(num_-1)); }
  int count() const { return num_;}

private:
  int num_;
  value_type sum_;
  value_type sum2_;
};

typedef Obs<double> RealObs;

} // end of namespace util

#endif
