#pragma once

#include <api.h>
#include <SDL3/SDL.h>

namespace Gabr
{
	class GABR_API Window
	{
	public:
		// Constructor
		Window(unsigned int width, unsigned int height, std::string title = "GABR");
		
		// Destructor
		~Window();

		// Get SDL window
		SDL_Window* GetSDLWindow() const;

	private:
		SDL_Window* mWindow;
	};
}