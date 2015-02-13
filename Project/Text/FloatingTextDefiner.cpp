#include "FloatingText.hpp"
#include "../Gfx.h"
#include "../Engine.hpp"

FloatingText::~FloatingText()
{

}
FloatingText::FloatingText()
{
	duration = -1;
	maxLength = -1;
	offsetX = 0;
	offsetY = 0;
	iconSprite.setTexture(*Engine::Graphic.requestTexture("test.png"), true);
	text.setString("");
}
FloatingText::FloatingText(std::string icoName, sf::Font& f, double dur, int l, int oX, int oY) : Message(f,dur,l)
{
	font = f;
	duration = dur;
	maxLength = l;
	offsetX = oX;
	offsetY = oY;
	iconName = icoName;
	if (!Engine::Graphic.loadTexture(iconName))
		throw MissingIconException(this->iconSprite);
	else
	{
	iconSprite.setTexture(*Engine::Graphic.requestTexture(icoName),true);
	text.setString("");
	}
}
FloatingText::FloatingText(FloatingText& ft) : Message(ft.font, ft.duration, ft.maxLength)
{
	font = ft.font;
	setColor(ft.color);
	duration = ft.duration;
	maxLength = ft.maxLength;
	offsetX = ft.offsetX;
	offsetY = ft.offsetY;
	iconName = ft.iconName;
	if (!Engine::Graphic.loadTexture(iconName))
		throw MissingIconException(this->iconSprite);
	else
	{
		iconSprite.setTexture(*Engine::Graphic.requestTexture(iconName), true);
		text.setString(ft.text.getString());
		setPosition(ft.text.getPosition().x, ft.text.getPosition().y);
	}
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
	text.setPosition(x+ offsetX, y+ offsetY);
	iconSprite.setPosition(x , y );
}
void FloatingText::setPosition(float x, float y)
{
	text.setPosition(x+ offsetX, y+ offsetY);
	iconSprite.setPosition(x , y );
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
	if (!Engine::Graphic.loadTexture(iconName))
		throw MissingIconException(this->iconSprite);
	else
		iconSprite.setTexture(*Engine::Graphic.requestTexture(iconName), true);
}

MissingIconException::MissingIconException(sf::Sprite& sprite)
{
	tmp.setTexture(*Engine::Graphic.requestTexture("test.png"));
}

const sf::Texture* MissingIconException::what()
{
	return tmp.getTexture();
}