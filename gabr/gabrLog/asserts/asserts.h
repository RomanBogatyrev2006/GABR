#pragma once
#include <iostream>

// Auto-define
#ifdef _DEBUG
	#define	GABR_ASSERT_ENABLE
#endif

#ifdef GABR_ASSERT_ENABLE
	#define GABR_ASSERT(x, ...) { if(!(x)) {std::cerr << "ASSERTION FAILED: " << __VA_ARGS__ << std::endl; __debugbreak();} }
#else
	#define GABR_ASSERT(x, ...)
#endif
