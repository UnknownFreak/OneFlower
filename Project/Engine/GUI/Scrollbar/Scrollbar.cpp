#include "Scrollbar.hpp"

unsigned int GUI::Scrollbar::handle(MessageType msg)
{
	return BaseHandler::handle(msg);
}

void GUI::Scrollbar::addItem(BaseHandler * item)
{
	itemList.push_back(item);
	itemCount++;
}

bool GUI::Scrollbar::removeItem(BaseHandler * item)
{
	std::vector<BaseHandler*>::iterator start = itemList.begin();
	std::vector<BaseHandler*>::iterator end = itemList.end();
	for (start; start != end; start++)
		if (*start == item)
		{
			itemList.erase(start);
			itemCount--;
			return true;
		}
	return false;
}

bool GUI::Scrollbar::removeItem(size_t index)
{
	if (index > -1 && index < itemCount + 1)
		itemList.erase(itemList.begin() + index);
	else
		return false;
	itemCount--;
	return true;
}

void GUI::Scrollbar::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (visible)
	{
		size_t i = 0, max = this->itemsThatCanBeDisplayed;
		BaseHandler::draw(target, states);
		for (i; i < max && (i + scrollPos < itemCount); i++)
			itemList[i + scrollPos]->draw(target, states, sf::IntRect(pos.x, pos.y, size.x, size.y));
	}
}
