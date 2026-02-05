#include "renderingManager.h"
#include <log/logger.h>
#include <bgfx/bgfx.h>

namespace Gabr
{
	// Constructor
	RenderingManager::RenderingManager(unsigned int width, unsigned int height)
		:mWidth(width), mHeight(height)
	{
		if (!Initialize()) return;
	}

	// Destructor
	RenderingManager::~RenderingManager()
	{
		Deinitialize();
	}

	// Create sprite object
	Sprite* RenderingManager::CreateSprite(float x, float y, const std::string& textureTag, float scaleX, float scaleY, float angle)
	{
		mSprites.emplace_back();
		Sprite& spr = mSprites.back();
		spr.SetLocation(x, y);
		spr.SetScale(scaleX, scaleY);
		spr.SetAngle(angle);

		return &spr;
	}

	// Destroy sprite object
	void RenderingManager::DestroySprite(Sprite* sprite)
	{
		auto it = std::find_if(mSprites.begin(), mSprites.end(),
			[&](Sprite& s)
		{
				return &s == sprite;
		});
		if (it != mSprites.end()) { mSprites.erase(it); }
	}

	// Create window and initialize renderer
	bool RenderingManager::Initialize()
	{
		// Initialize SDL
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			Logger::Get().Log(LogSeverity::FATAL, "Couldn't initialize SDL: " + std::string(SDL_GetError()));
			return false;
		}
		
		// Create SDL window
		mWindow = SDL_CreateWindow("GABR", mWidth, mHeight, 0);

		// Prepare BGFX
		bgfx::Init bgfxInit;
		bgfxInit.resolution.width = mWidth;
		bgfxInit.resolution.height = mHeight;
		bgfxInit.platformData.nwh = SDL_GetPointerProperty(SDL_GetWindowProperties(mWindow), SDL_PROP_WINDOW_WIN32_HWND_POINTER, nullptr);

		// Initialize BGFX
		if (!bgfx::init(bgfxInit))
		{
			Logger::Get().Log(LogSeverity::FATAL, "Couldn't initialize BGFX!");
			return false;
		}

		bRunning = true;
		bInitialized = true;
		return true;
	}

	// Clear/Destroy all sprites
	void RenderingManager::ClearSprites()
	{
		//for (auto it = mSprites.begin(); it != mSprites.end();)
		//{
		//	it = mSprites.erase(it);
		//}
		mSprites.clear();
	}

	// Deinitialize renderer and rendering manager
	void RenderingManager::Deinitialize()
	{
		if (!bInitialized) return;

		bRunning = false;

		// A CRUTCH SOLUTION: But it seems like it should be...
		bgfx::frame();
		bgfx::frame();
		bgfx::frame();

		// Destroy all sprites
		ClearSprites();

		// Deinitialize BGFX
		bgfx::shutdown();
		
		// Destroy SDL window
		if (mWindow)
		{
			SDL_DestroyWindow(mWindow);
			mWindow = nullptr;
		}

		// Deinitialize SDL
		SDL_Quit();

		bInitialized = false;
	}

	// Update renderer and rendering manager
	void RenderingManager::Update()
	{
		while (SDL_PollEvent(&mEvents))
		{
			switch (mEvents.type)
			{
			case SDL_EVENT_QUIT:
				bRunning = false;
				break;
			}
		}

		// !Rendering!

		// Set viewport rect
		bgfx::setViewRect(0, 0, 0, mWidth, mHeight);

		// Set clear color
		bgfx::setViewClear(0, BGFX_CLEAR_COLOR, 0x873E3EFF);
		bgfx::touch(0);

		for (int i = 0; i < mSprites.size(); i++)
		{
			if (mSprites[i].IsVisible()) { mSprites[i].Render(); }
		}

		bgfx::frame();
	}
}