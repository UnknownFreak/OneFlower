#ifndef GameEntry_HPP
#define GameEntry_HPP

#include <graphics/window/Window.hpp>
#include <Module/OneTime.hpp>
#include <Input/InputHandler.hpp>
#include <module/sceneManager.hpp>

#include <Graphics/UI/Stats.hpp>
#include <Graphics/UI/LoadingScreenInfo.hpp>

#include <courier/courier.hpp>

class GameEntry
{
	bool m_exit;
	std::shared_ptr<of::graphics::window::Application> gfx;
	of::module::Time& time;
	of::input::InputHandler& input;
	
	of::module::SceneManager& world;
	of::courier::Courier& courier;

	std::shared_ptr<Graphics::UI::Stats> ups;
	std::shared_ptr<Graphics::UI::LoadingScreenInfo> loadingScreenInfo;

	void physicsUpdate();
public:
	GameEntry();

	int Run();
};

#endif