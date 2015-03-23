#include "FloatingText.hpp"
#include "../Gfx.h"
#include "../Engine.hpp"

FloatingText::~FloatingText()
{
}
FloatingText::FloatingText() : Message(*Engine::Graphic.font.requestFont("Arial.ttf"), -1, -1), offset(0, 0), iconName("")
{
	iconSprite.setTexture(*Engine::Graphic.requestTexture("test.png"), true);
	text.setString("");
}
FloatingText::FloatingText(std::string icoName, sf::Font& f, double dur, int l, int oX, int oY) : Message(f, dur, l), offset(oX,oY), iconName(icoName)
{
	text.setString("");
	setIcon(iconName);
}
FloatingText::FloatingText(const FloatingText& ft) : Message(ft.font, ft.duration, ft.maxLength), offset(ft.offset), iconName(ft.iconName)
{
	setColor(ft.color);
	text.setString(ft.text.getString());
	setPosition(ft.text.getPosition().x, ft.text.getPosition().y);
	setIcon(iconName);
}
void FloatingText::drawMessage(sf::RenderWindow* rwd)
{
	rwd->draw(iconSprite);
	rwd->draw(text);
}
void FloatingText::move(double x, double y)
{
	text.move(x, y);
	iconSprite.move(x, y);
}

void FloatingText::setPosition(double x, double y)
{
	text.setPosition(x + offset.x, y + offset.y);
	iconSprite.setPosition(x , y);
}
void FloatingText::setOffset(double x, double y)
{
	offset.x = x;
	offset.y = y;
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
#ifdef _DEBUG
		throw MissingIconException(this->iconSprite);
#else
	{
		//LOW set propper missingtexture
		icoName = "test.png";
		iconSprite.setTexture(*Engine::Graphic.requestTexture(icoName), true);
	}
#endif
	else
	{
		iconSprite.setTexture(*Engine::Graphic.requestTexture(iconName), true);
		
	}
}

MissingIconException::MissingIconException(sf::Sprite& sprite)
{
	tmp.setTexture(*Engine::Graphic.requestTexture("test.png"));
}

const sf::Texture* MissingIconException::what()
{
	return tmp.getTexture();
}