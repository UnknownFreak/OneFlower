#include "InputHandler.hpp"

ResourceType IEngineResource<InputHandler>::type = ResourceType::Input;

void InputHandler::update()
{
	mouse.update();
	keyboard.update();
}


InputHandler::InputHandler() : keyboard(sf::Keyboard::isKeyPressed), mouse(sf::Mouse::isButtonPressed)
{
}

