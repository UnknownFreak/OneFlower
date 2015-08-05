#include "TradeWindow.hpp"
#include "../../../Engine.hpp"
#include "../../Component/InventoryComponent.hpp"
#include "../../Item/Bag.hpp"
#include "../../Item/Armor.hpp"
#include "Addon/WindowIcon.hpp"

TradeWindow::TradeWindow() : BaseWindow(50, 50, 250, 600, false, "Trade - Buy"),
scroll(50 + 12, 50 + 12, 250 - 24, 600 - 24, Vector2(64,40), Vector2(220, 10), this, false),
tradeSigleItem("ButtonTest.png", 40, 20, 20, 20), tradeStack("ButtonTest.png", 40, 20, 20, 45),
tab_buy("ButtonTest.png", 32, 32, 20, 20), tab_sell("ButtonTest.png", 32, 32, 20, 20), tab_history("ButtonTest.png", 32, 32, 20, 20),
tradingItemBackground(*Engine::Graphic.requestTexture("TradeWindowIcon.png"))
{
	tab_buy.icon.setColor(sf::Color(125, 125, 125));
	tradeSigleItem.setName("Sell");
}

TradeWindow::TradeWindow(float x, float y, int sizeX, int sizeY) : BaseWindow(x, y, sizeX, sizeY, false, "Trade - Buy"),
scroll(x + 12, y + 12, sizeX - 24, sizeY - 24, Vector2(255, 40), Vector2(220, 2), this, false),
tradeSigleItem("ButtonWide.png", sf::IntRect(0,0,50,20), 20, 20,"Trade"), tradeStack("ButtonWide.png", 50, 20, 20, 45),
tab_buy("BuySell.png", sf::IntRect(0, 0, 36, 36), 20, 20, "buy"), tab_sell("BuySell.png", sf::IntRect(36, 0, 36, 36), 20, 20, "sell"), tab_history("ButtonTest.png", sf::IntRect(0, 0, 32, 32), 20, 20, ""),
currentGold("test.png", *Engine::Graphic.font.requestFont("arial.ttf"),false),
tradingItemBackground(*Engine::Graphic.requestTexture("TradeWindowIcon.png"))
{
	tab_buy.icon.setColor(sf::Color(125, 125, 125));
	tradeSigleItem.setName("\tBuy");
	currentGold = "b §Icon|coins|0|0|0§";
	currentGold.setSize(12);
	itemsBuy.push_back(std::pair<Item*, int>(new Item(0, true, "test", "InventoryIconTest.png", Item::undefined, .4, 1234567, "Giggity"), -1));
	itemsBuy.push_back(std::pair<Item*, int>(new Item(0, true, "test", "InventoryIconTest.png", Item::undefined, .4, 123456, "Giggity"), -1));
	itemsBuy.push_back(std::pair<Item*, int>(new Item(0, true, "test", "InventoryIconTest.png", Item::undefined, .4, 12345, "Giggity"), -1));
	itemsBuy.push_back(std::pair<Item*, int>(new Item(0, true, "test", "InventoryIconTest.png", Item::undefined, .4, 1234, "Giggity"), -1));
	itemsBuy.push_back(std::pair<Item*, int>(new Item(0, true, "test", "InventoryIconTest.png", Item::undefined, .4, 123, "Giggity"), -1));
	itemsBuy.push_back(std::pair<Item*, int>(new Item(0, true, "test", "InventoryIconTest.png", Item::undefined, .4, 12, "Giggity"), -1));
	itemsBuy.push_back(std::pair<Item*, int>(new Item(0, true, "test", "InventoryIconTest.png", Item::undefined, .4, 1, "Giggity"), -1));
}

TradeWindow::~TradeWindow()
{
	size_t i = 0;
	for (i; i < itemsBuy.size(); i++)
	{
		delete itemsBuy[i].first;
		itemsBuy[i].first = NULL;
	}
	for (i = 0; i < history.size(); i++)
	{
		delete history[i].first;
		history[i].first = NULL;
	}
}

void TradeWindow::draw()
{
	if (open)
	{
		if (updateScrollbar)
			createScrollbar();
		move();
		WindowHandle();
		BaseWindow::draw();
		scroll.draw();
		drawTab();
		currentGold.draw();
		if (scroll.tooltip.first && !scroll.movingItem && Engine::GUI.showToolTip && Engine::GUI.focusedWindow->checkMouseInside() && Engine::GUI.focusedWindow == (BaseWindow*)this ||
			scroll.tooltip.first && !scroll.movingItem && Engine::GUI.showToolTip && !Engine::GUI.focusedWindow->checkMouseInside())
			if (scroll.mouseInsideIcon(*scroll.tooltip.first) && scroll.tooltip.second.getToolTipBody() != "")
			{
				Engine::GUI.openedWindowToolTip.setToolTipText(scroll.tooltip.second.getToolTipTitle(), scroll.tooltip.second.getToolTipBody());
				Engine::GUI.drawOpenedWindowToolTip = true;
			}
	}
}
void TradeWindow::WindowHandle()
{

	//currentGold
	currentGold.setPosition(position.x + offsetX + 20, position.y + window.getTextureRect().height - 28 + offsetY);

	//button
	tradeSigleItem.setPosition(position.x + offsetX + window.getTextureRect().width - 56, position.y + window.getTextureRect().height - 28 + offsetY);

	//tabs
	tab_buy.setPosition(position.x + offsetX + 5, position.y + 30 + offsetY);
	tab_sell.setPosition(position.x + offsetX + 5, position.y + 30 + 37 + offsetY);
	tab_history.setPosition(position.x + offsetX + 5, position.y + 30 + 74 + offsetY);

	//scrollbar
	scroll.setSizeY(window.getTextureRect().height - 130);
	scroll.setSizeX(328);
	scroll.setPosition(position.x + offsetX, position.y + 40 + offsetY);

	BaseWindow::WindowHandle();
}
void TradeWindow::setScrollbarUpdate(bool b)
{
	updateScrollbar = b;
}
bool TradeWindow::getScrollbarUpdate()
{
	return updateScrollbar;
}
void TradeWindow::setInventory()
{
	GameObject* go = Engine::Window.focus.gameObject;
	if (go)
		playerInventory = go->GetComponent<InventoryComponent>();
}
void TradeWindow::drawTab()
{
	tradeSigleItem.draw();
#pragma region tabs
	tab_buy.draw();
	//tab_history.draw();
	tab_sell.draw();

	setGold();

	if (focus)
	{
		if (selectedTab != tabs::sellTab)
		{
			if (tab_sell.onHover() && windowLClick)
			{
				selectedTab = tabs::sellTab;
				updateScrollbar = true;
				tradeSigleItem.setName("\tSell");
				title = "Trade - Sell";
			}
		}
		/*if (selectedTab != tabs::historyTab)
		{
			if (tab_history.onHover() && windowClick)
			{
				selectedTab = tabs::historyTab;
				updateScrollbar = true;
			}
		}*/
		if (selectedTab != tabs::buyTab)
		{
			if (tab_buy.onHover() && windowLClick)
			{
				selectedTab = tabs::buyTab;
				updateScrollbar = true;
				tradeSigleItem.setName("\tBuy");
				title = "Trade - Buy";
			}
		}
#pragma endregion
		if (tradeSigleItem.onHover() && windowLClick)
		{
			if (scroll.selected)
			{
				if (playerInventory)
					if (selectedTab == tabs::buyTab)
						buy(1);
					else if (selectedTab == tabs::sellTab)
						sell(1);
					else
						;
				else
				{
					setInventory();
					if (playerInventory)
						if (selectedTab == tabs::buyTab)
							buy(1);
						else if (selectedTab == tabs::sellTab)
							sell(1);
				}
			}
		}
	}
}
void TradeWindow::createScrollbar()
{
	scroll.setScroll(155);
	scroll.selected = NULL;
	std::vector<BaseWindowObject*>::iterator it = scroll.sprites.begin();
	for (it; it != scroll.sprites.end(); it++)
	{
		delete *it;
	}
	scroll.sprites.clear();
	if (selectedTab == tabs::buyTab)
	{
		//tmp
		for (std::vector<std::pair<Item*, int>>::iterator it = itemsBuy.begin(); it != itemsBuy.end(); ++it)
		{
			Item* itm = it->first;
			std::string number = std::to_string(it->second);
			if (number == "-1")
				number = "N/A";
			scroll.sprites.push_back(new WindowIcon(tradingItemBackground, itm->name, itm->toToolTipString(), number + "\t\t" + itm->name + "\t§Icon|coins|190|0|" +
				std::to_string(itm->price) + "|Icon|"+ itm->iconName +"|-36|-4|false| ", Vector2(40, 8), std::pair<int, int>(0, 0), sf::Color::Black, 12));
		}
		updateScrollbar = false;
	}
	else if (selectedTab == tabs::sellTab)
	{
		if (playerInventory)
		{
			int i = 0;
			std::vector<Bag*>::iterator it = playerInventory->bags.begin();
			for (it; it != playerInventory->bags.end(); it++)
			{
				if (((Bag*)*it)->freeSlots == ((Bag*)*it)->size)
					continue;
				std::vector<std::pair<Item*, int>>::iterator iit = ((Bag*)*it)->items.begin();
				int j = 0;
				for (iit; iit != ((Bag*)*it)->items.end(); ++iit)
				{
					if (iit->first)
						scroll.sprites.push_back(new WindowIcon(tradingItemBackground, iit->first->name, iit->first->toToolTipString(),
						std::to_string(iit->second) + "\t\t" + iit->first->name + "\t§Icon|coins|190|0|" + std::to_string(iit->first->price)
						+ "|Icon|" + iit->first->iconName + "|-36|-4|false| ", Vector2(40, 8), std::pair<int, int>(i, j), sf::Color::Black, 12));
					j++;
				}
				i++;
			}
			updateScrollbar = false;
		}
		else
		{
			//change to player
			GameObject* go = Engine::Window.focus.gameObject;
			if (go)
				playerInventory = go->GetComponent<InventoryComponent>();
		}
	}
	/*else
	{
		for (std::vector<std::pair<Item*, int>>::iterator it = history.begin(); it != history.end(); it++)
		{
		Item* itm = it->first;
		scroll.sprites.push_back(new WindowIcon(itm->icon, itm->name, itm->toToolTipString(), std::to_string(it->second) + " " + itm->name + "§Icon|coins|12|0|" +
		std::to_string(itm->price), Vector2(64, 3), std::pair<int, int>(0, 0), sf::Color::Black, 12));
		}
		updateScrollbar = false;
	}*/
}
void TradeWindow::buy(int size)
{
	if (playerInventory->coins >= itemsBuy[scroll.selectedBag].first->price)
	{
		if (itemsBuy[scroll.selectedBag].second < size && itemsBuy[scroll.selectedBag].second != -1)
			size = itemsBuy[scroll.selectedBag].second;
		if (playerInventory->addItem(*itemsBuy[scroll.selectedBag].first, size))
		{
			playerInventory->removeGold(size*itemsBuy[scroll.selectedBag].first->price);

			if (itemsBuy[scroll.selectedBag].second != -1)
			{
				itemsBuy[scroll.selectedBag].second -= size;
				if (itemsBuy[scroll.selectedBag].second == 0)
				{
					delete scroll.sprites[scroll.selectedBag];
					scroll.sprites[scroll.selectedBag] = NULL;
					scroll.selected = NULL;
					scroll.sprites.erase(scroll.sprites.begin() + scroll.selectedBag);
					delete itemsBuy[scroll.selectedBag].first;
					itemsBuy.erase(itemsBuy.begin() + scroll.selectedBag);
				}
				else
					((WindowIcon*)scroll.sprites[scroll.selectedBag])->messageText = std::to_string(itemsBuy[scroll.selectedBag].second) + "\t\t" +
					itemsBuy[scroll.selectedBag].first->name + "\t§Icon|coins|190|0|" +
					std::to_string(itemsBuy[scroll.selectedBag].first->price) + "|Icon|" + itemsBuy[scroll.selectedBag].first->iconName + "|-36|-4|false| ";
			}
		}
	}
}
void TradeWindow::sell(int size)
{
	WindowIcon* icon = (WindowIcon*)scroll.sprites[scroll.selectedBag];
	int itemStack = playerInventory->bags[icon->index.first]->items[icon->index.second].second;
	if (itemStack < size)
		size = itemStack;
	Item* item = playerInventory->removeItem(icon->index.first, icon->index.second, size);

	if (item)
	{
		bool found = false;
		for (size_t i = 0; i < itemsBuy.size(); i++)
		{
			if (itemsBuy[i].first->ID == item->ID)
			{
				found = true;
				if (itemsBuy[i].second != -1)
					itemsBuy[i].second += size;
				break;
			}
		}
		if (!found)
		{
			if (item->tag == Item::bag)
			{
				Bag* bag = (Bag*)item;
				itemsBuy.push_back(std::pair<Item*, int>(new Bag(*bag), size));
			}
			else if (item->tag == Item::armor)
			{
				Armor* arm = (Armor*)item;
				itemsBuy.push_back(std::pair<Item*, int>(new Armor(*arm), size));
			}
			else if (item->tag == Item::undefined)
			{
				itemsBuy.push_back(std::pair<Item*, int>(new Item(*item), size));
			}
		}
		//history.push_back(std::pair<Item*,int>(item,size));
		delete icon;
		scroll.sprites.erase(scroll.sprites.begin() + scroll.selectedBag);
		scroll.selected = NULL;
		playerInventory->addGold(size*item->price);
	}
	else
	{
		bool found = false;
		for (size_t i = 0; i < itemsBuy.size(); i++)
		{
			if (itemsBuy[i].first->ID == playerInventory->bags[icon->index.first]->items[icon->index.second].first->ID)
			{
				found = true;
				if (itemsBuy[i].second != -1)
					itemsBuy[i].second += size;
				break;
			}
		}
		if (!found)
		{
			if (playerInventory->bags[icon->index.first]->items[icon->index.second].first->tag == Item::bag)
			{
				Bag* bag = (Bag*)playerInventory->bags[icon->index.first]->items[icon->index.second].first;
				itemsBuy.push_back(std::pair<Item*, int>(new Bag(*bag), size));
			}
			else if (playerInventory->bags[icon->index.first]->items[icon->index.second].first->tag == Item::armor)
			{
				Armor* arm = (Armor*)playerInventory->bags[icon->index.first]->items[icon->index.second].first;
				itemsBuy.push_back(std::pair<Item*, int>(new Armor(*arm), size));
			}
			else if (playerInventory->bags[icon->index.first]->items[icon->index.second].first->tag == Item::undefined)
			{
				itemsBuy.push_back(std::pair<Item*, int>(new Item(*playerInventory->bags[icon->index.first]->items[icon->index.second].first), size));
			}
		}
		icon->messageText = std::to_string(playerInventory->bags[icon->index.first]->items[icon->index.second].second) +
			"\t\t" + playerInventory->bags[icon->index.first]->items[icon->index.second].first->name + "\t§Icon|coins|190|0|" +
			std::to_string(playerInventory->bags[icon->index.first]->items[icon->index.second].first->price)
			+ "|Icon|" + playerInventory->bags[icon->index.first]->items[icon->index.second].first->iconName + "|-36|-4|false| ";

		//history.push_back(std::pair<Item*, int>(playerInventory->bags[icon->index.first]->items[icon->index.second].first, size));
		playerInventory->addGold(size*playerInventory->bags[icon->index.first]->items[icon->index.second].first->price);
	}
}
void TradeWindow::setGold()
{
	if (playerInventory)
	{
		std::string _gold = std::to_string(playerInventory->coins);
		int size = _gold.length();
		if (size > 9)
			currentGold = "§Icon|coins|95|0|" + std::to_string(playerInventory->coins);
		else if (size > 8)
			currentGold = "§Icon|coins|88|0|" + std::to_string(playerInventory->coins);
		else if (size > 7)
			currentGold = "§Icon|coins|81|0|" + std::to_string(playerInventory->coins);
		else if (size > 6)
			currentGold = "§Icon|coins|74|0|" + std::to_string(playerInventory->coins);
		else if (size > 5)
			currentGold = "§Icon|coins|67|0|" + std::to_string(playerInventory->coins);
		else if (size > 4)
			currentGold = "§Icon|coins|60|0|" + std::to_string(playerInventory->coins);
		else if (size > 2)
			currentGold = "§Icon|coins|30|0|" + std::to_string(playerInventory->coins);
		else
			currentGold = "§Icon|coins|0|0|" + std::to_string(playerInventory->coins);
	}
	else
	{
		GameObject* go = Engine::Window.focus.gameObject;
		if (go)
			playerInventory = go->GetComponent<InventoryComponent>();
	}
}