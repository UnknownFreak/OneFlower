#include "ComboBox.hpp"

namespace GUI
{
	namespace Window
	{
		namespace Addon
		{
			ComboBox::ComboBox(Vector2 pos, Vector2 size, std::string defaultItem, const std::vector<std::string>& items)
				: position(pos), selectedItem(defaultItem), dropDownList(pos.x, pos.y, size.x, size.y, Vector2(0, 0), Vector2(0, 0), NULL, false, true)
			{

			}
		}
	}
}
