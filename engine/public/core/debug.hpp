#pragma once

namespace ENGH::Debug {

inline void __BREAK();

#ifdef ENGH_DEBUG

#define BREAK() __BREAK()

#else

#define BREAK() (void)0

#endif

}