#ifndef Engine_HPP
#define Engine_HPP
#include <SFML\Window\Window.hpp>
#include "Game.h"
#include <SFML\Window\Event.hpp>
#include "Gfx.h"
#include "EngineWindow.hpp" 
//Game Engine
namespace AsianVikingMotor
{

	extern sf::Event event;
	//The Editor Window

	//The Window of the Game
	extern EngineWindow Window;

	//Change this name to GameHandler Game
	extern Game game;

	//The Graphic handler
	extern Gfx Graphic;

	extern bool focus;



};
namespace Engine = AsianVikingMotor;
namespace AVM = AsianVikingMotor;




#endif