#pragma once
#include <graphics/renderable.hpp>
#include <graphics/window/Window.hpp>

namespace of::graphics
{

	class ParentedRenderable : public Renderable
	{
	protected:
		window::Application* m_parent;
	public:

		ParentedRenderable();
		~ParentedRenderable() = default;
	};
}