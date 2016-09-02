#include "../../../Engine.hpp"
#include "Window.hpp"

//has to remove old gui stuff before cause namespace conflicts with name
void GUI::Window::mouseHandle()
{
	// returns true if the mouse is inside this window, and the window is open and enabled, it sends a click event;
	if(isPointInside(Engine::Input.mouse.pos) && enabled)
		sendMessage(*this, Click);
}

GUI::Window::Window() : ElementBase(GUI::Element::Window)
{
	parent = NULL;
}

void GUI::Window::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (visible)
	{
		target.draw(backgroundSprite);
	}
}

unsigned int GUI::Window::handle(ElementBase & guiRef, ElementMessage msg)
{

	switch (msg)
	{
	case GUI::RequestFocus:
		break;
	case GUI::Close:
		break;
	case GUI::Open:
		break;
	case GUI::Click:
		break;
	case GUI::Move:
		backgroundSprite.setPosition(pos.x,pos.y);
		return 0;
	case GUI::Resize:
		backgroundSprite.setTextureRect(sf::IntRect(0, 0, size.x, size.y));
		return 0;
	case GUI::NotifyParent:
		break;
	case GUI::Enable:
		break;
	case GUI::Disable:
		break;
	default:
		break;
	}

	return ElementBase::handle(guiRef, msg);
}
