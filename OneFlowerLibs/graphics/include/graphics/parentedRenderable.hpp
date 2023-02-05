#pragma once
#include <graphics/renderable.hpp>
#include <graphics/window/RenderWindowHandle.hpp>
#include <module/window/WindowProxy.hpp>

namespace of::graphics
{

	class ParentedRenderable : public Renderable
	{
	protected:
		window::RenderWindowHandle* m_parent;
	public:

		ParentedRenderable() : m_parent(of::engine::GetModule<of::module::window::WindowProxy>().get()) {}
		~ParentedRenderable() = default;
	};
}