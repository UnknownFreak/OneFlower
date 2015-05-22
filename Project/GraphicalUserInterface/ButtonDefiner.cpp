#include "Button.hpp"
#include "..\Component\HitboxComponent.hpp"
#include "..\Component\RenderComponent.h"
#include <string>
#include "..\Engine.hpp"

Button::Button() : position(0, 0), name(""), hover(125, 125, 125), toolTip("None", "ToolTipIcon.png"), showToolTip(false)
{
	icon.setTexture(*Engine::Graphic.requestTexture("ButtonTest.png"));
	icon.setTextureRect(sf::IntRect(0, 0, 64, 64));
	setPosition(position);
}

Button::Button(std::string name) : position(0, 0), toolTip("None", "ToolTipIcon.png"), showToolTip(false)
{
	icon.setTexture(*Engine::Graphic.requestTexture(name));
	icon.setTextureRect(sf::IntRect(0, 0, 64, 64));
	setPosition(position);
}

Button::Button(std::string icon, int sizeX, int sizeY, double posX, double posY, sf::Color hover, bool showToolTip) : name(""), icon(*Engine::Graphic.requestTexture(icon), sf::IntRect(0, 0, sizeX, sizeY)), position(posX, posY), hover(hover), showToolTip(showToolTip), toolTip("None", "ToolTipIcon.png")
{
	setPosition(position);
}

Button::Button(std::string icon, int sizeX, int sizeY, double posX, double posY, std::string toolTip, sf::Color hover) : name(""), icon(*Engine::Graphic.requestTexture(icon), sf::IntRect(0, 0, sizeX, sizeY)), position(posX, posY), hover(hover), showToolTip(true), toolTip(toolTip, "ToolTipIcon.png")
{
	setPosition(position);
}

void Button::setIcon(std::string str)
{
	icon.setTexture(*Engine::Graphic.requestTexture(str));
}

void Button::setToolTip(std::string toolTipText)
{
	toolTip.setToolTipText(toolTipText);
}

bool Button::onHover()
{
	if (Engine::GUI.mouseAim.position.x <= icon.getLocalBounds().width + position.x && Engine::GUI.mouseAim.position.x >= icon.getLocalBounds().left + position.x)
		if (Engine::GUI.mouseAim.position.y <= icon.getLocalBounds().height + position.y && Engine::GUI.mouseAim.position.y >= icon.getLocalBounds().top + position.y)
		{
			icon.setColor(hover);
			if (showToolTip)
			{
				toolTip.setPosition(Engine::GUI.mouseAim.position.x, Engine::GUI.mouseAim.position.y);
				toolTip.draw();
			}
			return true;
		}
	icon.setColor(sf::Color(255, 255, 255));
	return false;
}
void Button::setPosition(double x, double y)
{
	position.x = x;
	position.y = y;
	icon.setPosition(x, y);
}
void Button::setPosition(Vector2 pos)
{
	position = pos;
	icon.setPosition(pos.x, pos.y);
}

void Button::ActionSlotClick()
{
	Engine::GUI.setActiveSkill(name);
}

void Button::draw()
{
	Engine::View.render.draw(icon);
}
Vector2 Button::getPosition()
{
	return position;
}
void Button::setName(std::string name)
{
	this->name = name;
}