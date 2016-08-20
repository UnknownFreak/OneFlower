#ifndef COLORARGUMENT_HPP
#define	COLORARGUMENT_HPP

#include "../Comparer/BaseParseArgument.hpp"


namespace GUI
{
	namespace Parser
	{
		namespace ParseArgument
		{
			class ColorArgument : public BaseParseArgument
			{
			public:
				sf::Color myColor;
				ColorArgument(sf::Color color);
				ColorArgument(const ColorArgument& copy);
				ColorArgument& operator=(const ColorArgument& right);

			};
		}
	}
}


#endif