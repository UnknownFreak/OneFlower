#ifndef TradeWindow_HPP
#define TradeWindow_HPP

//#include "BaseWindow.hpp"
//#include "Addon/ScrollBar.hpp"
//#include "../Text/FloatingText.hpp"
//#include "../../Item/Item.hpp"
//class InventoryComponent;
//class Item;
//namespace GUI
//{
//	namespace Windows
//	{
//		class TradeWindow : public BaseWindow
//		{
//		public:
//
//			Addon::ScrollBar scroll;
//
//			TradeWindow();
//			~TradeWindow();
//			TradeWindow(float x, float y, int sizeX, int sizeY);
//
//			void draw();
//			void WindowHandle();
//
//			void setScrollbarUpdate(bool b);
//			bool getScrollbarUpdate();
//		private:
//
//			enum tabs
//			{
//				buyTab = 0,
//				sellTab,
//				historyTab,
//			};
//
//			void drawTab();
//
//			int selectedTab = 0;
//
//			bool updateScrollbar = true;
//
//			InventoryComponent* playerInventory = NULL;
//
//			// testVector
//			std::vector<std::pair<Items::Item*, int>> itemsBuy;
//			std::vector<std::pair<Items::Item*, int>> history;
//
//			FloatingText currentGold;
//
//			sf::Sprite selectedButton;
//			sf::Sprite tradingItemBackground;
//
//			Addon::Button tradeSigleItem;
//			Addon::Button tradeStack;
//
//			Addon::Button tab_history;
//			Addon::Button tab_sell;
//			Addon::Button tab_buy;
//
//			void createScrollbar();
//			void buy(int size);
//			void sell(int size);
//			void buyBack();
//
//			void setInventory();
//			void setGold();
//		};
//	}
//}
#endif