#ifndef ICONARGUMENT_HPP
#define	ICONARGUMENT_HPP

#include "../BaseParseArgument.hpp"
#include "../../../../../Vector.h"

#include <SFML\Graphics\Sprite.hpp>

namespace GUI
{
	namespace Parser
	{
		namespace ParseArgument
		{
			class IconArgument : public BaseParseArgument
			{
				public:
					sf::Sprite mySprite;
					Vector2 pos;
					IconArgument(sf::Texture& texture, Vector2 pos, Vector2i size);
					IconArgument(IconArgument& copy);
					IconArgument& operator=(IconArgument& right);
			};
		}
	}
}
#endif