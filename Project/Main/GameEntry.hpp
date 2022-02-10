#ifndef GameEntry_HPP
#define GameEntry_HPP

#include <SFML\Window\Event.hpp>

#include <Graphics/Window.hpp>
#include <Physics/Physics.hpp>
#include <Module/OneTime.hpp>
#include <Input/Console.hpp>
#include <Input/InputHandler.hpp>
#include <World/WorldManager.hpp>

namespace Game
{
	extern sf::Event event;
}

class GameEntry
{
	bool m_exit;
	Graphics::RenderWindow& gfx;
	Physics::PhysicsEngine& physics;
	EngineModule::Time& time;
	Input::InputHandler& input;
	Console& console;
	
	WorldManager world;

	void render();
	void update();

	void physicsUpdate();
public:
	GameEntry();

	int Run();
	void moveCamera(const Core::Vector2f& vec);
};

#endif