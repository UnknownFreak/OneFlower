#pragma once

#include <swizzle/gfx/CommandBuffer.hpp>
#include <graphics/view/mvp.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace of::graphics
{
	class Renderable
	{
	public:
		virtual ~Renderable() = default;
		// input, DrawCommandTransaction, MVP?
		virtual void updateFrame(const float& dt) = 0;
		virtual void render(std::unique_ptr<swizzle::gfx::DrawCommandTransaction>& transaction, view::MVP& mvp) = 0;
	};
}
