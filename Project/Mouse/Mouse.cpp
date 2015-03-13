#include "Mouse.hpp"
#include "../Engine.hpp"

Mouse::Mouse() : pos(0, 0), offset(0,0)
{

}


void Mouse::update()
{
	
	offset.x = Engine::View.camera.getCenter().x - Engine::View.camera.getSize().x / 2;
	offset.y = Engine::View.camera.getCenter().y - Engine::View.camera.getSize().y / 2;

	pos.x = sf::Mouse::getPosition(Engine::View.render).x + offset.x;
	pos.y = sf::Mouse::getPosition(Engine::View.render).y + offset.y;
}