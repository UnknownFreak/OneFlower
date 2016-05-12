#include "GraphicalUserInterface.hpp"
#include "../../Engine.hpp"

#include <SFML\Window\Mouse.hpp>

#include <Windows.h>

namespace GUI {

	void showHideInv()
	{
		Engine::GUI.showHideInventory();
	}

	GraphicalUserInterface::GraphicalUserInterface() : offset(0, 0), hideGUI(true),
		showOverhead(true), isMouseVisible(false), showDialog(true),
		dialogs(), inventory(50, 50, 300, 290), ActionSlot(), showToolTip(true),
		stats(50, 50, 500, 400), focusedWindow(NULL), openedWindowToolTip(), tradingWindow(50, 50, 350, 400),
		playerHealthBar(0, 100, 50, { 0, 0 }, {250,30}, false)
	{
		// Mouse
		setCursor("Cursor.png");
		sf::Texture* tmp = (sf::Texture*)mouseAim.sprite.getTexture();
		tmp->setSmooth(true);
		initialize();
		//Engine::Input.registerCallback(std::bind(&GraphicalUserInterface::showHideInventory,this), sf::Keyboard::I,Input::Action::Release);
		//Engine::Input.registerCallback(std::bind(&GraphicalUserInterface::showHideTradeWindow,this), sf::Keyboard::O,Input::Action::Release);
		/*showHideStats();*/

		//showHideTradeWindow();
		//showHideInventory();
	}
	GraphicalUserInterface::~GraphicalUserInterface()
	{
		delete ActionSlot[0];
		delete ActionSlot[1];
		delete ActionSlot[2];
		delete ActionSlot[3];
	}
	
	void GraphicalUserInterface::updateMouseIcon()
	{
		mouseAim.setPosition((float)(Engine::Input.mouse.pos.x), (float)(Engine::Input.mouse.pos.y));
	}

	void GraphicalUserInterface::setIconLocation()
	{
	}

	void GraphicalUserInterface::setActiveSkill(std::string buttonName)
	{
		//Todo: check type of skill and set on left or right mouse
	}

	void GraphicalUserInterface::addDialog(DialogComponent& dcp)
	{
		dialogs.push_back(&dcp);
	}
	void GraphicalUserInterface::removeDialog(DialogComponent& dcp)
	{
		for (size_t i = 0; i < dialogs.size(); i++)
		{
			if (dialogs[i] == &dcp)
			{
				dialogs.erase(dialogs.begin() + i);
				break;
			}
		}
	}
	void GraphicalUserInterface::addOverhead(GameObject* entity)
	{
		if (entity->GetComponent<OverheadComponent>())
			overhead.push_back(entity->GetComponent<OverheadComponent>());
	}

	void GraphicalUserInterface::requestOverheadRemoval(GameObject* entity)
	{
		OverheadComponent* tmp = entity->GetComponent<OverheadComponent>();
		if (tmp)
			for (std::vector<OverheadComponent*>::iterator it = overhead.begin(); it != overhead.end(); it++)
				if (tmp == *it)
				{
					overhead.erase(it);
					break;
				}
	}

	void GraphicalUserInterface::setCursor(std::string name)
	{
		mouseAim.sprite.setTexture(*Engine::Graphic.requestTexture(name), true);
	}

	void GraphicalUserInterface::initialize()
	{
		// buttons
		for (size_t i = 0; i < 4; i++)
		{
			Window::Addon::Button* tmp = new Window::Addon::Button();
			tmp->setName("ActionBar" + std::to_string(i));
			tmp->setIcon("buttonTest.png");
			tmp->setPosition(40 + 128 * i, 500);
			ActionSlot.push_back(tmp);
		}
		ActionSlot[0]->setIcon("testTarget.png");
	}

	void GraphicalUserInterface::showHideMouse()
	{
		if (isMouseVisible)
		{
			isMouseVisible = false;
		}
		else
		{
			isMouseVisible = true;
		}
	}

	void GraphicalUserInterface::showHideGUI()
	{
		if (Engine::GUI.hideGUI)
			Engine::GUI.hideGUI = false;
		else
			Engine::GUI.hideGUI = true;
	}
	void GraphicalUserInterface::showHideOverhead()
	{
		if (Engine::GUI.showOverhead)
			Engine::GUI.showOverhead = false;
		else
			Engine::GUI.showOverhead = true;
	}
	void GraphicalUserInterface::showHideDialogs()
	{
		if (Engine::GUI.showDialog)
			Engine::GUI.showDialog = false;
		else
			Engine::GUI.showDialog = true;
	}
	void GraphicalUserInterface::setGUIScale()
	{
		double x1 = 800;
		double y1 = 600;
		double x = Engine::Graphic.view.camera.getSize().x;
		double y = Engine::Graphic.view.camera.getSize().y;
		double dx = x1 - x;
		double dy = y1 - y;
		dx = dx / x1;
		dy = dy / y1;
		dx = dx - 1;
		dy = dy - 1;
		dx = -dx;
		dy = -dy;
		scale.x = dx;
		scale.y = dy;
		Engine::GUI.mouseAim.sprite.setScale(dx, dx);
	}
	bool GraphicalUserInterface::windowHasFocus()
	{
		if (inventory.checkMouseInside() && inventory.focus && !hideGUI)
			return true;
		else if (stats.checkMouseInside() && stats.focus && !hideGUI)
			return true;
		else if (tradingWindow.checkMouseInside() && tradingWindow.focus && !hideGUI)
			return true;
		return false;
	}

	void GraphicalUserInterface::scroll()
	{
		if (inventory.checkMouseInside() && inventory.focus)
			inventory.scroll.setScroll(Engine::Input.mouse.deltaScrolls);
		else if (stats.checkMouseInside() && stats.focus)
			stats.items.setScroll(Engine::Input.mouse.deltaScrolls);
		else if (tradingWindow.checkMouseInside() && tradingWindow.focus)
			tradingWindow.scroll.setScroll(Engine::Input.mouse.deltaScrolls);
		Engine::Input.mouse.deltaScrolls = 0;
	}

	void GraphicalUserInterface::showHideInventory()
	{
		if (inventory.open)
		{
			inventory.open = false;
			inventory.focus = false;
			for (std::vector<Window::BaseWindow*>::iterator it = openWindows.begin(); it != openWindows.end(); it++)
				if (*it == &inventory)
				{
					openWindows.erase(it);
					break;
				}
			if (openWindows.size() != 0)
			{
				focusedWindow = openWindows.back();
				focusedWindow->focus = true;
			}
			else
				focusedWindow = NULL;
		}
		else
		{
			inventory.open = true;
			inventory.focus = true;
			if (focusedWindow)
				focusedWindow->focus = false;
			focusedWindow = &inventory;
			openWindows.push_back(&inventory);
		}
	}
	void GraphicalUserInterface::showHideStats()
	{
		if (stats.open)
		{
			stats.open = false;
			stats.focus = false;
			for (std::vector<Window::BaseWindow*>::iterator it = openWindows.begin(); it != openWindows.end(); it++)
				if (*it == &stats)
				{
					openWindows.erase(it);
					break;
				}
			if (openWindows.size() != 0)
			{
				focusedWindow = openWindows.back();
				focusedWindow->focus = true;
			}
			else
				focusedWindow = NULL;
		}
		else
		{
			stats.open = true;
			stats.focus = true;
			if (focusedWindow)
				focusedWindow->focus = false;
			focusedWindow = &stats;
			openWindows.push_back(&stats);
		}
	}

	void GraphicalUserInterface::showHideTradeWindow()
	{
		if (tradingWindow.open)
		{
			tradingWindow.open = false;
			tradingWindow.focus = false;
			for (std::vector<Window::BaseWindow*>::iterator it = openWindows.begin(); it != openWindows.end(); it++)
				if (*it == &tradingWindow)
				{
					openWindows.erase(it);
					break;
				}
			if (openWindows.size() != 0)
			{
				focusedWindow = openWindows.back();
				focusedWindow->focus = true;
			}
			else
				focusedWindow = NULL;
		}
		else
		{
			tradingWindow.open = true;
			tradingWindow.focus = true;
			if (focusedWindow)
				focusedWindow->focus = false;
			focusedWindow = &tradingWindow;
			openWindows.push_back(&tradingWindow);
		}
	}

	bool GraphicalUserInterface::mouseOutsideOpenWindow()
	{
		for (std::vector<Window::BaseWindow*>::iterator it = openWindows.begin(); it != openWindows.end(); it++)
			if (((Window::BaseWindow*)*it)->checkMouseInside() && !hideGUI)
				return false;
		return true;
	}
}