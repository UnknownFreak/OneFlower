#include "IconArgument.hpp"

namespace GUI
{
	namespace Parser
	{
		namespace ParseArgument
		{
			IconArgument::IconArgument(sf::Texture& texture, Vector2 pos, Vector2i size)
				: BaseParseArgument(BaseParseArgument::Icon),
				mySprite(texture), pos(pos), size(size)
			{
				mySprite.setScale(float(size.y / mySprite.getTextureRect().height), float(size.x / mySprite.getTextureRect().width));
			}
			IconArgument::IconArgument(IconArgument & copy) : BaseParseArgument(copy), mySprite(copy.mySprite), pos(copy.pos),size(size)
			{
			}
			IconArgument & IconArgument::operator=(IconArgument & right)
			{
				type = right.type;
				mySprite = right.mySprite;
				pos = right.pos;
				size = right.size;
				return *this;
			}
		}
	}
}