#ifndef ButtonObject_HPP
#define ButtonObject_HPP
#include "Component\HitboxComponent.hpp"
#include <SFML\Graphics\Sprite.hpp>
#include "Vector.h"
class Button
{

private:


public:

	void(*click)();

	Vector2 position;

	std::string name;
	sf::Sprite icon;
	HitboxComponent* hitbox;
	Button();
	Button(std::string icon);
	//~Button();
	void setIcon(std::string ico);
	void setPosition(double x, double y);
	void setPosition(Vector2 pos);
	bool onHover();
	void onClick();
	void ActionSlotClick();
	
};
#endif