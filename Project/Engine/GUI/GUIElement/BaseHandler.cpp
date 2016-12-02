#include "BaseHandler.hpp"
#include <SFML\Graphics\RenderTarget.hpp>

std::vector<GUI::BaseHandler*> GUI::BaseHandler::elements;
std::map<const GUI::BaseHandler*, std::deque<GUI::MessageType>> GUI::BaseHandler::messages;
Vector2& GUI::BaseHandler::mousePos = Engine::GUI.mouseAim.position;
std::vector<GUI::BaseHandler*> GUI::BaseHandler::zOrder;
GUI::BaseHandler* GUI::BaseHandler::focused = NULL;
bool GUI::BaseHandler::mouseUsed = false;

std::pair<GUI::BaseHandler*, GUI::BaseHandler*> GUI::BaseHandler::swapped;

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
					
					swapped.first = *it;
					swapped.second = focused;
					return 0;
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
							focused = zOrder[size - 1];
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
		break;
	case GUI::SetResizeCoord:
	{
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

bool GUI::BaseHandler::mouseDown()
{
	for each (BaseHandler* var in components)
		if (var->visible && !mouseUsed)
			var->mouseDown();
	return mouseUsed;
}

void GUI::BaseHandler::mouseHold()
{
	for each (BaseHandler* var in components)
		if (var->visible)
			var->mouseHold();
}

void GUI::BaseHandler::mouseUp()
{
	for each (BaseHandler* var in components)
		if (var->visible)
			var->mouseUp();
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

void GUI::BaseHandler::draw(sf::RenderTarget & target, sf::RenderStates states, sf::IntRect bounding)
{
	const sf::IntRect& original = sprite.getTextureRect();
	const Vector2 originalPos = actualPos;
	const Vector2i originalSize = size;


	if (originalPos.x < bounding.left)
		actualPos.x = bounding.left;
	if (originalPos.y < bounding.top)
		actualPos.y = bounding.top;

	if (size.x > bounding.width)
		size.x = bounding.width;
	if (size.y > bounding.height)
		size.y = bounding.height;

	size = size - (originalSize - size);

	const Vector2 diff = actualPos - originalPos;
	if (diff.x > 0 || diff.y > 0)
	{
		size.x = size.x - diff.x;
		size.y = size.y - diff.y;
	}
	sprite.setPosition(actualPos.x, actualPos.y);
	//Calc the area that we want to draw
	//
	sprite.setTextureRect(sf::IntRect(diff.x , diff.y, size.x, size.y));
	target.draw(sprite);
	//Reset the area that we drew
	//
	sprite.setTextureRect(original);
	actualPos = originalPos;
	size = originalSize;
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
		if(!parent)
			target.draw(sprite);
		else
			((BaseHandler*)this)->draw(target, states, sf::IntRect(actualPos.x, actualPos.y, size.x, size.y));
		for each (BaseHandler* p in components)
			target.draw(*p);
	}
}

void GUI::BaseHandler::draw()
{
	if (zOrder.size() != 0)
	{
		size_t it = zOrder.size() - 1;
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

		if (swapped.first)
		{
			std::cout << "focused swapped from: " << swapped.second << " to " << swapped.first << "\n";
			if (swapped.second)
				swapped.second->focus = false;
			
			std::vector<BaseHandler*>::iterator it = zOrder.begin();
			//std::vector<BaseHandler*>::iterator eit = zOrder.end();
			for (it; *it != swapped.first; it++);
			zOrder.erase(it);

			zOrder.push_back(swapped.first);
			focused = zOrder.back();
			focused->focus = true;
			swapped.first = NULL;
		}
	}
}

GUI::Type GUI::BaseHandler::getType()
{
	return guiType;
}

bool GUI::BaseHandler::hasFocus()
{
	return focus;
}

void GUI::BaseHandler::registerCallbacks()
{
	Engine::Input.mouse.registerCallback([]() 
	{
		if (BaseHandler::zOrder.size() != 0)
		{
			auto it = BaseHandler::zOrder.rbegin();
			auto eit = BaseHandler::zOrder.rend();
			for (it; it != eit; it++)
				(*it)->mouseDown();
		}
	}, sf::Mouse::Left, Input::Action::Press);
	Engine::Input.mouse.registerCallback([]()
	{
		if (BaseHandler::zOrder.size() != 0)
		{
			auto it = BaseHandler::zOrder.rbegin();
			auto eit = BaseHandler::zOrder.rend();
			for (it; it != eit; it++)
				(*it)->mouseHold();
		}
	}, sf::Mouse::Left, Input::Action::Hold);
	Engine::Input.mouse.registerCallback([]() 
	{
		if (BaseHandler::zOrder.size() != 0)
		{
			auto it = BaseHandler::zOrder.rbegin();
			auto eit = BaseHandler::zOrder.rend();
			for (it; it != eit; it++)
				(*it)->mouseUp();
		}
	},sf::Mouse::Left,Input::Action::Release);
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

Vector2 GUI::BaseHandler::getPosition()
{
	return pos;
}

const Vector2i GUI::BaseHandler::getSize()
{
	return size;
}

GUI::BaseHandler* GUI::BaseHandler::getBaseHandler()
{
	return this;
}

void GUI::BaseHandler::sendMessage(const BaseHandler& base, MessageType msg)
{
	messages[&base].push_back(msg);
};

