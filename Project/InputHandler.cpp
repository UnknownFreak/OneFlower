#include <SFML\Window\Keyboard.hpp>
#include <SFML\Window\Mouse.hpp>
#include "InputHandler.hpp"

InputHandler::InputHandler() {
	Keybind Jump = {sf::Keyboard::Key::W, "Jump"};
	Keybind Duck = {sf::Keyboard::Key::S, "Duck"};
	Keybind moveLeft = {sf::Keyboard::Key::A, "moveLeft"};
	Keybind moveRight = {sf::Keyboard::Key::D, "moveRight"};

	keybinds.push_back(Jump);
	keybinds.push_back(Duck);
	keybinds.push_back(moveLeft);
	keybinds.push_back(moveRight);
}

std::vector<std::string> InputHandler::getInput() {
	std::vector<std::string> inputs;

	for(std::vector<Keybind>::iterator it = keybinds.begin(); it != keybinds.end(); ++it) {
		if (sf::Keyboard::isKeyPressed((it)->input))
			inputs.push_back((it)->action);
	}

	return inputs;
}

/*
void moveSprite(int moveSpeedX, int moveSpeedY, float deltaTime) {
	int movementSpeed = 1;
	sf::Vector2f direction;
	float force = 0;
	if (sf::Keyboard::isKeyPressed(jump)) 
	{
		direction.y += 1;
	}
	if (sf::Keyboard::isKeyPressed(duck)) 
	{
		direction.y -= 1;
	}
	if (sf::Keyboard::isKeyPressed(moveLeft)) 
	{
		direction.x -= 1;
	}
	if (sf::Keyboard::isKeyPressed(moveRight)) 
	{
		direction.x += 1;
	}
}*/
