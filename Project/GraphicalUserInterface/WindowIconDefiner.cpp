#include "WindowIcon.hpp"
#include "../Engine.hpp"

WindowIcon::WindowIcon() : icon(*Engine::Graphic.requestTexture("test.png")), messageText()
{
	BaseWindowObject::type = 1;
	setPosition(0, 0);
	setSize(icon.getTextureRect().width, icon.getTextureRect().height);
}
WindowIcon::WindowIcon(sf::Sprite icon, std::string toolTipTitle, std::string toolTipBody, std::string messageText, Vector2 offset, std::pair<int, int> index, sf::Color color) : icon(icon), toolTipTitle(toolTipTitle), toolTipBody(toolTipBody), messageText(*Engine::Graphic.font.requestFont("arial.ttf")), textOffset(offset), index(index)
{
	BaseWindowObject::type = 1;
	this->messageText.setSize(14);
	this->messageText = messageText;
	this->messageText.setColor(color);
	setPosition(0, 0);
	setSize(icon.getTextureRect().width, icon.getTextureRect().height);
}

void WindowIcon::draw()
{
	Engine::Graphic.view.render.draw(icon);
	messageText.draw();
}
void WindowIcon::setPosition(Vector2 pos)
{
	BaseWindowObject::setPosition(pos);
	icon.setPosition(position.x, position.y);
	messageText.setPosition(position.x + textOffset.x, position.y + textOffset.y);
}
void WindowIcon::setPosition(double x, double y)
{
	BaseWindowObject::setPosition(x, y);
	icon.setPosition(position.x, position.y);
	messageText.setPosition(position.x + textOffset.x, position.y + textOffset.y);
}