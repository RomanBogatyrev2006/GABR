#include "application.h"
#include <time/timer.h>
#include <time/fpslimit.h>
#include <SDL3/SDL.h>

namespace Gabr
{
	Application* Application::sInstance = nullptr;

	// Constructor
	Application::Application(int width, int height)
		: mWindow(width, height, GABR_DEFAULT_APPNAME),
		  mRenderer(mWindow),
		  mSceneManager(&mEntManager),
		  mAudioManager()
	{
		sInstance = this;
		Timer::Init();
		//mRenderer.LoadTexture("CORELOADING", "coredata/loading.png");
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
		bRunning = true;

		while (bRunning)
		{
			FPSLimiter::BeginFrame();

			Input::BeginFrame();

			// Engine timer tick
			Timer::Tick();

			//Logger::Get().Log(LogSeverity::TRACE, std::to_string(x)+ std::to_string(y));

			//loadingBlink++;
			//if (loadingBlink > 4) { loadingBlink = 0; }

			mSceneManager.Update((float)Timer::DeltaTime());

			ClientUpdate(Timer::DeltaTime());

			ProcessEvents();

			ClientInput();

			Render();

			mAudioManager.Update();

			//FPSLimiter::SetEnabled(false);
			//FPSLimiter::SetLimit(30);
			FPSLimiter::EndFrame();
		}
	}

	void Application::ProcessEvents()
	{
		SDL_Event events;
		while (SDL_PollEvent(&events))
		{
			if (events.type == SDL_EVENT_QUIT) bRunning = false;
			Input::ProcessEvent(events);
		}
	}

	void Application::Render()
	{
		mRenderer.Clear(0.1f, 0.1f, 0.1f);

		mSceneManager.Render(&mRenderer);

		ClientRender();

		//if (loadingBlink < 4)
		//{
		//	mRenderer.DrawTexture("CORELOADING", {0, 480 - 32}, {1,1}, 0.0f, false, false, {0,0}, true);
		//}

		mRenderer.Present();
	}
}