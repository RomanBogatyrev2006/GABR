#pragma once

#include <api.h>
#include <rendering/renderer.h>

namespace Gabr
{
	class GABR_API Entity
	{
	public:
		virtual ~Entity() = default;

		virtual void Update(float dt) {}

		virtual void Render(Renderer* renderer) {}
	};
}