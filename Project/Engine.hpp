#ifndef Engine_HPP
#define Engine_HPP
#include <SFML\Window\Window.hpp>
#include <SFML\Window\Event.hpp>
#include "Game\Game.h"
#include "Game\Gfx.h"
#include "Engine\Window\EngineWindow.hpp"
#include "Game\Logic\Physics\Physics.hpp"
#include "Game\Logic\Time\Time.hpp"
#include "Game\Logic\Input\Mouse.hpp"
#include "Game\Logic\Input\InputHandler.hpp"

#include "Game\GUI\GraphicalUserInterface.hpp"
#include "Game\GameView.hpp"
#include "Game\World\WorldManagement.hpp"
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