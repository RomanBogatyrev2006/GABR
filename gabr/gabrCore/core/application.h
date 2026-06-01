#pragma once
#include <log/logger.h>
#include <memory>
#include <window/window.h>
#include <rendering/renderer.h>
#include <input/input.h>
#include <entity/entityManager.h>
#include <scenes/sceneManager.h>
#include <audio/audioManager.h>
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

		// Get application's entity manager
		EntityManager* GetEntityManager() { return &mEntManager; }

		// Get application's scene manager
		SceneManager* GetSceneManager() { return &mSceneManager; }

		// Get application's audio manager
		AudioManager* GetAudioManager() { return &mAudioManager; }


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

		// Entity manager
		EntityManager mEntManager;

		// Scene manager
		SceneManager mSceneManager;

		// Audio manager
		AudioManager mAudioManager;

		// Instance
		static Application* sInstance;

		int loadingBlink = 0;
	};

	Application* Create();
}