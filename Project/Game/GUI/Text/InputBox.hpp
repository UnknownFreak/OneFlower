#ifndef INPUTBOX_HPP
#define INPUTBOX_HPP
#include <SFML\Graphics\VertexArray.hpp>
#include "../Message.hpp"
class InputBox:public Message
{
	sf::VertexArray box;

public:

	InputBox();
	InputBox(sf::Font& font, int len, float xStart, float yStart, float xEnd, float yEnd);

	void draw();
	void move(int x,int y);
	void move(float x,float y);

private:
};

#endif