#include "Message.hpp"
#include "Font.hpp"
#include <string>
#include "../Engine.hpp"


Message::Message(const Message& msg) :text(msg.text), color(msg.color), size(msg.text.getCharacterSize()), duration(msg.duration), maxLength(msg.maxLength)
{

}
Message::Message() :text(sf::Text()), color(sf::Color::Black), size(text.getCharacterSize()), duration(5), maxLength(-1)
{
	text.setColor(color);
}
Message::~Message()
{

}
Message::Message(const sf::Font& f, const double dur,const int length) : text(sf::Text()), font(f), color(sf::Color::Black), size(text.getCharacterSize()), duration(dur), maxLength(length)
{
	text.setColor(color);
#ifndef _DEBUG
	if (text.getFontt() == NULL)
		throw MissingFonttException();
#endif
	text.setFont(font);
}
void Message::move(double offsetX, double offsetY)
{
	text.move(offsetX, offsetY);
}
Message& Message::operator=(std::string s)
{
	if (s.length() > maxLength && maxLength > 0) {
		s.resize(maxLength);
	}
	text.setString(s);
	return *this;
}
void Message::setColor(sf::Color c)
{
	color = c;
	text.setColor(c);
}
void Message::setSize(int s) {
	text.setCharacterSize(s);
}
void Message::setLength(int l) {
	std::string tmp;
	maxLength = l;
	if (l > 0) {
		tmp = text.getString();
		tmp.resize(l);
		text.setString(tmp);
	}
}
void Message::setPosition(double x, double y)
{
	text.setPosition(x, y);
}
void Message::drawMessage(sf::RenderWindow* rwd)
{
	rwd->draw(text);
}
void Message::setFont(sf::Font* font)
{
	if (font == NULL)
#ifdef _DEBUG
		throw MissingFontException();
#else
		//LOW set propper misingFontt
		this->font = Engine::Graphic.font.requestFont("arial.ttf");
#endif
		
	this->font = *font;
	text.setFont(*font);
		
}