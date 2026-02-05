#pragma once
#include <log/logger.h>
#include <memory>
#include <rendering/renderingManager.h>

namespace Gabr
{
	class GABR_API Application
	{
	public:
		// Constructor
		Application();

		// Destructor
		virtual ~Application();


		// Run application
		void Run();
	private:
		// Is application running?
		bool bRunning = false;

		// Renderer
		std::unique_ptr<RenderingManager> mRenderer;

		// Instance
		static Application* sInstance;
	};

	Application* Create();
}