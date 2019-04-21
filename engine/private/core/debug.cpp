#include <core/debug.hpp>

#ifdef WIN32

#include <Windows.h>

#else // !WIN32

#include <csignal>

#endif

inline void ENGH::Debug::__BREAK() {
#ifdef WIN32
	DebugBreak();
#else
	raise(SIGTRAP);
#endif
}
