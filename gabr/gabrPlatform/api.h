#pragma once

// Windows
#if defined(GABR_TARGET_WIN)
	#ifdef GABR_BUILD
		#define GABR_API __declspec(dllexport)
	#else
		#define GABR_API __declspec(dllimport)
	#endif
// Linux
#elif defined(GABR_TARGET_LINUX)
	#ifdef GABR_BUILD
		#define GABR_API __attribute__((visibility("default")))
	#else
		#define GABR_API
	#endif
// Undefined
#else
	#error "GABR supports only Windows (x64) and Linux (Not now)"
#endif