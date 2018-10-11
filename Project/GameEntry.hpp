#ifndef GameEntry_HPP
#define GameEntry_HPP

#include <SFML\Window\Event.hpp>

#include <Graphic\Gfx.h>
#include <Core\Time.hpp>
#include <Input\InputHandler.hpp>

#include <Physics\Physics.hpp>

#include <Graphic\World\WorldManager.hpp>

namespace Game
{
	extern sf::Event event;
}

class GameEntry
{
	bool m_exit;
	const Gfx& gfx;
	Time& time;
	InputHandler& input;

	PhysicsEngine& physics;

	WorldManager& world;

public:
	GameEntry();

	int main();

	void render();
	void update();

	void mainMenuUpdater();

	void physicsUpdate();

};

#endif