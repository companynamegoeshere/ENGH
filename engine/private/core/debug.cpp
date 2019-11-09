#include <core/debug.hpp>

#ifdef WIN32

#include <debugapi.h>

#else // !WIN32

#include <csignal>

#endif

inline void ENGH::Debug::Break() {
#ifdef ENGH_DEBUG
#ifdef WIN32
  DebugBreak();
#else
  raise(SIGTRAP);
#endif
#endif
}

// TODO Add assert macros
