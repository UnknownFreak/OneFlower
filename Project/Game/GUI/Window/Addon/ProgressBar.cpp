#include "ProgressBar.hpp"
#include "../../../../Engine.hpp"
namespace GUI
{
	namespace Window
	{
		namespace Addon
		{
			/*
			ProgressBar::ProgressBar(int min, int max, int value, sf::Sprite progressbar,Text::Message text, Vector2 position, Vector2 size, bool isVertical, ToolTip tooltip = ToolTip("None")):
				min(min), max(max), value(value), progressbar(progressbar), text(text), position(position), size(size), isVertical(isVertical), toolTip(toolTip)
			{
				if (toolTip.getToolTipBody() == "None")
					showToolTip = false;
			}
			//*/
			ProgressBar::ProgressBar(int min, int max, int value, Vector2 pos, Vector2 size, bool isVertical):
				min(min), max(max), value(value), position(pos), size(size), isVertical(isVertical), showToolTip(false), temporaryOutline(sf::LinesStrip, 5),
				temporaryBar(sf::PrimitiveType::Quads,4)
			{
				temporaryOutline[0].position = sf::Vector2f(position.x, position.y);
				temporaryOutline[1].position = sf::Vector2f(position.x + size.x, position.y);
				temporaryOutline[2].position = sf::Vector2f(position.x + size.x, position.y + size.y);
				temporaryOutline[3].position = sf::Vector2f(position.x, position.y + size.y);
				temporaryOutline[4].position = sf::Vector2f(position.x, position.y);
				temporaryOutline[0].color = sf::Color::White;
				temporaryOutline[1].color = sf::Color::White;
				temporaryOutline[2].color = sf::Color::White;
				temporaryOutline[3].color = sf::Color::White;
				temporaryOutline[4].color = sf::Color::White;

				temporaryBar[0].position = sf::Vector2f(position.x, position.y);
				temporaryBar[1].position = sf::Vector2f(position.x + size.x, position.y);
				temporaryBar[2].position = sf::Vector2f(position.x + size.x, position.y + size.y);
				temporaryBar[3].position = sf::Vector2f(position.x, position.y + size.y);
				temporaryBar[0].color = sf::Color::Blue;
				temporaryBar[1].color = sf::Color::Blue;
				temporaryBar[2].color = sf::Color::Blue;
				temporaryBar[3].color = sf::Color::Blue;

			}

			void ProgressBar::draw()
			{
				if (!isVertical)
				{
					temporaryBar[0].position = sf::Vector2f(position.x, position.y);
					temporaryBar[1].position = sf::Vector2f(value == 0 ? position.x : position.x  + (size.x * Engine::GUI.scale.x * (value / (double)(max - min))) , position.y);
					temporaryBar[2].position = sf::Vector2f(value == 0 ? position.x : position.x  + (size.x * Engine::GUI.scale.x * (value / (double)(max - min))) , position.y + (size.y * Engine::GUI.scale.y));
					temporaryBar[3].position = sf::Vector2f(position.x, position.y + (size.y * Engine::GUI.scale.y));

					temporaryOutline[0].position = sf::Vector2f(position.x , position.y);
					temporaryOutline[1].position = sf::Vector2f(position.x + size.x * Engine::GUI.scale.x, position.y);
					temporaryOutline[2].position = sf::Vector2f(position.x + size.x * Engine::GUI.scale.x, position.y + (size.y * Engine::GUI.scale.y));
					temporaryOutline[3].position = sf::Vector2f(position.x, position.y + (size.y * Engine::GUI.scale.y));
					temporaryOutline[4].position = sf::Vector2f(position.x, position.y);
				}
				else
				{
					temporaryBar[0].position = sf::Vector2f(position.x, position.y + size.y - (size.y * (value / (double)(max - min))));
					temporaryBar[1].position = sf::Vector2f(position.x + size.x -1, position.y + size.y - (size.y * (value / (double)(max - min))));
					temporaryBar[2].position = sf::Vector2f(position.x + size.x -1, position.y + size.y);
					temporaryBar[3].position = sf::Vector2f(position.x, position.y + size.y);
				}
				Engine::Graphic.view.render.draw(temporaryBar);
				Engine::Graphic.view.render.draw(temporaryOutline);
			}
			void ProgressBar::setValue(int value)
			{
				this->value = value;
			}
			void ProgressBar::setMin(int min)
			{
				this->min = min;
			}
			void ProgressBar::setMax(int max)
			{
				this->max = max;
			}
			void ProgressBar::setPosition(Vector2 pos)
			{
				position = pos;
			}
		}
	}
}