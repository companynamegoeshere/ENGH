#include <core/debug.hpp>

#ifdef WIN32

#else // !WIN32

#include <csignal>

#endif

inline void ENGH::Debug::Break() {
#ifdef ENGH_DEBUG
#ifdef WIN32
  __debugbreak();
#else
  raise(SIGTRAP);
#endif
#endif
}

// TODO Add assert macros
