#ifndef GameEntry_HPP
#define GameEntry_HPP

#include <Graphics/Window.hpp>
#include <Module/OneTime.hpp>
#include <Input/Console.hpp>
#include <Input/InputHandler.hpp>
#include <module/WorldManager.hpp>

class GameEntry
{
	bool m_exit;
	Graphics::RenderWindow& gfx;
	of::module::Time& time;
	Input::InputHandler& input;
	Console& console;
	
	of::module::WorldManager& world;

	void physicsUpdate();
public:
	GameEntry();

	int Run();
};

#endif