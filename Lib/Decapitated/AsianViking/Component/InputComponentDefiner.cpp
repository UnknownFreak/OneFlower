#include "InputComponent.h"
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Window\Keyboard.hpp>
#include <string>

std::string InputComponent::getTypeName() {
	return componentName;
}

void InputComponent::moveSprite(sf::Sprite *sprite, float moveSpeedX, float moveSpeedY, float deltaTime) {
	float moveX = 0, moveY = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		moveY -= moveSpeedY * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		moveY += moveSpeedY * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		moveX -= moveSpeedX * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		moveX += moveSpeedX * deltaTime;

	sprite->move(moveX, moveY);
}
