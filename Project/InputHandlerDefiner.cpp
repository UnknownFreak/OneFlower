#include "InputHandler.hpp"

void InputHandler::update()
{
	mouse.update();
	for(auto it = keybinds.begin(); it != keybinds.end(); it++)
		if(sf::Keyboard::isKeyPressed(it->first))
		{
			it->second();
			break;
		}
}
void InputHandler::addKeybind(sf::Keyboard::Key key,CallBack callbackFunction)
{
	keybinds.insert(std::pair<sf::Keyboard::Key,CallBack>(key,callbackFunction));
}
