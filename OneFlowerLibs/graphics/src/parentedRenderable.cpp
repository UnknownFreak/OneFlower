#include <graphics/parentedRenderable.hpp>

#include <graphics/window/Window.hpp>

namespace of::graphics
{
	ParentedRenderable::ParentedRenderable() : m_parent(of::graphics::window::Application::GetWindowSource().lock().get())
	{
	}
}