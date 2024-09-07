#pragma once

#include <graphics/window/Window.hpp>
#include <input/inputHandler.hpp>

namespace of::editor
{
	void initialize(std::shared_ptr<of::graphics::window::Application> gfx, std::shared_ptr<of::input::InputHandler> inputHandler);
	void exit();
}