#pragma once

#define SDL_MAIN_HANDLED
#include <SDL3/SDL.h>
#include <bgfx/bgfx.h>
#include <glm/glm.hpp>
#include "shader.h"
#include "texture.h"

namespace Gabr
{
	struct Vertex
	{
		glm::vec3 Position;
		uint32_t Color;
		glm::vec2 TextureCoords;
	};

	struct RenderBatch
	{
		glm::mat4 Position;
		bgfx::TextureHandle Texture;
		uint32_t StartIndex;
		uint32_t NumberOfIndices;
	};

	class GABR_API RenderingManager
	{
	public:
		// Constructor
		RenderingManager();

		// Destructor (Deinitialize/Close/Destroy/Quit)
		~RenderingManager();

		// Create window and initialize renderer
		bool Initialize(unsigned int width, unsigned int height);

		// Deinitialize renderer and rendering manager
		void Deinitialize();

		// Begin
		void Begin();

		// Update renderer and rendering manager
		void Update();


		// Is renderer running?
		inline const bool IsRunning() { return bRunning; };


		// --Drawing--

		// Draw rectangle
		void DrawRect(glm::vec2 position, float rotation, uint32_t color, glm::vec2 scale);

		// Draw texture
		void DrawTexture(Texture* texture, glm::vec2 position, float rotation, uint32_t color, glm::vec2 scale);

		// Create sprite object
		//Sprite* CreateSprite(float x = 0.0f, float y = 0.0f, const std::string& textureTag = "", float scaleX = 1.0f, float scaleY = 1.0f, float angle = 0.0f);

		// Destroy sprite object
		//void DestroySprite(Sprite* sprite);

	private:
		
		


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


		bgfx::IndexBufferHandle mIndexBuffer;
		bgfx::VertexLayout mVertexLayout;
		bgfx::DynamicVertexBufferHandle mVertexBuffer;
		bgfx::UniformHandle mUniform;
		Texture* mWhiteTexture;
		Shader* mShaderProgram;

		std::vector<Vertex> mVertices;

		std::vector<RenderBatch> mRenderBatches;

		// Projection (Camera)
		glm::vec3 mAt;
		glm::vec3 mCamera;
		glm::mat4 mView;
		glm::mat4 mProjection;
	};
}