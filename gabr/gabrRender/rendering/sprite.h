#pragma once

#include <api.h>
#include <bgfx/bgfx.h>

namespace Gabr
{
	class GABR_API Sprite
	{
	public:
		Sprite();

		~Sprite();

		void Render();

		
		// --Transformation (Location)--

		// Set location by X
		float SetLocationX(float x);

		// Set location by Y
		float SetLocationY(float y);

		// Set location by X and Y
		std::pair<float, float> SetLocation(float x, float y);


		// Get location by X
		const float GetLocationX();

		// Get location by Y
		const float GetLocationY();

		// Get location by X and Y
		const std::pair<float, float> GetLocation();


		// --Transformation (Scale)--
		
		// Set scale by X
		float SetScaleX(float x);

		// Set scale by Y
		float SetScaleY(float y);

		// Set scale by X and Y
		std::pair<float, float> SetScale(float x, float y);


		// Get scale by X
		const float GetScaleX();

		// Get scale by Y
		const float GetScaleY();

		// Get scale by X and Y
		const std::pair<float, float> GetScale();


		// --Transformation (Other)--

		// Set angle
		float SetAngle(float angle);

		// Get angle
		const float GetAngle();


		// --Rendering--

		// Set texture
		//virtual void SetTexture() const;

		// Get teuxtre
		//virtual void GetTexture() const;


		// Set visibility
		bool SetVisible(bool visible);

		// Is visibile?
		const bool IsVisible();


		// Set opacity
		float SetOpacity(float opacity);

		// Get opacity
		const float GetOpacity();


	private:
		// --Transformation (Location)--

		// Location by X
		float mX = 0.0f;

		// Location by Y
		float mY = 0.0f;


		// --Transformation (Scale)--
		
		// Scale by X
		float mScaleX = 1.0f;

		// Scale by Y
		float mScaleY = 1.0f;


		// --Transformation (Other)--

		// Angle of object
		float mAngle = 0.0f;
		

		// --Rendering--
		
		// Texture to render
		std::string textureTag = "";

		// Is sprite visible
		bool mVisible = true;

		// Opacity of sprite
		float mOpacity = 1.0f;

		
		// --BGFX--

		// Index buffer
		uint16_t mIndices[6] = { 3,2,0,2,1,0 };
		bgfx::IndexBufferHandle mIndexBuffer;
	};
}