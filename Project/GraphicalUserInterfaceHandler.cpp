#include "GraphicalUserInterface.hpp"
#include "Engine.hpp"

void GraphicalUserInterface::Draw()
{
	if (Engine::View.render.hasFocus())
	{
		if (!hideGUI)
		{
			setIconLocation();
			Engine::View.render.draw(mouseSlotLeft.icon);
			Engine::View.render.draw(mouseSlotRight.icon);
			if (mouseSlotLeft.onHover() && Engine::event.mouseButton.button == sf::Mouse::Button::Left)
				;//mouseSlotLeft.onClick();
			if (mouseSlotRight.onHover() && Engine::event.mouseButton.button == sf::Mouse::Button::Left)
				;//MessageBox(Engine::Window.hWnd, "RightPressed", "happen", NULL);
			for (size_t i = 0; i < ActionSlot.size(); ++i)
			{
				ActionSlot[i]->setPosition(40 + 128 * i + Engine::mouse.offset.x, 500 + Engine::mouse.offset.y);

				Engine::View.render.draw(ActionSlot[i]->icon);
				if (ActionSlot[i]->onHover() && Engine::event.mouseButton.button == sf::Mouse::Button::Left)
					ActionSlot[i]->ActionSlotClick();
			}
			if (showOverhead)
				for (size_t i = 0; i < overhead.size(); ++i)
				{
					overhead[i]->setPosition();
					Engine::View.render.draw(overhead[i]->msg.text);
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
	else
		while (ShowCursor(TRUE) < 0);
}