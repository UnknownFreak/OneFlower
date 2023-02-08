#include <graphics/parentedRenderable.hpp>

#include <module/window/WindowProxy.hpp>
namespace of::graphics
{
	ParentedRenderable::ParentedRenderable() : m_parent(of::engine::GetModule<of::module::window::WindowProxy>().get())
	{
	}
}