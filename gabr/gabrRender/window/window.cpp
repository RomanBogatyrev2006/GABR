#include "window.h"
#include <log/logger.h>

namespace Gabr
{
	Window::Window(unsigned int width, unsigned int height, std::string title)
	{
		// Initialize SDL VIDEO subsystem
		if (!SDL_Init(SDL_INIT_VIDEO))
		{
			Logger::Get().Log(LogSeverity::FATAL, "Couldn't initialize SDL VIDEO: " + std::string(SDL_GetError()));
			return;
		}

		// Create SDL window
		mWindow = SDL_CreateWindow(title.c_str(), width, height, NULL);
		if (!mWindow)
		{
			Logger::Get().Log(LogSeverity::FATAL, "Couldn't create window: " + std::string(SDL_GetError()));
			return;
		}

		Logger::Get().Log(LogSeverity::TRACE, "Window created!");
	}

	Window::~Window()
	{
		if (mWindow) { SDL_DestroyWindow(mWindow); }

		SDL_Quit();
	}

	SDL_Window* Window::GetSDLWindow() const
	{
		return mWindow;
	}
}