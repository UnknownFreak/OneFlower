#include "BasicText.hpp"

void GUI::BasicText::draw(sf::RenderTarget & target, sf::RenderStates renderstates) const
{

#if defined (_EDITOR_) || defined(_DEBUG)
		sf::VertexArray outline(sf::LinesStrip, 5);
		outline[0].color = sf::Color::Black;
		outline[1].color = sf::Color::Black;
		outline[2].color = sf::Color::Black;
		outline[3].color = sf::Color::Black;
		outline[4].color = sf::Color::Black;
		outline[0].position = sf::Vector2f(pos.x, pos.y);
		outline[1].position = sf::Vector2f(pos.x + text.getLocalBounds().width, pos.y);
		outline[2].position = sf::Vector2f(pos.x + text.getLocalBounds().width, pos.y + text.getLocalBounds().height);
		outline[3].position = sf::Vector2f(pos.x, pos.y + text.getLocalBounds().height);
		outline[4].position = sf::Vector2f(pos.x, pos.y);
		target.draw(outline, renderstates);
#endif
		target.draw(text, renderstates);
}

void GUI::BasicText::setPosition(Vector2 position)
{
	pos = position;
	text.setPosition(position.x, position.y);
}

void GUI::BasicText::setCharacterSize(unsigned int characterSize)
{
	text.setCharacterSize(characterSize);
}

GUI::BasicText::BasicText(sf::Font & font, sf::String message, Vector2 position, unsigned int characterSize) : text(message, font, characterSize), pos(position), message(message)
{
	text.setPosition(position.x, position.y);
}

GUI::BasicText::BasicText(const BasicText & copy) : text(copy.text), pos(copy.pos), message(copy.message)
{
	text.setPosition(pos.x,pos.y);
}

GUI::BasicText & GUI::BasicText::operator=(const BasicText & right)
{

	text = right.text;
	pos = right.pos;
	message = right.message;

	return *this;
}
