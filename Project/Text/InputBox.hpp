#ifndef INPUTBOX_HPP
#define INPUTBOX_HPP
#include "Message.hpp"
#include <SFML\Graphics\VertexArray.hpp>
class InputBox:public Message
{
	sf::VertexArray box;

public:

	InputBox();
	InputBox(sf::Font& font,int len,int xStart,int yStart,int xEnd,int yEnd);

	void drawMessage(sf::RenderWindow* rwd);
	void move(int x,int y);
	void move(float x,float y);

private:
};

#endif