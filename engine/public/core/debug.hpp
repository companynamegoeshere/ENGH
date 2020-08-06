#pragma once


namespace ENGH::Debug {

void Break();

}

#ifdef ENGH_DEBUG
#define ASSERT(x, msg) (void)((x) || (ENGH_ERROR("Assertion: failed ", #x, " at " __FILE__, "#", __LINE__), ::ENGH::Debug::Break(), true))
#else
#define ASSERT(x) (void)0
#endif
