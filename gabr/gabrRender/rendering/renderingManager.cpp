#include "renderingManager.h"
#include <log/logger.h>
#include <glm/gtc/type_ptr.hpp>

namespace Gabr
{
	// Constructor
	RenderingManager::RenderingManager()
	{
		//if (!Initialize()) return;
	}

	// Destructor
	RenderingManager::~RenderingManager()
	{
		Deinitialize();
	}
	
	// Create window and initialize renderer
	bool RenderingManager::Initialize(unsigned int width, unsigned int height)
	{
		mWidth = width;
		mHeight = height;
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

		std::vector<uint16_t> indices;
		for (uint32_t index = 0; index < 100; index++)
		{
			indices.push_back(4 * index + 3);
			indices.push_back(4 * index + 2);
			indices.push_back(4 * index + 0);

			indices.push_back(4 * index + 2);
			indices.push_back(4 * index + 1);
			indices.push_back(4 * index + 0);
		}

		mIndexBuffer = bgfx::createIndexBuffer(bgfx::copy(indices.data(), indices.size() * 2));
		if (!bgfx::isValid(mIndexBuffer))
		{
			Logger::Get().Log(LogSeverity::FATAL, "Couldn't create index buffer");
		}

		mVertexLayout.begin()
			.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
			.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
			.end();

		mVertexBuffer = bgfx::createDynamicVertexBuffer(bgfx::makeRef(mVertices.data(), sizeof(Vertex) * mVertices.size()), mVertexLayout);
		if (!bgfx::isValid(mVertexBuffer))
		{
			Logger::Get().Log(LogSeverity::FATAL, "Couldn't create vertex buffer");
		}

		mUniform = bgfx::createUniform("textureColor", bgfx::UniformType::Sampler);
		if (!bgfx::isValid(mUniform))
		{
			Logger::Get().Log(LogSeverity::FATAL, "Couldn't create uniform");
		}

		uint32_t white = 0xFFFFFFFF;
		mWhiteTexture = new Texture(&white, 1, 1);
		mShaderProgram = new Shader("vertex.bin", "frag.bin");

		mCamera = { 0.0f, 0.0f, -1.0f };
		mAt = { 0.0f, 0.0f, 0.0f };
		mView = glm::lookAt(mCamera, mAt, { 0.0f, 0.0f, 1.0f });
		mProjection = glm::ortho(-mWidth / 2.0f, mWidth / 2.0f, mHeight / 2.0f, -mHeight / 2.0f, -1000.0f, 1000.0f);

		bRunning = true;
		bInitialized = true;
		return true;
	}

	void RenderingManager::Begin()
	{
		bgfx::reset(mWidth, mHeight, BGFX_RESET_VSYNC);

		mVertices.clear();
		mRenderBatches.clear();

		// Set viewport rect
		bgfx::setViewRect(0, 0, 0, mWidth, mHeight);
		// Set some states (Mostly just for alpha)
		//bgfx::setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_BLEND_ALPHA);

		// Set clear color
		bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH | BGFX_CLEAR_STENCIL, 0x873E3EFF);
		bgfx::setViewTransform(0, glm::value_ptr(mView), glm::value_ptr(mProjection));

		bgfx::touch(0);
	}

	// Deinitialize renderer and rendering manager
	void RenderingManager::Deinitialize()
	{
		if (!bInitialized) return;

		bRunning = false;

		bgfx::destroy(mIndexBuffer);
		bgfx::destroy(mVertexBuffer);
		delete mShaderProgram;
		delete mWhiteTexture;
		bgfx::destroy(mUniform);

		// A CRUTCH SOLUTION: But it seems to be working pretty well...
		bgfx::frame();
		bgfx::frame();
		bgfx::frame();

		

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

		if (mVertices.size() > 0)
		{
			bgfx::update(mVertexBuffer, 0, bgfx::makeRef(mVertices.data(), mVertices.size() * sizeof(Vertex)));
		}
		
		for (RenderBatch& batch : mRenderBatches)
		{
			bgfx::setTransform(glm::value_ptr(batch.Position));
			bgfx::setVertexBuffer(0, mVertexBuffer);
			bgfx::setIndexBuffer(mIndexBuffer, batch.StartIndex, batch.NumberOfIndices);
			bgfx::setTexture(0, mUniform, batch.Texture);
			bgfx::submit(0, mShaderProgram->GetHandle());
		}

		//bgfx::frame();
	}

	// Draw rectangle
	void RenderingManager::DrawRect(glm::vec2 position, float rotation, uint32_t color, glm::vec2 scale)
	{
		RenderBatch batch;
		batch.StartIndex = mVertices.size() / 4 * 6;
		batch.NumberOfIndices = 6;
		batch.Texture = mWhiteTexture->GetHandle();
		batch.Position = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 1.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(scale.x, scale.y, 1.0f));

		mRenderBatches.push_back(batch);
		mVertices.push_back({ {-50.0f, 50.0f, 0.0f}, color, {0.0f, 1.0f} });
		mVertices.push_back({ {50.0f, 50.0f, 0.0f}, color, {1.0f, 1.0f} });
		mVertices.push_back({ {50.0f, -50.0f, 0.0f}, color, {1.0f, 0.0f} });
		mVertices.push_back({ {-50.0f, -50.0f, 0.0f}, color, {0.0f, 0.0f} });
	}

	// Draw texture
	void RenderingManager::DrawTexture(Texture* texture, glm::vec2 position, float rotation, uint32_t color, glm::vec2 scale)
	{
		RenderBatch batch;
		batch.StartIndex = mVertices.size() / 4 * 6;
		batch.NumberOfIndices = 6;
		batch.Texture = texture->GetHandle();
		batch.Position = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 1.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(scale.x, scale.y, 1.0f));

		mRenderBatches.push_back(batch);
		mVertices.push_back({ {-50.0f, 50.0f, 0.0f}, color, {0.0f, 1.0f} });
		mVertices.push_back({ {50.0f, 50.0f, 0.0f}, color, {1.0f, 1.0f} });
		mVertices.push_back({ {50.0f, -50.0f, 0.0f}, color, {1.0f, 0.0f} });
		mVertices.push_back({ {-50.0f, -50.0f, 0.0f}, color, {0.0f, 0.0f} });
	}
}