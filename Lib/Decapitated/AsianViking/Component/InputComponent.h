#ifndef InputComponent_H
#define InputComponent_H
#include <SFML\Graphics\Sprite.hpp>
#include <string>
#include "IBaseComponent.hpp"

class InputComponent : IBaseComponent<InputComponent>
{
public:
	std::string getTypeName();
	void moveSprite(sf::Sprite *sprite, float moveSpeedX, float moveSpeedY, float deltaTime);

private:
	//const std::string componentName = "InputComponent"; //put this in constructor
};

#endif