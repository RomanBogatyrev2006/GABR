#pragma once
#include <log/logger.h>
#include <memory>

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


		// Instance
		static Application* sInstance;
	};

	Application* Create();
}