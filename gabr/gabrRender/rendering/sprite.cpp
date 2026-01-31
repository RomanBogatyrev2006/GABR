#include "sprite.h"

namespace Gabr
{

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
}