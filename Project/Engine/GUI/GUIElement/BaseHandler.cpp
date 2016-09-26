#include "BaseHandler.hpp"
#include <SFML\Graphics\RenderTarget.hpp>

std::vector<GUI::BaseHandler*> GUI::BaseHandler::elements;
std::map<const GUI::BaseHandler*, std::deque<GUI::MessageType>> GUI::BaseHandler::messages;
Vector2& GUI::BaseHandler::mousePos = Engine::GUI.mouseAim.position;
std::vector<GUI::BaseHandler*> GUI::BaseHandler::zOrder;
GUI::BaseHandler* GUI::BaseHandler::focused = NULL;
bool GUI::BaseHandler::mouseUsed = false;
unsigned int GUI::BaseHandler::handle(MessageType msg)
{
	switch (msg)
	{
	case GUI::Click:
	{
		if (mouseState & GUI::Down)
		{
			mouseState = (MouseState)(mouseState & ~GUI::Down);
			Offset = mousePos - pos;
		}
		break;
	}
	case GUI::RequestFocus:
	{
		if (guiType == GUI::e_Window)
		{
			std::vector<BaseHandler*>::iterator it = zOrder.begin();
			std::vector<BaseHandler*>::iterator eit = zOrder.end();
			for (it; it != eit; it++)
			{
				if (*it == this && this != focused)
				{
					std::cout << "focused swapped from: " << focused << " to " << this << "\n";
					if(focused)
						focused->focus = false;
					std::swap(*it, zOrder.back());
					focused = zOrder.back();
					focused->focus = true;
				}
			}
		}
		// let parent know that focus is requested.
		else
			if (parent)
				sendMessage(*parent, RequestFocus);
	}
		break;
	case GUI::Close:
	{
		if (guiType == GUI::e_Window && visible)
		{
			size_t it = 0;
			size_t size = zOrder.size();
			for (it; it < size; it++)
				if (zOrder[it] == this)
				{
					if (this == focused)
					{
						focused->focus = false;
						if (size < 1)
							focused = NULL;
						else
						{
							focused = zOrder[size - 2];
							focused->focus = true;
						}
					}
					zOrder.erase(zOrder.begin() + it);
					visible = false;
					return 0;
				}
		}
	}
		break;
	case GUI::Open:
	{
		if (guiType == GUI::e_Window && !visible)
		{
			zOrder.push_back(this);
			if(focused)
				focused->focus = false;
			focused = this;
			focused->focus = true;
		}
		visible = true;
	}
		break;
	case GUI::SetMoveCoord:
	{
		pos = mousePos - Offset;// - screenOffset
		sendMessage(*this, GUI::Move);
	}
	case GUI::SetResizeCoord:
	{
		Offset = mousePos - pos;
		sendMessage(*this, GUI::Resize);
	}
		break;
	case GUI::Move:
	{	
		actualPos = Vector2(0, 0);
		if (parent)
			actualPos = parent->pos;
		actualPos += pos;
		sprite.setPosition(actualPos.x, actualPos.y);
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
	case GUI::Hide:
		visible = false;
		break;
	case GUI::Show:
		visible = true;
		break;
	default:
		break;
	}
	return 0;
}

bool GUI::BaseHandler::isPointInside(Vector2& point)
{
	return visible && point.x >= actualPos.x && point.x <= size.x + actualPos.x && point.y >= actualPos.y && point.y <= size.y + actualPos.y;
}

void GUI::BaseHandler::addComponent(BaseHandler * base)
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
	std::deque<MessageType>& msgs = messages[this];
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

void GUI::BaseHandler::draw()
{
	size_t it = zOrder.size()-1;
	size_t eit = 0;
	//parse all the messages for the topMostWindow first
	for (it; it > eit; it--)
	{
		std::deque<MessageType>& msgs = messages[zOrder[it]];
		while (msgs.size() != 0)
		{
			zOrder[it]->handle(msgs[0]);
			msgs.pop_front();
		}
	}

	it = 0;
	eit = zOrder.size();
	for (it; it < eit; it++)
		Engine::Graphic.view.render.draw(*zOrder[it]);
}

GUI::Type GUI::BaseHandler::getType()
{
	return guiType;
}

bool GUI::BaseHandler::hasFocus()
{
	return focus;
}

GUI::BaseHandler::BaseHandler(Type type) : guiType(type)
{
	messages.insert({ this,{} });
	elements.push_back(this);
	if (guiType == Type::e_Window)
		zOrder.push_back(this);
}
GUI::BaseHandler::BaseHandler(const BaseHandler & copy) : guiType(copy.guiType), focus(copy.focus), visible(copy.visible),
enabled(copy.enabled), resizeAble(copy.resizeAble), moveAble(copy.moveAble), pos(copy.pos), Offset(copy.pos), parent(copy.parent),
components(copy.components), sprite(copy.sprite), minResizeSize(copy.minResizeSize), size(copy.size)
{
	messages.insert({ this , {} });
	elements.push_back(this);
	if (guiType == Type::e_Window)
		zOrder.push_back(this);
}

GUI::BaseHandler::~BaseHandler()
{
	elements.erase(std::find(elements.begin(), elements.end(), this));
	messages.erase(this);
}
void GUI::BaseHandler::setPosition(Vector2 newPos)
{
	pos = newPos;
	sendMessage(*this, GUI::Move);
}

const Vector2i GUI::BaseHandler::getSize()
{
	return size;
}

GUI::BaseHandler * GUI::BaseHandler::getBaseHandler()
{
	return this;
}

void GUI::BaseHandler::sendMessage(const BaseHandler& base, MessageType msg)
{
	messages[&base].push_back(msg);
};
