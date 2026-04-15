#pragma once
#include <log/logger.h>
#include <memory>
#include <window/window.h>
#include <rendering/renderer.h>
#include <input/input.h>
#include "core.h"

namespace Gabr
{
	class GABR_API Application
	{
	public:
		// Constructor
		Application(int width = GABR_DEFAULT_WIDTH, int height = GABR_DEFAULT_HEIGHT);

		// Destructor
		virtual ~Application();


		// --Client--

		// Client update
		virtual void ClientUpdate(double deltaTime) {}

		// Client rendering
		virtual void ClientRender() {}

		// Client input handling
		virtual void ClientInput() {}


		// --Getters--

		// Get application's renderer
		Renderer* GetRenderer() { return &mRenderer; }

		// 



		// Run application
		void Run();
	private:
		void ProcessEvents();
		void Render();

		// Is application running?
		bool bRunning = false;

		// Window
		Window mWindow;

		// Renderer
		Renderer mRenderer;

		// Instance
		static Application* sInstance;

		int loadingBlink = 0;
	};

	Application* Create();
}