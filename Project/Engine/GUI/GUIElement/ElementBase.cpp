#include "ElementBase.hpp"
#include <SFML\Graphics\RenderTarget.hpp>

std::vector<GUI::ElementBase*> GUI::ElementBase::elements;
std::map<const GUI::ElementBase*, std::vector<GUI::MessageType>> GUI::ElementBase::messages;
Vector2& GUI::ElementBase::mousePos = Engine::GUI.mouseAim.position;
unsigned int GUI::ElementBase::handle(MessageType msg)
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
	case GUI::Move:
	{	
		Vector2 actualpos;
		if (parent)
			actualpos = parent->pos;
		actualpos += pos;
		sprite.setPosition(actualpos.x, actualpos.y);
		for each (ElementBase* child in components)
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

bool GUI::ElementBase::isPointInside(Vector2& point)
{
	if (visible)
		if (point.x >= pos.x && point.x <= size.x + pos.x)
			if (point.y >= pos.y && point.y <= size.y + pos.y)
				return true;
	return false;
}

void GUI::ElementBase::addElement(ElementBase * base)
{
	components.push_back(base);
}

void GUI::ElementBase::enable()
{
	sendMessage(*this, GUI::Enable);
}

void GUI::ElementBase::disable()
{
	sendMessage(*this, GUI::Disable);
}

void GUI::ElementBase::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	std::vector<MessageType>& msgs = messages[this];
	while (msgs.size() != 0)
	{
		((ElementBase*)this)->handle(msgs[0]);
		msgs.erase(msgs.begin());
	}
	if (visible)
	{
		target.draw(sprite);
		for each (ElementBase* p in components)
		{
			target.draw(*p);
		}
	}
}

GUI::ElementBase::ElementBase(Type type) : guiType(type)
{
	messages.insert({ this,{} });
	elements.push_back(this);
	if (guiType == Type::e_Window)
		zOrder.push_back(this);
};

GUI::ElementBase::~ElementBase()
{
	elements.erase(std::find(elements.begin(), elements.end(), this));
	messages.erase(this);
};

void GUI::ElementBase::sendMessage(const ElementBase& base, MessageType msg)
{
	messages[&base].push_back(msg);
};
