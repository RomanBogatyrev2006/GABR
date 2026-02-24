#pragma once

#include <api.h>
#include <bgfx/bgfx.h>

namespace Gabr
{
	class GABR_API Texture
	{
	public:
		// Constructor
		Texture(const char* filename);
		Texture(void* data, uint16_t width, uint16_t height);
		
		// Destructor
		~Texture();


		// Get texture handle
		bgfx::TextureHandle GetHandle() { return mTextureHandle; }

	private:
		// Texture handle
		bgfx::TextureHandle mTextureHandle;
	};
}