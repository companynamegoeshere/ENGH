#pragma once

#include <core/log.hpp>

namespace ENGH::Debug {

void Break();

}

#ifdef ENGH_DEBUG
#define ASSERT_2(x, msg) {\
    if(!(x)){             \
      ENGH_ERROR("Assertion: failed ", #x, " at " __FILE__, "#", __LINE__, "  ", msg); \
      ::ENGH::Debug::Break(); \
    } \
  } \
  (void)0
#define ASSERT_1(msg) ASSERT_2(false, msg)
#else
#define ASSERT_2(x, msg) (void)0
#define ASSERT_1(msg) (void)0
#endif

#define _INTERNAL_EXPAND(x) x
#define _INTERNAL_GET_MACRO_NAME(_1, _2, name, ...) name
#define _INTERNAL_GET_MACRO(...) _INTERNAL_EXPAND( _INTERNAL_GET_MACRO_NAME(__VA_ARGS__, ASSERT_2, ASSERT_1) )
#define ASSERT(...) _INTERNAL_EXPAND( _INTERNAL_GET_MACRO(__VA_ARGS__)(__VA_ARGS__) )
