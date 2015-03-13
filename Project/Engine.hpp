#ifndef Engine_HPP
#define Engine_HPP
#include <SFML\Window\Window.hpp>
#include "Game.h"
#include <SFML\Window\Event.hpp>
#include "Gfx.h"
#include "EngineWindow.hpp" 
#include "Physics.hpp"
#include "Time.hpp"
#include "GraphicalUserInterface.hpp"
#include "GameView.hpp"

//LOW: Seperate each object into each header and have this work as a combine header to lessen the compile time
//Game Engine
namespace AsianVikingMotor
{
	extern  GameView View;

	extern sf::Event event;
	//The Editor Window

#ifdef _DEBUG
	//The Window of the Game
	extern EngineWindow Window;
#endif
	//Change this name to GameHandler Game
	extern Game game;

	//The Graphic handler
	extern Gfx Graphic;

	extern Time time;

	extern PhysicsEngine Physics;
	extern GraphicalUserInterface GUI ;
};
namespace Engine = AsianVikingMotor;
namespace AVM = AsianVikingMotor;




#endif