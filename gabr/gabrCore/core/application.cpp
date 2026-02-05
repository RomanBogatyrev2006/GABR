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
		
		// Initialize rendering manager
		mRenderer = std::unique_ptr<RenderingManager>(new RenderingManager(640, 360));

		//Sprite* testSpr = mRenderer->CreateSprite(0.0f, 0.0f, "", 1.0f, 1.0f, 0.0f);
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

			// Rendering manager update
			if (mRenderer->IsRunning())
			{
				mRenderer->Update();
			}
			else // If window was closed
			{
				bRunning = false;
			}

			//FPSLimiter::SetEnabled(!mRenderer->IsVsync());
			FPSLimiter::EndFrame();
		}
	}
}