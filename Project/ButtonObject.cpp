#include "ButtonObject.hpp"
#include "ButtonObject.hpp"
#include "Component\HitboxComponent.hpp"
#include "Component\RenderComponent.h"
#include <string>
#include "Engine.hpp"

Button::Button(): position(0,0),name("")
{
	hitbox = new HitboxComponent(64,64);
	icon.setTexture(*Engine::Graphic.requestTexture("test.png"));
	icon.setTextureRect(sf::IntRect(0,0,64,64));
	setPosition(position);
}

Button::Button(std::string name): position(0,0)
{
	hitbox = new HitboxComponent(64,64);
	icon.setTexture(*Engine::Graphic.requestTexture(name));
	icon.setTextureRect(sf::IntRect(0,0,64,64));
	setPosition(position);
}

void Button::setIcon(std::string str)
{
	icon.setTexture(*Engine::Graphic.requestTexture(str));
}

bool Button::onHover()
{
	if(Engine::GUI.mouseAim.position.x + 16 <= icon.getLocalBounds().width + position.x && Engine::GUI.mouseAim.position.x + 16 >= icon.getLocalBounds().left + position.x)
		if(Engine::GUI.mouseAim.position.y + 16 <= icon.getLocalBounds().height + position.y && Engine::GUI.mouseAim.position.y + 16 >= icon.getLocalBounds().top + position.y)
		{
			icon.setColor(sf::Color(125,125,125));
			return true;
		}
	icon.setColor(sf::Color(255,255,255));
	return false;
}
void Button::setPosition(double x,double y)
{
	position.x = x;
	position.y = y;
	hitbox->position.x = x;
	hitbox->position.y = y;
	icon.setPosition(x,y);
}
void Button::setPosition(Vector2 pos)
{
	position = pos;
	hitbox->position = pos;
	icon.setPosition(pos.x,pos.y);
}

void Button::onClick()
{
	if(click)
		click();
	else
		MessageBox(Engine::Window.hWnd,"Function not set","Error",NULL);
}

void Button::ActionSlotClick()
{
	Engine::GUI.setActiveSkill(name);
}