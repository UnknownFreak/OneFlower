#ifndef GameEntry_HPP
#define GameEntry_HPP

#include <graphics/window/Window.hpp>
#include <Input/InputHandler.hpp>
#include <scene/sceneManager.hpp>

#include <Graphics/UI/Stats.hpp>

#include <courier/courier.hpp>

class GameEntry
{
	bool m_exit;
	std::shared_ptr<of::graphics::window::Application> gfx;
	std::shared_ptr<of::input::InputHandler> input;
	
	std::shared_ptr<of::scene::SceneManager> scene;
	of::courier::Courier& courier;

	std::shared_ptr<Graphics::UI::Stats> ups;

	void physicsUpdate();
public:
	GameEntry();

	int Run();
};

#endif