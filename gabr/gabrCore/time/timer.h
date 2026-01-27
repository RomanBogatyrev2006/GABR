#pragma once
#include <chrono>
#include <api.h>

namespace Gabr
{
	class GABR_API Timer
	{
	public:
		using clock = std::chrono::steady_clock;

		// --Main--

		// Initialize
		static void Init();

		// Tick timer
		static void Tick();

		// Deinitialize
		static void Shutdown();


		// --Time--

		// Get engine time
		static double GetTime();

		// Get DeltaTime
		static double DeltaTime();


		// --FPS--

		// Get current FPS (Frames per second)
		static uint32_t GetFPS();

		// Get current frame time (ms per frame)
		static double GetFrameTime();

	private:
		// Timer

		static inline clock::time_point sStartTime;
		static inline clock::time_point sLastFrame;
		static inline double sDeltaTime = 0.0;


		// FPS

		static inline uint32_t sFrameCounter = 0;
		static inline uint32_t sFPS = 0;
		static inline double sFPSTimer = 0.0;
	};
}
