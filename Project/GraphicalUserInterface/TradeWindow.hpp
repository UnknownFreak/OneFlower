#ifndef TradeWindow_HPP
#define TradeWindow_HPP

#include "BaseWindow.hpp"
#include "ScrollBar.hpp"
#include "../Text/FloatingText.hpp"
class InventoryComponent;
class Item;
class TradeWindow : public BaseWindow
{
public:

	ScrollBar scroll;

	TradeWindow();
	~TradeWindow();
	TradeWindow(float x, float y, int sizeX, int sizeY);

	void draw();
	void WindowHandle();

	void setScrollbarUpdate(bool b);
	bool getScrollbarUpdate();
private:

	enum tabs
	{
		buyTab = 0,
		sellTab,
		historyTab,
	};

	void drawTab();

	int selectedTab = 0;
	
	bool updateScrollbar = true;
	
	InventoryComponent* playerInventory = NULL;

	// testVector
	std::vector<std::pair<Item*,int>> itemsBuy;
	std::vector<std::pair<Item*,int>> history;

	FloatingText currentGold;

	sf::Sprite selectedButton;
	sf::Sprite tradingItemBackground;

	Button tradeSigleItem;
	Button tradeStack;

	Button tab_history;
	Button tab_sell;
	Button tab_buy;

	void createScrollbar();
	void buy(int size);
	void sell(int size);
	void buyBack();

	void setInventory();
	void setGold();
};

#endif