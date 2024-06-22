#include "editor.hpp"

#include <graphics/window/Window.hpp>

#include <internal/gizmo.hpp>
#include <internal/editorCamera.hpp>


namespace of::editor
{
	void initialize(std::shared_ptr<of::graphics::window::Application> gfx)
	{
		gfx->setCameraController(std::make_shared<EditorCamera>());
		gfx->addRenderable(of::graphics::window::RenderLayer::IMGUI, of::common::uuid(), std::make_shared<Gizmo>(gfx));
	}
}