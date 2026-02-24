#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <log/logger.h>

namespace Gabr
{
	// Constructor
	Texture::Texture(const char* filename)
	{
		int32_t width, height;
		uint8_t* data = stbi_load(filename, &width, &height, nullptr, STBI_rgb_alpha);

		mTextureHandle = bgfx::createTexture2D(
			(uint16_t)width,
			(uint16_t)height,
			false,
			1,
			bgfx::TextureFormat::Enum::RGBA8,
			BGFX_SAMPLER_NONE | BGFX_SAMPLER_UVW_CLAMP,
			bgfx::copy(data, width * height * 4)
		);

		delete data;

		if (!bgfx::isValid(mTextureHandle))
		{
			Logger::Get().Log(LogSeverity::ERR, "Unable to create texture");
		}
	}

	Texture::Texture(void* data, uint16_t width, uint16_t height)
	{
		mTextureHandle = bgfx::createTexture2D(
			(uint16_t)width,
			(uint16_t)height,
			false,
			1,
			bgfx::TextureFormat::Enum::RGBA8,
			BGFX_SAMPLER_NONE | BGFX_SAMPLER_UVW_CLAMP,
			bgfx::copy(data, width * height * 4)
		);

		if (!bgfx::isValid(mTextureHandle))
		{
			Logger::Get().Log(LogSeverity::ERR, "Unable to create texture");
		}
	}

	// Destructor
	Texture::~Texture()
	{
		bgfx::destroy(mTextureHandle);
	}
}