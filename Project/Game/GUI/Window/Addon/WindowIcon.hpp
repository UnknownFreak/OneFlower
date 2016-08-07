#ifndef WindowIcon_HPP
#define WindowIcon_HPP
#include <string>
#include <SFML\Graphics\Sprite.hpp>
#include "../BaseWindowObject.hpp"
#include "../../ToolTip.hpp"
#include "../../Text/FloatingText.hpp"
namespace GUI
{
	namespace Window
	{
		namespace Addon
		{
			class WindowIcon : public BaseWindowObject
			{
			public:

				WindowIcon();
				WindowIcon(sf::Sprite icon, std::string toolTipTitle, std::string toolTipBody,
					std::string messageText, Vector2 textOffset, std::pair<int, int> index,
					sf::Color color = sf::Color(0, 0, 0), int fontSize = 14);

				//used for inventory slots
				std::pair<int, int> index;
				sf::Sprite icon;
				GUI::FloatingText messageText;
				std::string toolTipTitle;
				std::string toolTipBody;
				void draw();
				void setPosition(Vector2 pos);
				void setPosition(double x, double y);

			private:

				Vector2 textOffset;
			};
		}
	}
}
#endif