#include "renderer.h"
#include <log/logger.h>
#include <glm/glm.hpp>
#include <window/window.h>

// STB Image
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Gabr
{
	// Constructor
	Renderer::Renderer(Window& window)
	{
		mRenderer = SDL_CreateRenderer(
			window.GetSDLWindow(),
			nullptr
		);
	}

	// Destructor
	Renderer::~Renderer()
	{
		UnloadAllTextures();
		if (mRenderer) { SDL_DestroyRenderer(mRenderer); }
	}

	// Clear screen
	void Renderer::Clear(float r, float g, float b)
	{
		//SDL_SetRenderDrawColor(
		//	mRenderer,
		//	(uint8_t)(r * 255),
		//	(uint8_t)(g * 255),
		//	(uint8_t)(b * 255),
		//	255
		//);
		//
		//SDL_RenderClear(mRenderer);
	}

	// Present (Render)
	void Renderer::Present()
	{
		SDL_RenderPresent(mRenderer);
	}

	// Load texture to memory
	bool Renderer::LoadTexture(const std::string& tag, const std::string& path)
	{
		UnloadTexture(tag);

		int width, height, channels;
		unsigned char* pixels = stbi_load
		(
			path.c_str(),
			&width,
			&height,
			&channels,
			4
		);

		if (!pixels)
		{
			Logger::Get().Log(LogSeverity::TRACE, "Failed to load texture: " + path);
			return false;
		}

		SDL_Texture* texture = SDL_CreateTexture
		(
			mRenderer,
			SDL_PIXELFORMAT_RGBA32,
			SDL_TEXTUREACCESS_STATIC,
			width,
			height
		);

		SDL_UpdateTexture(texture, nullptr, pixels, width * 4);
		SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

		stbi_image_free(pixels);

		mTextures[tag] = { texture, width, height };
		Logger::Get().Log(LogSeverity::TRACE, "Texture loaded: " + tag);
		return true;
	}

	// Unload texture from memory by tag
	void Renderer::UnloadTexture(const std::string& tag)
	{
		auto it = mTextures.find(tag);
		if (it != mTextures.end())
		{
			if (it->second.texture) { SDL_DestroyTexture(it->second.texture); }
			mTextures.erase(it);
		}
	}

	// Unload all textures from memory
	void Renderer::UnloadAllTextures()
	{
		for (auto& [tag, tex] : mTextures)
		{
			if (tex.texture) { SDL_DestroyTexture(tex.texture); }
		}
		mTextures.clear();
	}

	// Draw texture
	void Renderer::DrawTexture(const std::string& tag, glm::vec2 position, glm::vec2 scale, float rotation, bool hFlip, bool vFlip, glm::vec2 origin, bool fixedToCamera)
	{
		auto it = mTextures.find(tag);
		if (it == mTextures.end()) return;

		SDL_Texture* tex = it->second.texture;

		int width = it->second.width;
		int height = it->second.height;

		glm::vec2 camPos = mCamera.position;
		glm::vec2 finalPos = (position - camPos);
		finalPos *= mCamera.zoom;

		SDL_FRect dst;
		
		if (!fixedToCamera)
		{
			dst.w = width * scale.x * mCamera.zoom;
			dst.h = height * scale.y * mCamera.zoom;
		}
		else
		{
			dst.w = width * scale.x;
			dst.h = height * scale.y;
		}

		SDL_FPoint center = {0, 0};

		if (!fixedToCamera)
		{
			dst.x = finalPos.x - origin.x * mCamera.zoom;
			dst.y = finalPos.y - origin.y * mCamera.zoom;
		}
		else
		{
			dst.x = position.x - origin.x;
			dst.y = position.y - origin.y;
		}

		static SDL_FlipMode flip;
		
		if		(!hFlip && !vFlip)	{ flip = SDL_FLIP_NONE; }
		else if (!hFlip && vFlip)	{ flip = SDL_FLIP_VERTICAL; }
		else if (hFlip && !vFlip)	{ flip = SDL_FLIP_HORIZONTAL; }
		else if (hFlip && vFlip)	{ flip = SDL_FLIP_HORIZONTAL_AND_VERTICAL; }

		SDL_RenderTextureRotated(
			mRenderer,
			tex,
			nullptr,
			&dst,
			fixedToCamera ? rotation - mCamera.rotation : rotation,
			&center,
			flip
		);
	}

	// Get SDL Renderer
	SDL_Renderer* Renderer::getSDLRenderer()
	{
		return mRenderer;
	}

	// Set camera position
	void Renderer::SetCameraPosition(glm::vec2 pos)
	{
		mCamera.position = glm::clamp(pos, mCamera.minBounds, mCamera.maxBounds);
	}

	// Move camera
	void Renderer::MoveCamera(glm::vec2 delta)
	{
		SetCameraPosition(mCamera.position + delta);
	}

	// Set camera zoom
	void Renderer::SetCameraZoom(float zoom)
	{
		mCamera.zoom = zoom;
	}

	// Set camera rotation
	void Renderer::SetCameraRotation(float rot)
	{
		mCamera.rotation = rot;
	}

	// Get camera
	Camera& Renderer::GetCamera()
	{
		return mCamera;
	}


}