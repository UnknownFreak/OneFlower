#include "BaseHandler.hpp"
#include <SFML\Graphics\RenderTarget.hpp>

std::vector<GUI::BaseHandler*> GUI::BaseHandler::elements;
std::map<const GUI::BaseHandler*, std::vector<GUI::MessageType>> GUI::BaseHandler::messages;
Vector2& GUI::BaseHandler::mousePos = Engine::GUI.mouseAim.position;
unsigned int GUI::BaseHandler::handle(MessageType msg)
{
	switch (msg)
	{
	case GUI::RequestFocus:
	{
		if (guiType == GUI::e_Window)
		{

		}
		// let parent know that focus is requested.
		else
			if (parent)
				sendMessage(*parent, RequestFocus);
	}
		break;
	case GUI::Close:
		visible = false;
		break;
	case GUI::Open:
		visible = true;
		break;
	case GUI::Click:
		break;
	case GUI::SetMoveCoord:
	{
		pos = mousePos - Offset;// - screenOffset
		sendMessage(*this, GUI::Move);
	}
		break;
	case GUI::Move:
	{	
		Vector2 actualpos;
		if (parent)
			actualpos = parent->pos;
		actualpos += pos;
		sprite.setPosition(actualpos.x, actualpos.y);
		for each (BaseHandler* child in components)
			sendMessage(*child, GUI::Move);
	}
		break;
	case GUI::Resize:
		break;
	case GUI::NotifyParent:
		break;
	case GUI::Enable:
		enabled = true;
		break;
	case GUI::Disable:
		enabled = false;
		break;
	default:
		break;
	}
	return 0;
}

bool GUI::BaseHandler::isPointInside(Vector2& point)
{
	return visible && point.x >= pos.x && point.x <= size.x + pos.x && point.y >= pos.y && point.y <= size.y + pos.y;
}

void GUI::BaseHandler::addElement(BaseHandler * base)
{
	components.push_back(base);
}

void GUI::BaseHandler::enable()
{
	sendMessage(*this, GUI::Enable);
}

void GUI::BaseHandler::disable()
{
	sendMessage(*this, GUI::Disable);
}

void GUI::BaseHandler::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	std::vector<MessageType>& msgs = messages[this];
	while (msgs.size() != 0)
	{
		((BaseHandler*)this)->handle(msgs[0]);
		msgs.erase(msgs.begin());
	}
	if (visible)
	{
		target.draw(sprite);
		for each (BaseHandler* p in components)
		{
			target.draw(*p);
		}
	}
}

GUI::BaseHandler::BaseHandler(Type type) : guiType(type)
{
	messages.insert({ this,{} });
	elements.push_back(this);
	if (guiType == Type::e_Window)
		zOrder.push_back(this);
};

GUI::BaseHandler::~BaseHandler()
{
	elements.erase(std::find(elements.begin(), elements.end(), this));
	messages.erase(this);
};

void GUI::BaseHandler::sendMessage(const BaseHandler& base, MessageType msg)
{
	messages[&base].push_back(msg);
};
