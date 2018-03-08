#ifndef GameEntry_HPP
#define GameEntry_HPP

#include <Graphic\Gfx.h>
#include <Graphic\Time\Time.hpp>
#include <Input\InputHandler.hpp>

#include <Physics\Physics.hpp>

#include <World\WorldManager.hpp>

class GameEntry
{

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