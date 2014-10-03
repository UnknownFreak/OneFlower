#include <SFML\Window\Keyboard.hpp>
#include <SFML\Window\Mouse.hpp>
#include "GameObject.h"
#include "InputComponent.h"
#include "RenderComponent.h"
#include "TransformComponent.hpp"

unsigned int IBaseComponent<InputComponent>::typeID = 1011;

InputComponent::InputComponent() {
	componentName = "InputComponent";

	jump = sf::Keyboard::Up;
	duck = sf::Keyboard::Down;
	moveLeft = sf::Keyboard::Left;
	moveRight = sf::Keyboard::Right;
	/*
	spellSlots[0] = sf::Keyboard::Num1;
	spellSlots[1] = sf::Keyboard::Num2;
	spellSlots[2] = sf::Keyboard::Num3;
	spellSlots[3] = sf::Keyboard::Num4;
	spellSlots[4] = sf::Keyboard::Num5;
	inventory = sf::Keyboard::I;
	action = sf::Mouse::Left;*/
}

std::string InputComponent::getTypeName() {
	return componentName;
}

void InputComponent::moveSprite(int moveSpeedX, int moveSpeedY, float deltaTime) {
	float moveX = 0, moveY = 0;

	if (sf::Keyboard::isKeyPressed(jump)) {
		this->attachedOn->GetComponent<TransformComponent>()->position.y -= moveSpeedY;
	}
	if (sf::Keyboard::isKeyPressed(duck)) {
		this->attachedOn->GetComponent<TransformComponent>()->position.y += moveSpeedY;
	}
	if (sf::Keyboard::isKeyPressed(moveLeft)) {
		this->attachedOn->GetComponent<TransformComponent>()->position.x -= moveSpeedX;
	}
	if (sf::Keyboard::isKeyPressed(moveRight)) {
		this->attachedOn->GetComponent<TransformComponent>()->position.x += moveSpeedX;
	}
}