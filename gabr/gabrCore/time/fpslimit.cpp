#include "fpslimit.h"
#include <thread>

namespace Gabr
{
	// On begin frame
	void FPSLimiter::BeginFrame()
	{
		if (sNextFrameTime.time_since_epoch().count() == 0)
			sNextFrameTime = clock::now();
	}

	// On end frame
	void FPSLimiter::EndFrame()
	{
		if (!sEnabled || sTargetFPS <= 0) return;

		const clock::duration frameDuration = std::chrono::duration_cast<clock::duration>
			(std::chrono::duration<double>(1.0 / static_cast<double>(sTargetFPS)));

		clock::time_point now = clock::now();

		if (now > sNextFrameTime + frameDuration)
			sNextFrameTime = now;

		sNextFrameTime += frameDuration;

		if (now + std::chrono::microseconds(200) < sNextFrameTime)
		{
			std::this_thread::sleep_until(sNextFrameTime - std::chrono::microseconds(100));
		}

		while (clock::now() < sNextFrameTime) {}
	}

	// Set FPS Limit (0 = unlimited)
	void FPSLimiter::SetLimit(int fps)
	{
		sTargetFPS = fps > 0 ? fps : 0;
	}

	// Enable/Disable limit
	void FPSLimiter::SetEnabled(bool enabled)
	{
		sEnabled = enabled;
	}
}
