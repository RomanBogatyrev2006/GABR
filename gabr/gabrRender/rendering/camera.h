#pragma once
#include <glm/glm.hpp>

namespace Gabr
{
	struct Camera
	{
		glm::vec2 position = { 0.0f, 0.0f };

		glm::vec2 minBounds = {	-FLT_MAX, -FLT_MAX };
		glm::vec2 maxBounds = {	 FLT_MAX,  FLT_MAX };

		float zoom = 1.0f;
		float rotation = 0.0f;
	};
}