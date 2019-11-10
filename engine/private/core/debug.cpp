#include <core/debug.hpp>

#if defined(WIN32) || defined(_MSC_VER)

#else // !WIN32

#include <csignal>

#endif

void ENGH::Debug::Break() {
#ifdef ENGH_DEBUG
#if defined(WIN32) || defined(_MSC_VER)

#ifdef _MSC_VER
  __debugbreak();
#else
  __builtin_trap();
#endif

#else
  raise(SIGTRAP);
#endif

#endif
}

// TODO Add assert macros
