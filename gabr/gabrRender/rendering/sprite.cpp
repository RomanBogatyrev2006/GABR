#include "sprite.h"

#include <log/logger.h>
/*
namespace Gabr
{
	Sprite::Sprite()
	{
		mIndexBuffer = bgfx::createIndexBuffer(bgfx::makeRef(mIndices, 12));

		if (!bgfx::isValid(mIndexBuffer))
		{
			Logger::Get().Log(LogSeverity::TRACE, "Couldn't create index buffer!");
			return;
		}

		mVertexLayout.begin()
			.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
			.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
		.end();

		                 					   //AABBGGRR
		mVertices[0] = { {-0.5f, 0.5f, 0.0f}, {0xFFFFFFFF}, {0.0, 0.0} };
		mVertices[1] = { {0.5, 0.5, 0.0},     {0xFFFFFFFF}, {1.0, 0.0} };
		mVertices[2] = { {0.5, -0.5, 0.0},    {0xFFFFFFFF}, {1.0, 1.0} };
		mVertices[3] = { {-0.5, -0.5, 0.0},   {0xFFFFFFFF}, {0.0, 1.0} };

		//mVertexBuffer = bgfx::createVertexBuffer(bgfx::makeRef(mVertices, sizeof(Vertex) * 4), mVertexLayout);

		if (!bgfx::isValid(mVertexBuffer))
		{
			Logger::Get().Log(LogSeverity::TRACE, "Couldn't create index buffer!");
			return;
		}

		shaderProgram = new Shader("vertex.bin", "frag.bin");
		mTexture = new Texture("gamedata/AboutToPOP.png");
		mUniform = bgfx::createUniform("textureColor", bgfx::UniformType::Sampler);
	}

	Sprite::~Sprite()
	{
		delete shaderProgram;
		delete mTexture;
		bgfx::destroy(mUniform);
		bgfx::destroy(mIndexBuffer);
		bgfx::destroy(mVertexBuffer);
	}

	void Sprite::Render()
	{
		bgfx::setTexture(0, mUniform, mTexture->GetHandle());
		bgfx::setVertexBuffer(0, mVertexBuffer);
		bgfx::setIndexBuffer(mIndexBuffer);
		bgfx::submit(0, shaderProgram->GetHandle());
	}


	// Set location by X
	float Sprite::SetLocationX(float x)
	{
		mX = x;
		return mX;
	}

	// Set location by Y
	float Sprite::SetLocationY(float y)
	{
		mY = y;
		return mY;
	}

	// Set location by X and Y
	std::pair<float, float> Sprite::SetLocation(float x, float y)
	{
		mX = x;
		mY = y;
		return std::make_pair(mX, mY);
	}

	// Get location by X
	const float Sprite::GetLocationX()
	{
		return mX;
	}

	// Get location by Y
	const float Sprite::GetLocationY()
	{
		return mY;
	}

	// Get location by X and Y
	const std::pair<float, float> Sprite::GetLocation()
	{
		return std::make_pair(mX, mY);
	}

	// Set scale by X
	float Sprite::SetScaleX(float x)
	{
		mScaleX = x;
		return mScaleX;
	}

	// Set scale by Y
	float Sprite::SetScaleY(float y)
	{
		mScaleY = y;
		return mScaleY;
	}

	// Set scale by X and Y
	std::pair<float, float> Sprite::SetScale(float x, float y)
	{
		return std::make_pair(mScaleX, mScaleY);
	}

	// Get scale by X
	const float Sprite::GetScaleX()
	{
		return mScaleX;
	}

	// Get scale by Y
	const float Sprite::GetScaleY()
	{
		return mScaleY;
	}

	// Get scale by X and Y
	const std::pair<float, float> Sprite::GetScale()
	{
		return std::make_pair(mScaleX, mScaleY);
	}

	// Set angle
	float Sprite::SetAngle(float angle)
	{
		mAngle = angle;
		return mAngle;
	}

	// Get angle
	const float Sprite::GetAngle()
	{
		return mAngle;
	}

	// Set visibility
	bool Sprite::SetVisible(bool visible)
	{
		mVisible = visible;
		return mVisible;
	}

	// Is visibile?
	const bool Sprite::IsVisible()
	{
		return mVisible;
	}

	// Set opacity
	float Sprite::SetOpacity(float opacity)
	{
		mOpacity = opacity;
		return mOpacity;
	}

	// Get opacity
	const float Sprite::GetOpacity()
	{
		return mOpacity;
	}
}*/