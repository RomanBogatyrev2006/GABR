#pragma once

//#include <bgfx/bgfx.h>
//#include <bgfx/platform.h>
#define SDL_MAIN_HANDLED
#include <SDL3/SDL.h>
#include "sprite.h"
#include "texture.h"
#include <deque>

namespace Gabr
{
	class GABR_API RenderingManager
	{
	public:
		// Constructor
		RenderingManager(unsigned int width, unsigned int height);

		// Destructor (Deinitialize/Close/Destroy/Quit)
		~RenderingManager();

		// Update renderer and rendering manager
		void Update();


		// Is renderer running?
		inline const bool IsRunning() { return bRunning; };

		/*
		// --Textures managing--

		// Load texture from file (path to file)
		bool LoadTexture(const std::string& file, const std::string& tag);

		// Unload texture
		void UnloadTexture(const std::string& tag);

		// Get texture by tag
		void GetTexture(const std::string& tag);

		*/
		// --Sprites managing--

		// Create sprite object
		Sprite* CreateSprite(float x = 0.0f, float y = 0.0f, const std::string& textureTag = "", float scaleX = 1.0f, float scaleY = 1.0f, float angle = 0.0f);

		// Destroy sprite object
		void DestroySprite(Sprite* sprite);

	private:
		// Create window and initialize renderer
		bool Initialize();
		
		// Deinitialize renderer and rendering manager
		void Deinitialize();

		// Clear/Destroy all sprites
		void ClearSprites();
		


		// --Window--

		// SDL Window
		SDL_Window* mWindow;

		// Window Width and Height
		unsigned int mWidth, mHeight;


		// SDL Events
		SDL_Event mEvents;


		// Is running
		bool bRunning = false;

		// Is initialized
		bool bInitialized = false;


		// Storage of texture
		//std::vector<std::string, Texture> mTextures = {};

		// Storage of sprites
		std::deque<Sprite> mSprites = {};
	};
}