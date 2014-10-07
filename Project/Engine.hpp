#ifndef Engine_HPP
#define Engine_HPP
#include <SFML\Window\Window.hpp>
#include "CustomWindow.h"
#include "Game.h"
#include <SFML\Window\Event.hpp>

//Game Engine
namespace AsianVikingMotor
{

	extern sf::Event event;
	//The Editor Window
	extern EditorWindow Editor;

	//The Window of the Game
	extern sf::RenderWindow Window;

	//Change this name to GameHandler Game
	extern Game game;

};
namespace Engine = AsianVikingMotor;
namespace AVM = AsianVikingMotor;




#endif