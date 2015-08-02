#ifndef Engine_HPP
#define Engine_HPP
#include <SFML\Window\Window.hpp>
#include "Game.h"
#include <SFML\Window\Event.hpp>
#include "Gfx.h"
#include "EngineWindow.hpp"
#include "Physics.hpp"
#include "Time.hpp"

#include "GraphicalUserInterface\GraphicalUserInterface.hpp"
#include "Mouse\Mouse.hpp"
#include "GameView.hpp"
#include "WorldManagement.hpp"
#include "InputHandler.hpp"
//LOW: Seperate each object into each header and have this work as a combine header to lessen the compile time
//Game Engine
namespace AsianVikingMotor
{

	extern sf::Event event;
	//The Editor Window

#ifdef _DEBUG
	//Main window of the Editor
	//TODO: Rename this shit
	extern EngineWindow Window;
#endif
	//Change this name to GameHandler Game
	extern Game game;

	//The Graphic handler
	extern Gfx Graphic;

	extern Time time;

	extern PhysicsEngine Physics;

	extern GraphicalUserInterface GUI;

	extern InputHandler Input;

	extern WorldManagement World;
};
namespace Engine = AsianVikingMotor;
namespace AVM = AsianVikingMotor;

#endif