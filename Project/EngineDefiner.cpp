#include "Engine.hpp"
#include "Game.h"
Game Engine::game;// = Game();
sf::Event Engine::event;
Gfx Engine::Graphic;
bool Engine::focus = true;
EngineWindow Engine::Window;
PhysicsEngine Engine::Physics;
Time Engine::time;
GraphicalUserInterface Engine::GUI;
