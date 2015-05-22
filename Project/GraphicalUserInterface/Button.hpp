#ifndef ButtonObject_HPP
#define ButtonObject_HPP
#include "..\Component\HitboxComponent.hpp"
#include <SFML\Graphics\Sprite.hpp>
#include "..\Vector.h"
#include "ToolTip.hpp"
class Button
{
private:
	sf::Color hover;
	ToolTip toolTip;
	bool showToolTip;
	
	Vector2 position;

	std::string name;
	
public:

	sf::Sprite icon;
	Button();
	Button(std::string icon);
	Button(std::string icon, int sizeX, int sizeY, double posX, double posY,sf::Color hover = sf::Color(125,125,125), bool showToolTip = false);
	Button(std::string icon, int sizeX, int sizeY, double posX, double posY, std::string toolTip, sf::Color hover = sf::Color(125, 125, 125));
	//~Button();
	void setToolTip(std::string tip);
	void setIcon(std::string ico);
	void setPosition(double x,double y);
	void setPosition(Vector2 pos);
	void setName(std::string name);
	Vector2 getPosition();
	bool onHover();
	void ActionSlotClick();

	void draw();
};
#endif