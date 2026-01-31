#pragma once

#include <api.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include "sprite.h"
#include "texture.h"

namespace Gabr
{
	class GABR_API RenderingManager
	{
	public:
		bool Initialize();

		void Deinitialize();

		void Update();


		// --Textures managing--

		// Load texture from file (path to file)
		bool LoadTexture(const std::string& file, const std::string& tag);

		// Unload texture
		void UnloadTexture(const std::string& tag);

		// Get texture by tag
		void GetTexture(const std::string& tag);


		// --Sprites managing--

		// Create sprite object
		Sprite* CreateSprite(float x = 0.0f, float y = 0.0f, const std::string& textureTag = "", float scaleX = 1.0f, float scaleY = 1.0f, float angle = 0.0f);

		// Destroy sprite object
		void DestroySprite(Sprite* sprite);


	private:
		// Storage of texture
		std::vector<std::string, Texture> mTextures = {};

		// Storage of sprites
		std::vector<Sprite> mSprites = {};

	};
}