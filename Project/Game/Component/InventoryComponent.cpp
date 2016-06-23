#include <string>
#include "InventoryComponent.hpp"
#include "GameObject.h"
#include "../Item/Item.hpp"
#include "../Item/Bag.hpp"
#include "../Item/Armor.hpp"
#include "../../Engine.hpp"
#include "../GUI/GraphicalUserInterface.hpp"
#include "../GUI/Window/Addon/WindowIcon.hpp"
const unsigned int IBaseComponent<InventoryComponent>::typeID = 1008;
std::string IBaseComponent<InventoryComponent>::componentName = "InventoryComponent";

InventoryComponent::InventoryComponent() : maxWeight(150), currentWeight(0), bags({ new Items::Bag(), new Items::Bag() }), maxBags(4), coins(15)
{
#ifdef _DEBUG
	usedBags = bags.size();
	Items::Item* itm = new Items::Item(0, true, "Boo", "ArrowTest.Png", Items::Item::undefined, 0.1, 12, "Arrows <Debug>");
	addItem(*itm,1);
	Items::Armor Arm;
	//Arm.ID = 1;
	Arm.armorType = "Helm";
	addItem(Arm,1);
	Items::Armor a(3, 3, "TestArmorHelm", "HelmTest.png", 2, 24, "ArmorTest", "Helm", "HelmTest.png", {});
	addItem(a,1);
	//Arm.ID = 4;
	Arm.armorType = "Boots";
	addItem(Arm,1);
	Items::Bag bg;
	//bg.ID = 2;
	addItem(bg,1);
	addItem(bg,1);
	addItem(bg,1);
#endif
}
InventoryComponent::~InventoryComponent()
{
	for(auto it = bags.begin(); it != bags.end(); it++)
		delete *it;
}
bool InventoryComponent::addItem(Items::Item& item, int numberOfItems)
{
	int i = 0;
	bool exists = true;
	for (std::vector<Items::Bag*>::iterator it = bags.begin(); it != bags.end(); it++)
	{
		Items::Bag *bg = *it;
		std::pair<Items::Item*, int>* pair = bg->FindNonFilledStack(item.getID());
		if(pair)
		{
			int tmp = 0;
			for (std::vector<std::pair<Items::Item*, int>>::iterator iit = bg->items.begin(); iit != bg->items.end(); iit++)
			{
				if(iit->first == pair->first)
					break;
				tmp++;
			}

			pair->second += numberOfItems;
			if(pair->second > STACKSIZE)
			{
				numberOfItems = pair->second - STACKSIZE;
				pair->second = STACKSIZE;
				currentWeight += pair->first->getWeight()*STACKSIZE;
				if(Engine::GUI.inventory.createdInventory)
					((GUI::Window::Addon::WindowIcon*)(Engine::GUI.inventory.scroll.sprites[i + tmp]))->messageText = std::to_string(pair->second);
				break;
			}
			else
			{
				currentWeight += pair->first->getWeight()*numberOfItems;
			}
			if(Engine::GUI.inventory.createdInventory)
				((GUI::Window::Addon::WindowIcon*)(Engine::GUI.inventory.scroll.sprites[i + tmp]))->messageText = std::to_string(pair->second);

			exists = false;
		}
		i += bg->size;
	}
	i = 0;
	if(exists)
		for (std::vector<Items::Bag*>::iterator it = bags.begin(); it != bags.end(); it++)
		{
			Items::Bag* bg = *it;
			if(bg->freeSlots != 0)
			{
				int tmp = bg->addItem(&item,numberOfItems);
				if(tmp != -1)
				{
					currentWeight += item.getWeight()*numberOfItems;
					if(Engine::GUI.inventory.createdInventory)
					{
						((GUI::Window::Addon::WindowIcon*)(Engine::GUI.inventory.scroll.sprites[i + tmp]))->icon = item.icon;
						((GUI::Window::Addon::WindowIcon*)(Engine::GUI.inventory.scroll.sprites[i + tmp]))->toolTipTitle = item.getName();
						((GUI::Window::Addon::WindowIcon*)(Engine::GUI.inventory.scroll.sprites[i + tmp]))->toolTipBody = item.toToolTipString();
						((GUI::Window::Addon::WindowIcon*)(Engine::GUI.inventory.scroll.sprites[i + tmp]))->messageText = std::to_string(numberOfItems);
						if (item.getTag() == Items::Item::armor || item.getTag() == Items::Item::weapon && !Engine::GUI.stats.updateEquipment)
							Engine::GUI.stats.updateEquipment = true;
					}
					return true;
				}
			}
			i += bg->size;
		}
	return false;
}
Items::Item* InventoryComponent::removeItem(int bag, int index, int numberOfItems)
{
	Items::Item* item = NULL;
	int j = 0;
	for(size_t i = 0; i < bag; i++)
		j += bags[bag]->size;
	if(bags[bag]->items[index].second >= numberOfItems)
	{
		bags[bag]->items[index].second -= numberOfItems;
		currentWeight -= bags[bag]->items[index].first->getWeight()*numberOfItems;
	}
	else
	{
		currentWeight -= bags[bag]->items[index].first->getWeight()*bags[bag]->items[index].second;
		numberOfItems = bags[bag]->items[index].second;
		bags[bag]->items[index].second -= numberOfItems;
	}

	if(bags[bag]->items[index].second <= 0)
	{
		item = bags[bag]->items[index].first;
		bags[bag]->items[index].first = NULL;
	}
	if(Engine::GUI.inventory.createdInventory)
	{
		if(bags[bag]->items[index].second == 0)
		{
			((GUI::Window::Addon::WindowIcon*)(Engine::GUI.inventory.scroll.sprites[j + index]))->messageText = "";
			((GUI::Window::Addon::WindowIcon*)(Engine::GUI.inventory.scroll.sprites[j + index]))->icon = Engine::GUI.inventory.getEmptyInventorySlotIcon();
			((GUI::Window::Addon::WindowIcon*)(Engine::GUI.inventory.scroll.sprites[j + index]))->toolTipTitle = "";
			((GUI::Window::Addon::WindowIcon*)(Engine::GUI.inventory.scroll.sprites[j + index]))->toolTipBody = "";
			if ((item->getTag() == Items::Item::armor || item->getTag() == Items::Item::weapon) && !Engine::GUI.stats.updateEquipment)
				Engine::GUI.stats.updateEquipment = true;
			Engine::GUI.tradingWindow.setScrollbarUpdate(true);
		}
		else
			((GUI::Window::Addon::WindowIcon*)(Engine::GUI.inventory.scroll.sprites[j + index]))->messageText = std::to_string(bags[bag]->items[index].second);
	}
	return item;
}

bool InventoryComponent::swapItem(Items::Bag* first, int firstPair, Items::Bag*second, int secondPair)
{
	if(firstPair < 0 || secondPair < 0)
		return false;
	if(first == second)
	{
		Items::Item* item = first->items[firstPair].first;
		int tmp = first->items[firstPair].second;
		first->items[firstPair].first = second->items[secondPair].first;
		first->items[firstPair].second = second->items[secondPair].second;

		second->items[secondPair].first = item;
		second->items[secondPair].second = tmp;
		return true;
	}
	else
	{
		if(!second->items[secondPair].first)
		{
			Items::Item* item = first->items[firstPair].first;
			int tmp = first->items[firstPair].second;
			first->items[firstPair].first = second->items[secondPair].first;
			first->items[firstPair].second = second->items[secondPair].second;

			second->items[secondPair].first = item;
			second->items[secondPair].second = tmp;
			++first->freeSlots;
			--second->freeSlots;
			return true;
		}
		else
		{
			Items::Item* item = first->items[firstPair].first;
			int tmp = first->items[firstPair].second;
			first->items[firstPair].first = second->items[secondPair].first;
			first->items[firstPair].second = second->items[secondPair].second;

			second->items[secondPair].first = item;
			second->items[secondPair].second = tmp;
			return true;
		}
	}
	return false;
}
bool InventoryComponent::equipBag(Items::Bag* first, int firstPair)
{
	if (first->items[firstPair].first->getTag() == Items::Item::bag && usedBags <= maxBags)
	{
		std::pair<Items::Item*, int>* it = &first->items[firstPair];
		Items::Bag* b = (Items::Bag*)it->first;
		first->items[firstPair].first = NULL;
		first->items[firstPair].second = NULL;
		first->freeSlots++;

		bags.push_back(b);
		++usedBags;
		return true;
	}
	return false;
}
bool InventoryComponent::unequipBag(Items::Bag* bag, Items::Bag* second, int emptySlot)
{
	if(bag->freeSlots != bag->size || bag == second)
	{
		return false;
	}
	else
	{
		std::vector<Items::Bag*>::iterator it = bags.begin();
		for(it; it != bags.end(); it++)
		{
			Items::Bag* b = *it;
			if(b == bag && !second->items[emptySlot].first)
			{
				bags.erase(it);
				break;
			}
		}
		if(second->items[emptySlot].first == NULL)
		{
			second->items[emptySlot].first = bag;
			second->items[emptySlot].second = 1;
			second->freeSlots--;
			usedBags--;
			return true;
		}
		else return false;
	}
}
void InventoryComponent::attachOn(GameObject* attachTo)
{
	BaseComponent::attachOn(attachTo);
}
void InventoryComponent::addGold(unsigned int goldToAdd)
{
	coins += goldToAdd;
}
void InventoryComponent::removeGold(unsigned int goldToRemove)
{
	coins -= goldToRemove;
}
bool InventoryComponent::updateFromEditor()
{
	return true;
}
std::string InventoryComponent::getWeight()
{
	std::string w = std::to_string(currentWeight);
	std::string mw = std::to_string(maxWeight);
	return w.substr(0,w.size() - 4) + " / " + mw.substr(0,mw.size() - 4);
}