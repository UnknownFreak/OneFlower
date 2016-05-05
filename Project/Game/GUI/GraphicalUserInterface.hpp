#ifndef GUI_HPP
#define GUI_HPP

#include "..\Component\HitboxComponent.hpp"
#include "..\Component\GameObject.h"
#include "..\Component\RenderComponent.h"
#include "..\Component\TransformComponent.hpp"
#include "..\Component\OverheadComponent.hpp"
#include "Window/Addon/Button.hpp"
#include "Window/InventoryWindow.hpp"
#include "Window/StatsWindow.hpp"
#include "Window/TradeWindow.hpp"
#include "..\Tile.h"
#include "Text/Message.hpp"
#include<vector>
#include<stack>
#include<SFML\Graphics\Text.hpp>


class DialogComponent;
namespace GUI
{
	class GraphicalUserInterface
	{
	public:

		Window::InventoryWindow inventory;
		Window::StatsWindow stats;
		Window::TradeWindow tradingWindow;
		bool hideGUI;
		bool isMouseVisible;
		bool showOverhead;
		bool showDialog;
		bool updateFocus = false;
		//Show tooltips in game
		bool showToolTip;
		//Used for drawing tooltip for opened window.
		bool drawOpenedWindowToolTip = false;
		Tile mouseAim;

		Window::Addon::Button mouseSlotRight;
		Window::Addon::Button mouseSlotLeft;

		sf::Text t;
		std::vector<OverheadComponent*> overhead;
		std::vector<DialogComponent*> dialogs;

		std::vector<Window::Addon::Button*> ActionSlot;

		Window::BaseWindow* focusedWindow;
		std::vector<Window::BaseWindow*> openWindows;
		//std::vector<Message*> messages;

		ToolTip openedWindowToolTip;

		GraphicalUserInterface();
		//~GraphicalUserInterface();

		bool windowHasFocus();
		void scroll();
		void updateMouseIcon();
	void draw();
		void showHideMouse();
		void showHideDialogs();

		void setActiveSkill(std::string buttonName);
		void setCursor(std::string name);

		void showHideOverhead();
		void showHideGUI();

		void showHideInventory();
		void showHideStats();
		void showHideTradeWindow();

		void addOverhead(GameObject* over);
		void requestOverheadRemoval(GameObject* go);
		void addDialog(DialogComponent &dcp);
		void removeDialog(DialogComponent &dcp);

		void setGUIScale();

		bool mouseOutsideOpenWindow();
	private:

		void initialize();
		void setIconLocation();

		Vector2 offset;
	};
}
#endif // ! GUI_HPP