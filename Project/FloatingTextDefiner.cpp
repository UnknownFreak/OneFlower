#include "FloatingText.hpp"
#include "Gfx.h"
#include "Engine.hpp"

FloatingText::~FloatingText()
{

}
FloatingText::FloatingText()
{
	renderLayer = 2;
}
FloatingText::FloatingText(std::string icoName, sf::Font& f, double dur, int l, int oX, int oY) : Message(f,dur,l)
{
	font = f;
	duration = dur;
	maxLength = l;
	offsetX = oX;
	offsetY = oY;
	renderLayer = 2;
	iconName = icoName;
	iconSprite.setTexture(*Engine::Graphic.requestTexture(icoName),true);
	text.setString("");
}
FloatingText::FloatingText(FloatingText& ft) : Message(ft.font, ft.duration, ft.maxLength)
{
	font = ft.font;
	setColor(ft.color);
	duration = ft.duration;
	maxLength = ft.maxLength;
	offsetX = ft.offsetX;
	offsetY = ft.offsetY;
	renderLayer = ft.renderLayer;
	iconName = ft.iconName;
	iconSprite.setTexture(*Engine::Graphic.requestTexture(iconName), true);
	text.setString(ft.text.getString());
	setPosition(ft.text.getPosition().x, ft.text.getPosition().y);
}
void FloatingText::drawMessage(sf::RenderWindow* rwd)
{
	rwd->draw(iconSprite);
	rwd->draw(text);
}
void FloatingText::move(int x, int y)
{
	text.move(x, y);
	iconSprite.move(x,y);
	
}
void FloatingText::move(float x, float y)
{
	text.move(x, y);
	iconSprite.move(x, y);
}

void FloatingText::setPosition(int x, int y)
{
	text.setPosition(x, y);
	iconSprite.setPosition(x + offsetX, y + offsetY);
}
void FloatingText::setPosition(float x, float y)
{
	text.setPosition(x, y);
	iconSprite.setPosition(x + offsetX, y + offsetY);
}
void FloatingText::setOffset(int x, int y)
{
	offsetX = x;
	offsetY = y;
}

FloatingText& FloatingText::operator=(std::string info)
{
	if (info.length() > maxLength && maxLength > 0)
	{
		info.resize(maxLength);
	}
	text.setString(info);
	return *this;
}
void FloatingText::setIcon(std::string name)
{
	iconName = name;
	iconSprite.setTexture(*Engine::Graphic.requestTexture(iconName), true);
}