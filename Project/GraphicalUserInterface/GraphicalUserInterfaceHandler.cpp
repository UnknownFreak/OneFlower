#include "GraphicalUserInterface.hpp"
#include "..\Engine.hpp"
#include "..\Component\DialogComponent.hpp"

void GraphicalUserInterface::Draw()
{
	//if (Engine::View.render.hasFocus())
	{
		if (!hideGUI)
		{
			if (mouseOutsideOpenWindow())
			{
				if (mouseSlotLeft.onHover() && Engine::Input.mouse.leftClick())
				{
					//MessageBox(Engine::Window.hWnd, "RightPressed", "happen", NULL);//mouseSlotLeft.onClick();
				}
				if (mouseSlotRight.onHover() && Engine::Input.mouse.leftClick())
				{
					;//MessageBox(Engine::Window.hWnd, "RightPressed", "happen", NULL);
				}
			}
			else
			{
				mouseSlotLeft.icon.setColor(sf::Color(255, 255, 255));
				mouseSlotRight.icon.setColor(sf::Color(255, 255, 255));
			}
			setIconLocation();
			Engine::View.render.draw(mouseSlotLeft.icon);
			Engine::View.render.draw(mouseSlotRight.icon);
			float offsetX = Engine::View.camera.getCenter().x - (800 * Engine::View.camera.getViewport().width / 2);
			float offsetY = Engine::View.camera.getCenter().y - (600 * Engine::View.camera.getViewport().height / 2);
			for (size_t i = 0; i < ActionSlot.size(); i++)
			{
				ActionSlot[i]->setPosition(40 + 128 * i + offsetX, 500 + offsetY);

				Engine::View.render.draw(ActionSlot[i]->icon);
				if (ActionSlot[i]->onHover() && Engine::event.mouseButton.button == sf::Mouse::Button::Left)
					ActionSlot[i]->ActionSlotClick();
			}
			if (showOverhead)
				for (size_t i = 0; i < overhead.size(); ++i)
				{
					overhead[i]->setPosition();
					overhead[i]->msg.draw();
				}
			if (showDialog)
				for (std::vector<DialogComponent*>::iterator it = dialogs.begin(); it != dialogs.end(); ++it)
				{
					DialogComponent* dcp = *it;
					if (dcp->open)
					{
						dcp->updateLocation();
						dcp->msg->draw();//Engine::View.render.draw(dcp->msg->text);
						if (dcp->msg->timer.getElapsedTime().asSeconds() > dcp->msg->duration && dcp->msg->duration > 0)
						{
							dcp->close();
							break;
						}
					}
				}
			for (std::vector<BaseWindow*>::iterator it = openWindows.begin(); it != openWindows.end(); ++it)
			{
				if (*it == &inventory)
				{
					inventory.draw();
					if (inventory.requestClose)
					{
						showHideInventory();
						break;
					}
				}
				else if (*it == &stats)
				{
					stats.draw();
					if (stats.requestClose)
					{
						showHideStats();
						break;
					}
				}
				else if (*it == &tradingWindow)
				{
					tradingWindow.draw();
					if (tradingWindow.requestClose)
					{
						showHideTradeWindow();
						break;
					}
				}
			}
			if(updateFocus)
			{	
				updateFocus = false;
				bool done = false;
				int size = openWindows.size() - 1;
				for (int i = size; i > -1; --i)
				{
					if (openWindows[i]->requestFocus && !done)
					{
						openWindows[i]->focus = true;
						openWindows[i]->requestFocus = false;
						focusedWindow->focus = false;
						openWindows.push_back(openWindows[i]);
						focusedWindow = openWindows[i];
						openWindows.erase(openWindows.begin() + i);
						done = true;
					}
					else if (openWindows[i]->requestFocus)
						openWindows[i]->requestFocus = false;
					else
						continue;
				}
			}
			if (drawOpenedWindowToolTip)
			{
				openedWindowToolTip.draw();
				drawOpenedWindowToolTip = false;
			}
			if (isMouseVisible)
			{
				while (ShowCursor(FALSE) > 0);
				updateMouseIcon();
				Engine::View.render.draw(mouseAim.sprite);
			}
			else
				while (ShowCursor(TRUE) < 0);
		}
	}
	//else
		//while (ShowCursor(TRUE) < 0);
}