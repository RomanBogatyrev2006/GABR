#pragma once
#include <api.h>

namespace Gabr
{
	struct AnimationFrame
	{
		std::string textureTag;
		std::string soundFile;
		float delay;
	};

	class GABR_API Animation
	{
	public:
		Animation() = default;
		
		Animation(const std::vector<AnimationFrame>& frames, bool isLooping = true, int startFrame = 0);

		void SetAnimation(const std::vector<AnimationFrame>& frames, bool isLooping, int startFrame = 0);

		void Update(double deltaTime);

		const std::string& GetCurrentTexture() const;

		void Reset();

	private:
		// Array of animation frames
		std::vector<AnimationFrame> mFrames;

		// Animation looped
		bool bLooped = true;


		// Current frame
		int mCurrentFrame = 0;
		
		// Delay between frame
		float mFrameDelay = 0.0f;
		
	};
}