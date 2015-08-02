#include "GraphicalInventory.hpp"
#include <Windows.h>
#include "../Engine.hpp"
#include <vector>
#include "../Item/Bag.hpp"
#include "../Component/InventoryComponent.hpp"
#include "WindowIcon.hpp"

GraphicalInventory::GraphicalInventory(int x1, int y1, int x2, int y2) : BaseWindow(x1, y1, x2, y2, true, "Inventory"),
emptyInventorySlot(*Engine::Graphic.requestTexture("InventoryEmptyIcon.png"), sf::IntRect(0, 0, 32, 32)),
scroll(x1, y1 + 24, 0, 4, 32, Vector2(5, 5), this, true),
toolTip("None"), item(NULL), gold("coins.png", *Engine::Graphic.font.requestFont("Arial.ttf"),false, 0, 0, -16, 0)
{
	gold.setSize(13);
	emptyInventorySlot.setColor(sf::Color(255, 255, 255));
	window.setPosition(x1, y1);
	sf::Texture * tx = Engine::Graphic.requestTexture("ToolTipIcon.png");
	tx->setRepeated(true);
}
void GraphicalInventory::draw()
{
	if (open)
	{
		if (!createdInventory)
		{
			CreateScrollItems();
		}
		move();
		WindowHandle();
		BaseWindow::draw();
		IconDrawHandle();
		IconSelectHandle();
		if (scroll.tooltip.first && !scroll.movingItem && Engine::GUI.showToolTip && Engine::GUI.focusedWindow->checkMouseInside() && Engine::GUI.focusedWindow == (BaseWindow*)this ||
			scroll.tooltip.first && !scroll.movingItem && Engine::GUI.showToolTip && !Engine::GUI.focusedWindow->checkMouseInside())
			if (scroll.mouseInsideIcon(*scroll.tooltip.first) && scroll.tooltip.second.getToolTipBody() != "")
			{
				Engine::GUI.openedWindowToolTip.setToolTipText(scroll.tooltip.second.getToolTipTitle(), scroll.tooltip.second.getToolTipBody());
				Engine::GUI.drawOpenedWindowToolTip = true;
			}
	}
}
void GraphicalInventory::CreateScrollItems()
{
	for (auto it = scroll.sprites.begin(); it != scroll.sprites.end(); ++it)
	{
		delete *it;
		*it = NULL;
	}
	scroll.sprites.clear();
	GameObject* go = Engine::Window.focus.gameObject;
	if (go)
	{
		if (go->GetComponent<InventoryComponent>())
		{
			int max = go->GetComponent<InventoryComponent>()->maxBags;
			std::vector<Bag*>& b = go->GetComponent<InventoryComponent>()->bags;
			for (int it = 0; it < max; it++)
			{
				int i = 0;
				if (it < b.size())
				{
					Bag* bag = b[it];
					for (std::vector<std::pair<Item*, int>>::iterator iit = bag->items.begin(); iit != bag->items.end(); iit++)
					{
						if (iit->first)
							scroll.sprites.push_back(new WindowIcon(iit->first->icon, iit->first->name, iit->first->toToolTipString(), std::to_string(iit->second), Vector2(0, 16),std::pair<int,int>(it,i)));
						else
							scroll.sprites.push_back(new WindowIcon(emptyInventorySlot, "", "", "", Vector2(0, 16),std::pair<int,int>(it,i)));
						i++;
					}
				}
			}
		}
	}
	if (scroll.sprites.size() > 0)
		createdInventory = true;
}
void GraphicalInventory::WindowHandle()
{
	scroll.setSizeY(window.getTextureRect().height - 80);
	scroll.setSizeX(window.getTextureRect().width - 8);
	scroll.setPosition(position.x + offsetX, position.y + 40 + offsetY);
	gold.setPosition(window.getPosition().x + window.getTextureRect().width - 16, window.getPosition().y + window.getTextureRect().height - 20);
	BaseWindow::WindowHandle();
}
bool GraphicalInventory::mouseInsideIcon(sf::Sprite& sprite)
{
	if (Engine::GUI.mouseAim.position.x <= sprite.getLocalBounds().width + sprite.getPosition().x &&
		Engine::GUI.mouseAim.position.x >= sprite.getLocalBounds().left + sprite.getPosition().x)
		if (Engine::GUI.mouseAim.position.y <= sprite.getLocalBounds().height + sprite.getPosition().y &&
			Engine::GUI.mouseAim.position.y >= sprite.getLocalBounds().top + sprite.getPosition().y)
			return true;
	return false;
}
void GraphicalInventory::IconDrawHandle()
{
	
	GameObject* go = Engine::Window.focus.gameObject;
	if (go)
		if (go->GetComponent<InventoryComponent>())
		{
			std::string sgold = std::to_string(go->GetComponent<InventoryComponent>()->coins);
			if (sgold.size() > 4)
				gold.setOffset(-(6*16),0);
			else if (sgold.size() > 2)
				gold.setOffset(-(4 * 16), 0);
			else
				gold.setOffset(-(2 * 16), 0);
			gold = "§Icon|coins|16|0|" + sgold;
			gold.draw();
			int max = go->GetComponent<InventoryComponent>()->maxBags;
			std::vector<Bag*>& b = go->GetComponent<InventoryComponent>()->bags;
			Vector2 off(window.getPosition().x + 10.f, window.getPosition().y + 46.f);
			for (int it = 0; it < max; it++)
			{
				if (it < b.size())
				{
					Bag* bag = b[it];
					bag->icon.setPosition(off.x, off.y);
					if (item)
						if (mouseInsideIcon(bag->icon) && scroll.getIfMovingItem() && scroll.equipItem)
						{
							bag->icon.setColor(sf::Color(150, 25, 25));
							Engine::Graphic.view.render.draw(bag->icon);
							bag->icon.setColor(sf::Color(255, 255, 255));
							off.y += iconSize + iconOffset;
							continue;
						}
					Engine::Graphic.view.render.draw(bag->icon);
				}
				else
				{
					if (tryEquipBag(off))
						continue;
				}
				off.y += iconSize + iconOffset;
			}
			scroll.draw();
		}
}
void GraphicalInventory::ClickOnBagSlot(Bag* bag)
{
	if (mouseInsideIcon(bag->icon) && !scroll.movingItem)
	{
		if (Engine::Input.mouse.leftClick())
		{
			clickOffset.x = Engine::Input.mouse.pos.x - bag->icon.getPosition().x;
			clickOffset.y = Engine::Input.mouse.pos.y - bag->icon.getPosition().y;
			scroll.movingItem = true;
			bagSlotSelected = true;
			scroll.unequipBag = true;
			scroll.selectedBag = bag->freeSlots;
			item = bag;
			scroll.selected = &bag->icon;
		}
		if (Engine::GUI.showToolTip && Engine::GUI.focusedWindow->checkMouseInside() && Engine::GUI.focusedWindow == (BaseWindow*)this || 
			Engine::GUI.showToolTip && !Engine::GUI.focusedWindow->checkMouseInside())
		{
			Engine::GUI.openedWindowToolTip.setToolTipText(bag->name, bag->toToolTipString());
			Engine::GUI.drawOpenedWindowToolTip = true;
		}
	}
}
void GraphicalInventory::swap()	
{
	if (Engine::event.type == Engine::event.MouseButtonReleased)
	{
		if (Engine::event.mouseButton.button == sf::Mouse::Button::Left && scroll.selectedBag !=-1 && scroll.swapBag != -1)
		{
			WindowIcon* selected = (WindowIcon*)(scroll.sprites[scroll.selectedBag]);
			WindowIcon* swap = (WindowIcon*)(scroll.sprites[scroll.swapBag]);
			InventoryComponent* icp = Engine::Window.focus.gameObject->GetComponent<InventoryComponent>();

			if (scroll.requestSwap && !bagSlotSelected && scroll.mouseInside() && !scroll.equipItem)
			{
				if (icp->swapItem(icp->bags[selected->index.first], selected->index.second, icp->bags[swap->index.first], swap->index.second))
				{
					scroll.requestSwap = false;
					scroll.movingItem = false;

					scroll.tooltip.first = NULL;

					BaseWindowObject* tmp = scroll.sprites[scroll.selectedBag];
					scroll.sprites[scroll.selectedBag] = scroll.sprites[scroll.swapBag];
					scroll.sprites[scroll.swapBag] = tmp;

					std::pair<int, int> tmp_two = ((WindowIcon*)scroll.sprites[scroll.selectedBag])->index;
					((WindowIcon*)scroll.sprites[scroll.selectedBag])->index = ((WindowIcon*)scroll.sprites[scroll.swapBag])->index;
					((WindowIcon*)scroll.sprites[scroll.swapBag])->index = tmp_two;
					Engine::GUI.stats.updateEquipment = true;
				}
			}
			else if (scroll.requestSwap && bagSlotSelected && scroll.mouseInside())
			{
				int start = 0;
				int end = 0;
				for (std::vector<Bag*>::iterator it = icp->bags.begin(); it != icp->bags.end(); it++)
					{
						Bag* tmp = *it;
						Bag* itm = (Bag*)item;
						if (tmp == itm)
						{
							end += itm->size;
							break;
						}
						end += tmp->size;
						start += tmp->size;
					}
				if (icp->unequipBag((Bag*)item, icp->bags[swap->index.first], swap->index.second))
				{
					int insertLocationBag = 0;
					for (size_t i = 0; i < swap->index.first; i++)
					{
						insertLocationBag += icp->bags[i]->size;
					}
					insertLocationBag += swap->index.second;
					
					WindowIcon* itm = (WindowIcon*)scroll.sprites[insertLocationBag];
					itm->icon = item->icon;
					itm->messageText = "1";
					itm->toolTipTitle = item->name; 
					itm->toolTipBody = item->toToolTipString();
					for (std::vector<BaseWindowObject*>::iterator it = scroll.sprites.begin() + start; it != scroll.sprites.begin() + end; it++)
					{
						delete *it;
						*it = NULL;
					}
					scroll.sprites.erase(scroll.sprites.begin() + start, scroll.sprites.begin() + end);
					
					scroll.movingItem = false;
					scroll.requestSwap = false;
					scroll.unequipBag = false;
					bagSlotSelected = false;
				}
			}
			if (!scroll.movingItem)
			{
				scroll.selectedBag = -1;
				scroll.swapBag = -1;
				scroll.requestSwap = false;
				bagSlotSelected = false;
				scroll.unequipBag = false;
				item = NULL;
			}
		}
	}
}
void GraphicalInventory::IconSelectHandle()
{
	GameObject* go = Engine::Window.focus.gameObject;
	if (go)
	{
		InventoryComponent* icp = go->GetComponent<InventoryComponent>();
		if (icp)
		{
			swap();
			int max = icp->maxBags;
			std::vector<Bag*>& b = go->GetComponent<InventoryComponent>()->bags;
			Vector2 off(window.getPosition().x + 10.f, window.getPosition().y + 30.f);
			for (int it = 0; it < max; it++)
			{
				if (it < b.size())
				{
					Bag* bag = b[it];
					bag->icon.setPosition(off.x, off.y);
					ClickOnBagSlot(bag);
					off.y += iconSize + iconOffset;
				}
			}
		}
	}
}
bool GraphicalInventory::tryEquipBag(Vector2& off)
{
	emptyInventorySlot.setTextureRect(sf::IntRect(0, 0, iconSize, iconSize));
	emptyInventorySlot.setPosition(off.x, off.y);
	if (mouseInsideIcon(emptyInventorySlot) && scroll.getIfMovingItem() && !scroll.mouseInside() && !bagSlotSelected && scroll.equipItem)
	{
		InventoryComponent* icp = Engine::Window.focus.gameObject->GetComponent<InventoryComponent>();
		WindowIcon* swap = (WindowIcon*)(scroll.sprites[scroll.selectedBag]);

		if (icp->bags[swap->index.first]->items[swap->index.second].first)
			if (icp->bags[swap->index.first]->items[swap->index.second].first->tag == Item::bag)
			{
				emptyInventorySlot.setColor(sf::Color(25, 150, 25));
				Engine::Graphic.view.render.draw(emptyInventorySlot);
				emptyInventorySlot.setColor(sf::Color(255, 255, 255));
				if (Engine::event.type == Engine::event.MouseButtonReleased)
				{
					if (Engine::event.mouseButton.button == sf::Mouse::Button::Left)
					{
						if (icp->equipBag(icp->bags[swap->index.first], swap->index.second))
						{
							scroll.movingItem = false;
							scroll.requestSwap = false;
							scroll.equipItem = false;
							WindowIcon* itm = (WindowIcon*)scroll.sprites[scroll.selectedBag];
							std::pair<int, int> pair = itm->index;
							delete scroll.sprites[scroll.selectedBag];
							scroll.sprites[scroll.selectedBag] = NULL;
							scroll.sprites[scroll.selectedBag] = new WindowIcon(emptyInventorySlot, "", "", "", Vector2(0, 16), pair);
							int bag = icp->bags.size();
							for (size_t i = 0; i < icp->bags[icp->bags.size() - 1]->size; ++i)
							{
								scroll.sprites.push_back(new WindowIcon(emptyInventorySlot, "", "", "", Vector2(0, 16), std::pair<int, int>(bag, i)));
							}
							off.y += iconSize + iconOffset;
							return true;
						}
					}
				}
			}
			else
			{
				emptyInventorySlot.setColor(sf::Color(150, 25, 25));
				Engine::Graphic.view.render.draw(emptyInventorySlot);
				emptyInventorySlot.setColor(sf::Color(255, 255, 255));
			}
	}
	else if (scroll.mouseInside() && scroll.getIfMovingItem() && !scroll.requestSwap || !checkMouseInside() && scroll.getIfMovingItem() && !scroll.requestSwap)
		Engine::Graphic.view.render.draw(emptyInventorySlot);
	else
		Engine::Graphic.view.render.draw(emptyInventorySlot);
	return false;
}