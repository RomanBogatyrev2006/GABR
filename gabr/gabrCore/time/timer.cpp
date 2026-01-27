#include "timer.h"
#include <thread>

// Windows specific
#ifdef GABR_TARGET_WIN
	#include <Windows.h>
	#pragma comment(lib, "winmm.lib")
#endif

namespace Gabr
{
	// Initialize
	void Timer::Init()
	{
		// Windows specific mess
		#ifdef GABR_TARGET_WIN
			timeBeginPeriod(1);
		#endif

		sStartTime = clock::now();
		sLastFrame = sStartTime;

		sDeltaTime = 0.0;
		sFrameCounter = 0;
		sFPS = 0;
		sFPSTimer = 0.0;
	}

	// Tick timer
	void Timer::Tick()
	{
		clock::time_point now = clock::now();

		// Delta time
		sDeltaTime = std::chrono::duration<double>(now - sLastFrame).count();
		sLastFrame = now;

		// FPS calculation
		sFrameCounter++;
		sFPSTimer += sDeltaTime;

		if (sFPSTimer >= 1.0)
		{
			sFPS = sFrameCounter;
			sFrameCounter = 0;
			sFPSTimer -= 1.0;
		}
	}

	// Deinitialize
	void Timer::Shutdown()
	{
		// Windows specific mess
		#ifdef GABR_TARGET_WIN
			timeEndPeriod(1);
		#endif
	}

	// Get engine time
	double Timer::GetTime()
	{
		return std::chrono::duration<double>(clock::now() - sStartTime).count();
	}

	// Get delta time
	double Timer::DeltaTime() { return sDeltaTime; }

	// Get current FPS (Frames per second)
	uint32_t Timer::GetFPS() { return sFPS; }

	// Get current frame time (ms per frame)
	double Timer::GetFrameTime()
	{
		return sFPS > 0 ? (1000.0 / static_cast<double>(sFPS)) : 0.0;
	}
}
