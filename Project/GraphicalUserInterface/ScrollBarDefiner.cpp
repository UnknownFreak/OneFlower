#include "ScrollBar.hpp"
#include "../Engine.hpp"
#include "../Component/InventoryComponent.hpp"
#include "../Item/Bag.hpp"
#include "BaseWindowObject.hpp"
#include "WindowIcon.hpp"
ScrollBar::ScrollBar(int x, int y, int sizeX, int sizeY, int iconSize, Vector2 iconOffset, BaseWindow* parent, bool swapItems) : scrollLine(sf::PrimitiveType::LinesStrip, 2),
top("ScrollBarArrowUp.png", 8, 8, x, y),
bot("ScrollBarArrowDown.png", 8, 8, x, y + sizeY), scrolling(false),
scroll("ScrollBar.png", 8, 4, x, y + 8), parent(parent),
offset(parent->position.x, parent->position.y), canSwapItems(swapItems),
iconSize(iconSize), iconOffset(iconOffset), position(x, y), size(sizeX, sizeY)
, tooltip(NULL, ToolTip())
{
	setPosition(x, y);
}
void ScrollBar::draw()
{
	scrollHandle();
	if (_draw)
	{
		Engine::View.render.draw(scrollLine);
		top.draw();
		bot.draw();
		scroll.draw();
	}
	int i = 0;
	Vector2 off(offset);
	for (std::vector<BaseWindowObject*>::iterator it = sprites.begin(); it != sprites.end(); it++)
	{
		BaseWindowObject* obj = *it;
		if (obj)
		{
			obj->setPosition(off.x, off.y - scrolled);
			drawIcon(*obj, off, i);
			setTiles(off);
			++i;
		}
	}
	checkIfScrollBar(off);
	i = 0;
	off = offset;
}
void ScrollBar::setPosition(int x, int y)
{
	position.x = x;
	position.y = y;
	offset.x = position.x + 60;
	offset.y = position.y + 6;
	scrollLine[0].position = sf::Vector2f(position.x + size.x + 3.5, position.y + 1);
	scrollLine[1].position = sf::Vector2f(position.x + size.x + 3.5, position.y + size.y);
	top.setPosition(position.x + size.x, position.y);
	bot.setPosition(position.x + size.x, position.y + size.y);
	scroll.setPosition(position.x + size.x, top.getPosition().y + 8 + (((bot.getPosition().y - 16 - scroll.icon.getTextureRect().height) - top.getPosition().y + 8) * (scrolled / maxScrolls)));
}
void ScrollBar::setTiles(Vector2& off)
{
	off.x += iconSize + iconOffset.x;
	if (off.x > top.icon.getPosition().x - iconSize - iconOffset.x)
	{
		off.y += iconSize + iconOffset.y;
		off.x = offset.x;
	}
}
void ScrollBar::checkIfScrollBar(Vector2&off)
{
	float width = top.icon.getPosition().x - offset.x;
	float itemsPerRow_f = width / (iconSize + iconOffset.x);
	float iconOutside = off.y - bot.getPosition().y + 8;
	float windowSize = bot.getPosition().y + 8 - offset.y;
	float totalRows_f = sprites.size() / itemsPerRow_f;

	int itemsPerRow = int(itemsPerRow_f);
	int totalRows = int(totalRows_f);

	if (itemsPerRow > itemsPerRow_f + 0.5f)
		--itemsPerRow;
	if (totalRows > totalRows_f)
		--totalRows;
	
	maxScrolls = iconOutside + iconSize;
	float itemsInWindow = (windowSize) / (iconSize + iconOffset.y);
	deltaScrolls = itemsInWindow / (totalRows);
	int size = (bot.getPosition().y - (top.getPosition().y + 8)) * deltaScrolls;
	setScrollBarSize(size);

	if (deltaScrolls > 1 || deltaScrolls <= 0)
		_draw = false;
	else
		_draw = true;
}
void ScrollBar::setScrollBarSize(int size)
{
	scroll.icon.setTextureRect(sf::IntRect(0, 0, 8, size));
}
void ScrollBar::setSizeY(int len)
{
	size.y = len;
}
bool ScrollBar::checkCulling(sf::Sprite* sprite, Vector2& position)
{
	if (position.y - scrolled > top.getPosition().y && position.y - scrolled + iconSize < bot.getPosition().y + 8)
	{
		sprite->setTextureRect(sf::IntRect(sprite->getTextureRect().left, 0, iconSize, iconSize));
		return true;
	}
	else if (position.y - scrolled + iconSize > top.getPosition().y && !(position.y - scrolled + iconSize + iconOffset.y > bot.getPosition().y + 8))
	{
		int minSize = sprite->getPosition().y + iconSize;
		int topSize = top.getPosition().y;
		sprite->setTextureRect(sf::IntRect(sprite->getTextureRect().left, iconSize - (minSize - topSize), iconSize, (minSize - topSize)));
		sprite->setPosition(position.x, top.getPosition().y);
		return true;
	}
	else if (position.y - scrolled < bot.getPosition().y && position.y - scrolled + iconSize + iconOffset.y > bot.icon.getPosition().y + 8)
	{
		int minSize = sprite->getPosition().y + iconSize;
		int topSize = bot.getPosition().y + 8;
		sprite->setTextureRect(sf::IntRect(sprite->getTextureRect().left, 0, iconSize, iconSize - (minSize - topSize)));
		return true;
	}
	return false;
}
void ScrollBar::scrollHandle()
{
	if (_draw)
	{
		if (top.onHover() && Engine::Input.mouse.leftClick())
		{
			scrolled -= 8;
			if (scrolled < 0)
				scrolled = 0;
		}
		if (bot.onHover() && Engine::Input.mouse.leftClick())
		{
			scrolled += 8;
			if (scrolled > maxScrolls)
				scrolled = maxScrolls;
		}
		if (scroll.onHover() && Engine::Input.mouse.leftClick())
			scrolling = true;

		if (scrolling && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			if (mousePosY < Engine::Input.mouse.pos.y)
			{
				scrolled += Engine::Input.mouse.pos.y - mousePosY;
				mousePosY = Engine::Input.mouse.pos.y;
			}
			else if (mousePosY > Engine::Input.mouse.pos.y)
			{
				scrolled -= mousePosY - Engine::Input.mouse.pos.y;
				mousePosY = Engine::Input.mouse.pos.y;
			}
			else
				mousePosY = Engine::Input.mouse.pos.y;
			if (scrolled < 0)
				scrolled = 0;
			else if (scrolled > maxScrolls)
				scrolled = maxScrolls;
		}
		else if (scrolling)
			scrolling = false;
		scroll.setPosition(scroll.getPosition().x, top.getPosition().y + 8 + (((bot.getPosition().y - 16 - scroll.icon.getTextureRect().height) - top.getPosition().y + 8) * (scrolled / maxScrolls)));
	}
	if (movingItem && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		if (selected)
		{
			selected->setColor(sf::Color(255, 255, 255, 127));
			selected->setPosition(Engine::GUI.mouseAim.position.x, Engine::GUI.mouseAim.position.y);
			Engine::View.render.draw(*selected);
			selected->setColor(sf::Color(255, 255, 255, 255));
		}
	}
	else if (!canSwapItems)
	{
		if (selected)
		{
			selected->setColor(sf::Color(255, 255, 255, 127));
			selected->setPosition(Engine::GUI.mouseAim.position.x, Engine::GUI.mouseAim.position.y);
			Engine::View.render.draw(*selected);
			selected->setColor(sf::Color(255, 255, 255, 255));
		}
	}
	else if (movingItem && !mouseInsideIcon(*selected) && canSwapItems && mouseInside())
	{
		movingItem = false;
		requestSwap = true;
	}
	else if (movingItem && !mouseInside() && !equipItem)
	{
		movingItem = false;
		requestSwap = false;
	}
	else
	{
		movingItem = false;
	}
}
void ScrollBar::setSizeX(int x)
{
	size.x = x;
}
bool ScrollBar::mouseInsideIcon(sf::Sprite& sprite)
{
	if (Engine::GUI.mouseAim.position.x <= sprite.getLocalBounds().width + sprite.getPosition().x &&
		Engine::GUI.mouseAim.position.x >= sprite.getLocalBounds().left + sprite.getPosition().x)
		if (Engine::GUI.mouseAim.position.y <= sprite.getLocalBounds().height + sprite.getPosition().y &&
			Engine::GUI.mouseAim.position.y >= sprite.getLocalBounds().top + sprite.getPosition().y)
			return true;
	return false;
}
void ScrollBar::drawIcon(BaseWindowObject& obj, Vector2& off, int i)
{
	if (obj.type == 1)
	{
		WindowIcon& ico = (WindowIcon&)obj;
		if (checkCulling(&ico.icon, off))
		{
			if (mouseInsideIcon(ico.icon) && !movingItem)
			{
				ico.icon.setColor(sf::Color(150, 150, 150));
				ico.draw();
				ico.icon.setColor(sf::Color(255, 255, 255));

				if (ico.toolTipBody != "")
				{
					tooltip.first = &ico.icon;
					tooltip.second.setToolTipText(ico.toolTipTitle, ico.toolTipBody);
				}
				if (Engine::Input.mouse.leftClick() && canSwapItems && parent->focus && ico.toolTipBody != "" ||
					Engine::Input.mouse.leftClick() && canSwapItems && ico.toolTipBody != "" && !Engine::GUI.focusedWindow->checkMouseInside() || 
					canSwapItems && parent->requestFocus && ico.toolTipBody != "")
				{
					movingItem = true;
					selected = &ico.icon;
					selectedBag = i;
				}
			}
			else if (mouseInsideIcon(ico.icon) && movingItem && &ico.icon != selected)
			{
				InventoryComponent* icp = Engine::Window.focus.gameObject->GetComponent<InventoryComponent>();
				swapBag = i;
				int bagSwapIndex = i;
				int droppedIndex = 0;
				for (size_t it = 0; it < icp->bags.size(); ++it)
					if (icp->bags[it]->size > bagSwapIndex)
					{
						droppedIndex = it;
						break;
					}
					else
						bagSwapIndex -= icp->bags[it]->size;
				if (icp->bags[droppedIndex]->items[bagSwapIndex].first && unequipBag && ico.toolTipBody != "")
				{
					ico.icon.setColor(sf::Color(150, 25, 25));
					ico.draw();
					ico.icon.setColor(sf::Color(255, 255, 255));
				}
				else
				{
					ico.icon.setColor(sf::Color(25, 150, 25));
					ico.draw();
					ico.icon.setColor(sf::Color(255, 255, 255));
				}
			}
			else if (mouseInsideIcon(ico.icon) && movingItem)
			{
				
				ico.icon.setColor(sf::Color(150, 25, 25));
				ico.draw();
				ico.icon.setColor(sf::Color(255, 255, 255));
			}
			else
				ico.draw();
			if (movingItem && !mouseInside())
			{
				tooltip.first = NULL;
				equipItem = true;
			}
			else
				equipItem = false;
		}
	}
}
bool ScrollBar::getIfMovingItem()
{
	return movingItem;
}
bool ScrollBar::mouseInside()
{
	if (Engine::GUI.mouseAim.position.x <= parent->window.getTextureRect().width + parent->window.getPosition().x &&
		Engine::GUI.mouseAim.position.x >= parent->window.getTextureRect().left + parent->window.getPosition().x + 60)
		if (Engine::GUI.mouseAim.position.y <= parent->window.getTextureRect().height + parent->window.getPosition().y &&
			Engine::GUI.mouseAim.position.y >= parent->window.getTextureRect().top + parent->window.getPosition().y)
			return true;
	return false;
}
void ScrollBar::setScroll(float deltaScroll)
{
	deltaScroll *= 8;
	if (_draw)
	{
		scrolled -= deltaScroll;
		if (scrolled < 0)
			scrolled = 0;
		else if (scrolled > maxScrolls)
			scrolled = maxScrolls;
	}
}