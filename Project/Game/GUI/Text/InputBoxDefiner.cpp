#include "InputBox.hpp"
#include "../../../Engine.hpp"
InputBox::InputBox()
{
}

InputBox::InputBox(sf::Font& font, int len, float x1, float y1, float x2, float y2) : Message(font, -1, len), box(sf::VertexArray(sf::LinesStrip, 4))
{
	box[0].position = sf::Vector2f(x1,y1);
	box[1].position = sf::Vector2f(x2,y1);
	box[2].position = sf::Vector2f(x2,y2);
	box[3].position = sf::Vector2f(x2,y1);

	createBody("Some string goes here");
}

void InputBox::draw()
{
	Engine::Graphic.view.render.draw(box);
	draw();
}

void InputBox::move(int x,int y)
{
	box[0].position.x += x;
	box[0].position.y += y;

	box[1].position.x += x;
	box[1].position.y += y;

	box[2].position.x += x;
	box[2].position.y += y;

	box[3].position.x += x;
	box[3].position.y += y;
}
void InputBox::move(float x,float y)
{
	box[0].position.x += x;
	box[0].position.y += y;

	box[1].position.x += x;
	box[1].position.y += y;

	box[2].position.x += x;
	box[2].position.y += y;

	box[3].position.x += x;
	box[3].position.y += y;
}