#pragma once

#ifdef ENGH_DEBUG

#define __DEBUG_BODY(...) do { __VA_ARGS__ } while(0)

#ifdef WIN32

#include <Windows.h>

#define BREAK() __DEBUG_BODY(\
    DebugBreak();\
)

#else // !WIN32

#include <csignal>

#define BREAK() __DEBUG_BODY(\
    raise(SIGTRAP);\
)

#endif

#else

#define BREAK() (void)0

#endif