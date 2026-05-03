#pragma once

#define SDL_MAIN_HANDLED
#include <SDL3/SDL.h>
#include <glm/gtc/type_ptr.hpp>
#include <api.h>
#include "camera.h"

namespace Gabr
{
	// Forward declarations
	class Window;
	class Texture;

	struct RenderCommand
	{
		SDL_Texture* texture;
		SDL_FRect dst;
		float rotation;
		SDL_FPoint center;
		SDL_FlipMode flip;
		float z;
	};

	class GABR_API Renderer
	{
	public:
		// Constructor
		Renderer(Window& window);

		// Destructor
		~Renderer();


		// Clear screen
		void Clear(float r, float g, float b);

		// Present (Render)
		void Present();


		// --Texture management--

		// Load texture to memory
		bool LoadTexture(const std::string& tag, const std::string& path);

		// Unload texture from memory by tag
		void UnloadTexture(const std::string& tag);

		// Unload all textures from memory
		void UnloadAllTextures();


		// --Drawing--

		// Draw rectangle
		//void DrawRect(glm::vec2 position, float rotation, uint32_t color, glm::vec2 scale);
		
		// Draw texture
		void DrawTexture(
			const std::string& tag,
			glm::vec2 position,
			glm::vec2 scale = glm::vec2{ 1, 1 },
			float rotation = 0.0f,
			bool hFlip = false,
			bool vFlip = false,
			glm::vec2 origin = glm::vec2{ 0, 0 },
			bool fixedToCamera = false,
			float z = 0.0f
		);


		// Get SDL Renderer
		SDL_Renderer* getSDLRenderer();


		// --Camera management--

		// Set camera position
		void SetCameraPosition(glm::vec2 pos);

		// Move camera
		void MoveCamera(glm::vec2 delta);

		// Set camera zoom
		void SetCameraZoom(float zoom);

		// Set camera rotation
		void SetCameraRotation(float rot);

		// Get camera
		Camera& GetCamera();

	private:
		SDL_Renderer* mRenderer = nullptr;

		struct TextureData
		{
			SDL_Texture* texture = nullptr;
			int width = 0;
			int height = 0;
		};

		std::unordered_map<std::string, TextureData> mTextures;
		std::vector<RenderCommand> mRenderQueue;

		Camera mCamera;
	};
}