#pragma once
#include <chrono>
#include <api.h>

namespace Gabr
{
	class GABR_API FPSLimiter
	{
	public:
		// On begin frame
		static void BeginFrame();

		// On end frame
		static void EndFrame();


		// --Control--

		// Set FPS Limit (0 = unlimited)
		static void SetLimit(int fps);

		// Enable/Disable limit
		static void SetEnabled(bool enabled);

	private:
		using clock = std::chrono::steady_clock;

		static inline bool sEnabled = false;
		static inline int sTargetFPS = 60;
		static inline clock::time_point sNextFrameTime{};
	};
}
