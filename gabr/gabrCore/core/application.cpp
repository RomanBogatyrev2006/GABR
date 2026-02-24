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
		//mRenderer = std::unique_ptr<RenderingManager>(new RenderingManager(640, 360));
		mRenderer.Initialize(GABR_DEFAULT_WIDTH, GABR_DEFAULT_HEIGHT);

		//Sprite* testSpr = mRenderer->CreateSprite(0.0f, 0.0f, "", 1.0f, 1.0f, 0.0f);
		tex = new Texture("PP.png");
	}

	// Destructor
	Application::~Application()
	{
		Timer::Shutdown();
		Logger::Get().Log(LogSeverity::TRACE, "Engine terminated!");
		delete tex;
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
			if (mRenderer.IsRunning())
			{
				mRenderer.Begin();
				
				mRenderer.DrawRect({ 64.0f, 0.0f }, 0.0f, 0xff00ffff, {1.3f, 1.3f});
				//mRenderer.DrawTexture(tex, { -32.0f, -60.0f }, rotation, 0xffffffff, { 1.3f, 1.3f });
				mRenderer.Update();
				rotation += Timer::DeltaTime();
				rotation = std::fmod(rotation, 360.0f);
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