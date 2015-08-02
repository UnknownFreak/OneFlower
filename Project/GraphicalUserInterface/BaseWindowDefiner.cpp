#include "BaseWindow.hpp"
#include "../Engine.hpp"

BaseWindow::BaseWindow(float x, float y, int sizeX, int sizeY, bool resizeable, std::string title) : close("WindowIcons.png", sf::IntRect(0, 0, Engine::Graphic.requestTexture("WindowIcons.png")->getSize().x / 2, Engine::Graphic.requestTexture("WindowIcons.png")->getSize().y), x + sizeX - 16, sizeY, ""),
window(*Engine::Graphic.requestTexture("DefaultWindow.png"), sf::IntRect(0, 0, sizeX, sizeY)),
resize("WindowIcons.png", sf::IntRect(Engine::Graphic.requestTexture("WindowIcons.png")->getSize().x / 2, 0, Engine::Graphic.requestTexture("WindowIcons.png")->getSize().x / 2, Engine::Graphic.requestTexture("WindowIcons.png")->getSize().y), x + sizeX - 16, y + sizeY - 16, ""),
clickOffset(0, 0), position(x, y), drawResizeIcon(resizeable), title(*Engine::Graphic.font.requestFont("arial.ttf")),
outline(sf::LinesStrip,5)
{
	double scaleX = 16 / (Engine::Graphic.requestTexture("WindowIcons.png")->getSize().x / 2);
	double scaleY = 16 / Engine::Graphic.requestTexture("WindowIcons.png")->getSize().y;
	close.icon.setScale(scaleX, scaleY);
	resize.icon.setScale(scaleX, scaleY);

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
	Engine::Graphic.view.render.draw(window);
	Engine::Graphic.view.render.draw(outline);
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
	/*
	outline[0].position = sf::Vector2f(position.x, position.y);
	outline[1].position = sf::Vector2f(position.x + window.getTextureRect().width, position.y);
	outline[2].position = sf::Vector2f(position.x + window.getTextureRect().width, position.y + window.getTextureRect().height);
	outline[3].position = sf::Vector2f(position.x, position.y + window.getTextureRect().height);
	outline[4].position = sf::Vector2f(position.x, position.y);
	*/
}
void BaseWindow::Iresize(float x, float y)
{
	float x1 = x - window.getPosition().x;
	float y1 = y - window.getPosition().y;
	if (x1 < 220)
		x1 = 220;
	if (y1 < 290)
		y1 = 290;
	window.setTextureRect(sf::IntRect(0, 0, (int)x1, (int)y1));
	outline[1].position = sf::Vector2f(window.getPosition().x + x1, window.getPosition().y);
	outline[2].position = sf::Vector2f(window.getPosition().x + x1, window.getPosition().y + y1);
	outline[3].position = sf::Vector2f(window.getPosition().x, window.getPosition().y + y1);

}
void BaseWindow::checkMouseOffset(double&x, double &y)
{
	float width = Engine::Graphic.view.camera.getSize().x;
	float height = Engine::Graphic.view.camera.getSize().y;
	if (x > Engine::Graphic.view.camera.getCenter().x + width / 2 - 50)
		x = Engine::Graphic.view.camera.getCenter().x + width / 2 - 50;
	if (x < Engine::Graphic.view.camera.getCenter().x - width / 2)
		x = Engine::Graphic.view.camera.getCenter().x - width / 2;
	if (y > Engine::Graphic.view.camera.getCenter().y + height / 2 - 30)
		y = Engine::Graphic.view.camera.getCenter().y + height / 2 - 30;
	if (y < Engine::Graphic.view.camera.getCenter().y - height / 2)
		y = Engine::Graphic.view.camera.getCenter().y - height / 2;
}
void BaseWindow::WindowHandle()
{
	// check if user clicked inside a window that does not have focus - then request focus for that window
	if (!focus && !Engine::GUI.focusedWindow->checkMouseInside() && checkMouseInside() && !Engine::GUI.focusedWindow->moving && !Engine::GUI.focusedWindow->resizeing
		&& !Engine::GUI.focusedWindow->windowLClick)
	{
		if (Engine::Input.mouse.leftClick() || sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			requestFocus = true;
			Engine::GUI.updateFocus = true;
		}
	}
	// check if the user clicked inside a window with focus.
	if (checkMouseInside() && (focus || requestFocus))
	{
		if (Engine::Input.mouse.leftClick())
			windowLClick = true;
		else if (Engine::Input.mouse.rightClick())
			windowRClick = true;
		else
		{
			windowLClick = false;
			windowRClick = false;
		}
	}
	//User hovers over the close button. in window that has focus, or a window that has the close button visible and has no focus, or if the window requests focus
	if (close.onHover() && Engine::GUI.focusedWindow->checkMouseInside() && Engine::GUI.focusedWindow == this && !moving ||
		close.onHover() && !Engine::GUI.focusedWindow->checkMouseInside() && !moving ||
		close.onHover() && requestFocus && !moving)
	{
		if (windowLClick || requestFocus)
			requestClose = true;
	}
	// User hovers over the resize button (if it is drawn), same as above description
	if (resize.onHover() && drawResizeIcon && Engine::GUI.focusedWindow->checkMouseInside() && Engine::GUI.focusedWindow == this && !moving ||
		resize.onHover() && drawResizeIcon && !Engine::GUI.focusedWindow->checkMouseInside() && !moving)
		if (windowLClick || requestFocus)
			resizeing = true;
		
	if (MouseInsideTitleBar() && Engine::GUI.focusedWindow->checkMouseInside() && Engine::GUI.focusedWindow == this ||
		MouseInsideTitleBar() && !Engine::GUI.focusedWindow->checkMouseInside() || 
		MouseInsideTitleBar() && requestFocus)
	{
		if (windowLClick || requestFocus)
		{
			moving = true;
			clickOffset.x = Engine::Input.mouse.pos.x - window.getPosition().x;
			clickOffset.y = Engine::Input.mouse.pos.y - window.getPosition().y;
		}
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && resizeing)
		Iresize(Engine::Input.mouse.pos.x, Engine::Input.mouse.pos.y);
	else if (resizeing)
		resizeing = false;
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && moving && (focus || requestFocus))
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
	offsetX = Engine::Graphic.view.camera.getCenter().x - (800 * Engine::Graphic.view.camera.getViewport().width / 2);
	offsetY = Engine::Graphic.view.camera.getCenter().y - (600 * Engine::Graphic.view.camera.getViewport().height / 2);
	window.setPosition(position.x + offsetX, position.y + offsetY);
	close.setPosition(position.x + offsetX + window.getTextureRect().width - inventoryButtonOffsets, position.y + offsetY);
	resize.setPosition(position.x + offsetX + window.getTextureRect().width - inventoryButtonOffsets, position.y + offsetY + window.getTextureRect().height - inventoryButtonOffsets);
	title.setPosition(position.x + offsetX, position.y+ offsetY);

	outline[0].position = sf::Vector2f(position.x + offsetX, position.y + offsetY);
	outline[1].position = sf::Vector2f(position.x + offsetX + window.getTextureRect().width, position.y + offsetY);
	outline[2].position = sf::Vector2f(position.x + offsetX + window.getTextureRect().width, position.y + offsetY + window.getTextureRect().height);
	outline[3].position = sf::Vector2f(position.x + offsetX, position.y + offsetY + window.getTextureRect().height);
	outline[4].position = sf::Vector2f(position.x + offsetX, position.y + offsetY);
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