#include "ColorArgument.hpp"
namespace GUI
{
	namespace Parser
	{
		namespace ParseArgument
		{
			ColorArgument::ColorArgument(sf::Color color) : BaseParseArgument(ArgumentType::Color), myColor(color)
			{
			}
			ColorArgument::ColorArgument(const ColorArgument & copy) : BaseParseArgument(copy), myColor(copy.myColor)
			{
			}
			ColorArgument& ColorArgument::operator=(const ColorArgument & right)
			{
				myColor = right.myColor;
				type = right.type;
				return *this;
			}
		}
	}
}
