#include "Message.hpp"
#include "FontDefiner.hpp"
#include <string>
Message::Message()
{
}
Message::~Message()
{

}
Message::Message(sf::Font& f, float dur, int length) 
{
	font = f;
	text = sf::Text();
	text.setFont(font);
	if (text.getFont() == NULL)
		throw MissingFontException();
	color = sf::Color::Black;
	text.setColor(color);
	size = text.getCharacterSize();
	duration = dur;
	maxLength = length;
}
void Message::move(int offsetX,int offsetY)
{
	text.move(offsetX,offsetY);
}
void Message::move(float offsetX, float offsetY)
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
void Message::setPosition(int x, int y)
{

	text.setPosition(x, y);

}
void Message::setPosition(float x, float y)
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
		throw MissingFontException();
	this->font = *font;
	text.setFont(*font);
		
}