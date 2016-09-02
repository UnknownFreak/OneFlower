#include "ElementBase.hpp"

std::vector<GUI::ElementBase*> GUI::ElementBase::elements;
std::map<const GUI::ElementBase*, std::vector<GUI::ElementMessage>> GUI::ElementBase::messages;

unsigned int GUI::ElementBase::handle(ElementBase& guiRef, ElementMessage msg)
{
	switch (msg)
	{
	case GUI::RequestFocus:
	{
		if (guiRef.guiType == GUI::Window)
		{

		}
	}
		break;
	case GUI::Close:
		guiRef.visible = false;
		break;
	case GUI::Open:
		guiRef.visible = true;
		break;
	case GUI::Click:
	{
		switch (guiRef.mouseState)
		{
		case GUI::Down:
		{

		}
			break;
		case GUI::Hold:
		{

		}
			break;
		case GUI::Up:
		{

		}break;
		case GUI::None:
			break;
		default:
			break;
		}
	}
		break;
	case GUI::Move:
	{
		//TODO:
	}
		break;
	case GUI::Resize:
	{
		//TODO:
	}
		break;
	case GUI::NotifyParent:
		break;
	case GUI::Enable:
		guiRef.enabled = true;
		break;
	case GUI::Disable:
		guiRef.enabled = false;
		break;
	default:
		break;
	}
	return 0;
}

bool GUI::ElementBase::isPointInside(Vector2 point)
{
	if (visible)
		if (point.x >= pos.x &&
			point.x <= size.x + pos.x)
			if (point.y >= pos.y &&
				point.y <= size.y + pos.y)
				return true;
	return false;
}

void GUI::ElementBase::addElement(ElementBase * base)
{
	components.push_back(base);
}
