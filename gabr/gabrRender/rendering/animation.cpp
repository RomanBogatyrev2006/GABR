#include "animation.h"

namespace Gabr
{
	Animation::Animation(const std::vector<AnimationFrame>& frames, bool isLooping, int startFrame)
	{
		SetAnimation(frames, isLooping, startFrame);
	}

	void Animation::SetAnimation(const std::vector<AnimationFrame>& frames, bool isLooping, int startFrame)
	{
		mFrames = frames;
		bLooped = isLooping;
		mCurrentFrame = startFrame;

		if (!mFrames.empty()) mFrameDelay = mFrames[mCurrentFrame].delay;
	}

	void Animation::Update(double deltaTime)
	{
		if (mFrames.empty()) return;

		mFrameDelay -= (float)deltaTime;

		if (mFrameDelay > 0.0f) return;

		mCurrentFrame++;

		if (mCurrentFrame >= (int)mFrames.size())
		{
			if (bLooped) mCurrentFrame = 0;
			else mCurrentFrame = (int)mFrames.size() - 1;
		}

		mFrameDelay = mFrames[mCurrentFrame].delay;
	}
	
	const std::string& Animation::GetCurrentTexture() const
	{
		static std::string empty = "";
		if (mFrames.empty()) return empty;

		return mFrames[mCurrentFrame].textureTag;
	}
	
	void Animation::Reset()
	{
		mCurrentFrame = 0;
		
		if (!mFrames.empty()) mFrameDelay = mFrames[0].delay;
	}
}