/**
 * debug_dump.hpp
 *
 * Debug print utility.
 * 
 * Copyright (c) 2013 by Yuichi Motoyama <yomichi@tsg.jp>
 *
 * Distributed under the Boost Software License version 1.0.
 * (See acompanied file License.txt or http://www.boost.org/LICENSE_1_0.txt)
 *
 */


#ifndef DEBUG_DUMP_HPP
#define DEBUG_DUMP_HPP

#include <iostream>
#include <boost/preprocessor/repetition.hpp>
#include <boost/preprocessor/iteration/local.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>

#define DD_ARG_MAX 25

#define DD_arg(z,n,unused) BOOST_PP_COMMA_IF(n) T##n const& v##n
#define DD_body(z,n,unused) << v##n

#ifndef NDEBUG
#define DD_dump(z,n,unused) \
template <BOOST_PP_ENUM_PARAMS(n, class T)> \
inline void debug_dump( BOOST_PP_REPEAT(n, DD_arg, ~) )\
{ std::cerr \
    BOOST_PP_REPEAT(n, DD_body, ~) \
  << std::endl; }
#else
#define DD_dump(z,n,unused) \
template <BOOST_PP_ENUM_PARAMS(n, class T)> \
inline void debug_dump( BOOST_PP_REPEAT(n, DD_arg, ~) ){ }
#endif
      
#ifndef NDEBUG
#define DD_dump_if(z,n,unused) \
template <BOOST_PP_ENUM_PARAMS(n, class T)> \
inline void debug_dump_if(bool cond, BOOST_PP_REPEAT(n, DD_arg, ~) )\
{ if(cond)\
  std::cerr \
  BOOST_PP_REPEAT(n, DD_body, ~) \
  << std::endl; }
#else
#define DD_dump_if(z,n,unused) \
template <BOOST_PP_ENUM_PARAMS(n, class T)> \
inline void debug_dump_if(bool cond, BOOST_PP_REPEAT(n, DD_arg, ~) ){ }
#endif

#ifndef NDEBUG
#define DD_stream(z,n,unused) \
template <class OSTREAM, BOOST_PP_ENUM_PARAMS(n, class T)> \
inline void debug_stream(OSTREAM &os, BOOST_PP_REPEAT(n, DD_arg, ~) )\
{ os \
  BOOST_PP_REPEAT(n, DD_body, ~) \
  << std::endl; }
#else
#define DD_stream(z,n,unused) \
template <class OSTREAM, BOOST_PP_ENUM_PARAMS(n, class T)> \
inline void debug_stream(OSTREAM &os, BOOST_PP_REPEAT(n, DD_arg, ~) ){ }
#endif

#ifndef NDEBUG
#define DD_stream_if(z,n,unused) \
template <class OSTREAM, BOOST_PP_ENUM_PARAMS(n, class T)> \
inline void debug_stream_if(bool cond, OSTREAM &os, BOOST_PP_REPEAT(n, DD_arg, ~))\
{ if(cond) os \
  BOOST_PP_REPEAT(n, DD_body, ~) \
  << std::endl; }
#else
#define DD_stream_if(z,n,unused) \
template <class OSTREAM, BOOST_PP_ENUM_PARAMS(n, class T)> \
inline void debug_stream_if(bool cond, OSTREAM &os, BOOST_PP_REPEAT(n, DD_arg, ~) ){ }
#endif


#define BOOST_PP_LOCAL_MACRO(n) DD_dump(~,n,~)
#define BOOST_PP_LOCAL_LIMITS (1, DD_ARG_MAX+1)
#include BOOST_PP_LOCAL_ITERATE()
#undef BOOST_PP_LOCAL_LIMITS
#undef BOOST_PP_LOCAL_MACRO

#define BOOST_PP_LOCAL_MACRO(n) DD_dump_if(~,n,~)
#define BOOST_PP_LOCAL_LIMITS (1, DD_ARG_MAX+1)
#include BOOST_PP_LOCAL_ITERATE()
#undef BOOST_PP_LOCAL_LIMITS
#undef BOOST_PP_LOCAL_MACRO

#define BOOST_PP_LOCAL_MACRO(n) DD_stream(~,n,~)
#define BOOST_PP_LOCAL_LIMITS (1, DD_ARG_MAX+1)
#include BOOST_PP_LOCAL_ITERATE()
#undef BOOST_PP_LOCAL_LIMITS
#undef BOOST_PP_LOCAL_MACRO

#define BOOST_PP_LOCAL_MACRO(n) DD_stream_if(~,n,~)
#define BOOST_PP_LOCAL_LIMITS (1, DD_ARG_MAX+1)
#include BOOST_PP_LOCAL_ITERATE()
#undef BOOST_PP_LOCAL_LIMITS
#undef BOOST_PP_LOCAL_MACRO

#undef DD_arg
#undef DD_body
#undef DD_dump
#undef DD_dump_if
#undef DD_stream
#undef DD_stream_if
#undef DD_ARG_MAX

#endif // DEBUG_DUMP_HPP
