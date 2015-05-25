#include "BaseWindow.hpp"
#include "../Engine.hpp"

BaseWindow::BaseWindow(int x, int y, int sizeX, int sizeY, bool resizeable, std::string title) : close("WindowCloseIcon.png", 16, 16, x + sizeX - 16, sizeY),
window(*Engine::Graphic.requestTexture("DefaultWindow.png"), sf::IntRect(0, 0, sizeX, sizeY)),
resize("WindowResize.png", 16, 16, x + sizeX - 16, y + sizeY - 16), clickOffset(0, 0), position(x, y), drawResizeIcon(resizeable), title(*Engine::Graphic.font.requestFont("arial.ttf")),
outline(sf::LinesStrip,5)
{
	this->title = title;
	this->title.setSize(21);
	outline[0].position = sf::Vector2f(x, y);
	outline[1].position = sf::Vector2f(x + sizeX, y);
	outline[2].position = sf::Vector2f(x + sizeX, y + sizeY);
	outline[3].position = sf::Vector2f(x, y + sizeY);
	outline[4].position = sf::Vector2f(x, y);
	outline[0].color = sf::Color::Black;
	outline[1].color = sf::Color::Black;
	outline[2].color = sf::Color::Black;
	outline[3].color = sf::Color::Black;
	outline[4].color = sf::Color::Black;
}

void BaseWindow::draw()
{
	Engine::View.render.draw(window);
	Engine::View.render.draw(outline);
	title.draw();
	close.draw();
	if (drawResizeIcon)
		resize.draw();
}
void BaseWindow::Imove(double x, double y)
{
	checkMouseOffset(x, y);
	position.x = x - offsetX - clickOffset.x;
	position.y = y - offsetY - clickOffset.y;
	outline[0].position = sf::Vector2f(position.x, position.y);
	outline[1].position = sf::Vector2f(position.x + window.getTextureRect().width, position.y);
	outline[2].position = sf::Vector2f(position.x + window.getTextureRect().width, position.y + window.getTextureRect().height);
	outline[3].position = sf::Vector2f(position.x, position.y + window.getTextureRect().height);
	outline[4].position = sf::Vector2f(position.x, position.y);
}
void BaseWindow::Iresize(double x, double y)
{
	int x1 = x - window.getPosition().x;
	int y1 = y - window.getPosition().y;
	if (x1 < 220)
		x1 = 220;
	if (y1 < 240)
		y1 = 240;
	window.setTextureRect(sf::IntRect(0, 0, x1, y1));
	outline[1].position = sf::Vector2f(window.getPosition().x + x1, window.getPosition().y);
	outline[2].position = sf::Vector2f(window.getPosition().x + x1, window.getPosition().y + y1);
	outline[3].position = sf::Vector2f(window.getPosition().x, window.getPosition().y + y1);

}
void BaseWindow::checkMouseOffset(double&x, double &y)
{
	float width = Engine::View.camera.getSize().x;
	float height = Engine::View.camera.getSize().y;
	if (x > Engine::View.camera.getCenter().x + width / 2 - 50)
		x = Engine::View.camera.getCenter().x + width / 2 - 50;
	if (x < Engine::View.camera.getCenter().x - width / 2)
		x = Engine::View.camera.getCenter().x - width / 2;
	if (y > Engine::View.camera.getCenter().y + height / 2 - 30)
		y = Engine::View.camera.getCenter().y + height / 2 - 30;
	if (y < Engine::View.camera.getCenter().y - height / 2)
		y = Engine::View.camera.getCenter().y - height / 2;
}
void BaseWindow::WindowHandle()
{
	if (close.onHover() && Engine::Input.mouse.leftClick() && Engine::GUI.focusedWindow->checkMouseInside() && Engine::GUI.focusedWindow == this ||
		close.onHover() && Engine::Input.mouse.leftClick() && !Engine::GUI.focusedWindow->checkMouseInside())
	{
		requestClose = true;
	}
	if (resize.onHover() && Engine::Input.mouse.leftClick() && drawResizeIcon && Engine::GUI.focusedWindow->checkMouseInside() && Engine::GUI.focusedWindow == this ||
		resize.onHover() && Engine::Input.mouse.leftClick() && !Engine::GUI.focusedWindow->checkMouseInside())
		resizeing = true;
	if (Engine::Input.mouse.LMBPressed && resizeing)
		Iresize(Engine::Input.mouse.pos.x, Engine::Input.mouse.pos.y);
	else if (resizeing)
		resizeing = false;
	if (!focus && !Engine::GUI.focusedWindow->checkMouseInside() && Engine::Input.mouse.leftClick() && checkMouseInside() && !Engine::GUI.focusedWindow->moving)
	{
		requestFocus = true;
		Engine::GUI.updateFocus = true;
	}
	if (MouseInsideTitleBar() && focus && Engine::GUI.focusedWindow->checkMouseInside() || MouseInsideTitleBar() && requestFocus)
	{
		if (Engine::Input.mouse.leftClick() || requestFocus)
		{
			moving = true;
			clickOffset.x = Engine::Input.mouse.pos.x - window.getPosition().x;
			clickOffset.y = Engine::Input.mouse.pos.y - window.getPosition().y;
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && moving)
			Imove(Engine::Input.mouse.pos.x, Engine::Input.mouse.pos.y);
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && moving)
		Imove(Engine::Input.mouse.pos.x, Engine::Input.mouse.pos.y);
	else
		moving = false;
}
bool BaseWindow::MouseInsideTitleBar()
{
	if (Engine::GUI.mouseAim.position.x <= window.getLocalBounds().width + window.getPosition().x &&
		Engine::GUI.mouseAim.position.x >= window.getLocalBounds().left + window.getPosition().x)
		if (Engine::GUI.mouseAim.position.y <= 25 + window.getPosition().y &&
			Engine::GUI.mouseAim.position.y >= window.getLocalBounds().top + window.getPosition().y)
			return true;
	return false;
}
void BaseWindow::move()
{
	offsetX = Engine::View.camera.getCenter().x - (800 * Engine::View.camera.getViewport().width / 2);
	offsetY = Engine::View.camera.getCenter().y - (600 * Engine::View.camera.getViewport().height / 2);
	window.setPosition(position.x + offsetX, position.y + offsetY);
	close.setPosition(position.x + offsetX + window.getTextureRect().width - inventoryButtonOffsets, position.y + offsetY);
	resize.setPosition(position.x + offsetX + window.getTextureRect().width - inventoryButtonOffsets, position.y + offsetY + window.getTextureRect().height - inventoryButtonOffsets);
	title.setPosition(position.x + offsetX, position.y+ offsetY);
}
bool BaseWindow::checkMouseInside()
{
	if (open)
		if (Engine::GUI.mouseAim.position.x <= window.getLocalBounds().width + window.getPosition().x &&
			Engine::GUI.mouseAim.position.x >= window.getLocalBounds().left + window.getPosition().x)
			if (Engine::GUI.mouseAim.position.y <= window.getLocalBounds().height + window.getPosition().y &&
				Engine::GUI.mouseAim.position.y >= window.getLocalBounds().top + window.getPosition().y)
				return true;
	return false;
}