#pragma once
#include <graphics/renderable.hpp>
#include <graphics/window/RenderWindowHandle.hpp>

namespace of::graphics
{

	class ParentedRenderable : public Renderable
	{
	protected:
		window::RenderWindowHandle* m_parent;
	public:

		ParentedRenderable();
		~ParentedRenderable() = default;
	};
}