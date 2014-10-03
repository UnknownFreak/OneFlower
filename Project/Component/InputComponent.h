#ifndef InputComponent_H
#define InputComponent_H
#include <SFML\Graphics\Sprite.hpp>
#include <string>
#include "IBaseComponent.hpp"

class InputComponent : public IBaseComponent<InputComponent>
{
public:
	InputComponent();

	std::string getTypeName();
	void moveSprite(sf::Sprite *sprite, float moveSpeedX, float moveSpeedY, float deltaTime);

private:
	sf::Keyboard::Key jump;
	sf::Keyboard::Key duck;
	sf::Keyboard::Key moveLeft;
	sf::Keyboard::Key moveRight;
};

#endif