#include "application.h"
#include "core.h"
#include <time/timer.h>
#include <time/fpslimit.h>

namespace Gabr
{
	Application* Application::sInstance = nullptr;

	// Constructor
	Application::Application()
	{
		sInstance = this;

		Logger::Get().Log(LogSeverity::TRACE, "Engine initialized!");

	}

	// Destructor
	Application::~Application()
	{
		Timer::Shutdown();
		Logger::Get().Log(LogSeverity::TRACE, "Engine terminated!");
	}

	// Run application
	void Application::Run()
	{
		Timer::Init();
		bRunning = true;
		while (bRunning)
		{
			FPSLimiter::BeginFrame();

			// Engine timer tick
			Timer::Tick();

			//FPSLimiter::SetEnabled(!mRenderer->IsVsync());
			FPSLimiter::EndFrame();
		}
	}
}