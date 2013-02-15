/**
 * pow2.hpp
 * 
 * Copyright (c) 2013 by Yuichi Motoyama <yomichi@tsg.jp>
 *
 * Distributed under the Boost Software License version 1.0.
 * (See acompanied file License.txt or http://www.boost.org/LICENSE_1_0.txt)
 *
 */

#ifndef POW2_HPP
#define POW2_HPP

namespace util{

template <class T>
inline T pow2(T const &val){ return val*val;}
template <class T>
inline T pow3(T const &val){ return val*val*val;}
template <class T>
inline T pow4(T const &val){ return pow2(val*val);}

}

#endif
