#pragma once
#include <Core/Vector.h>
namespace World
{
	namespace Grid
	{
		struct Tile
		{
			enum Type
			{
				Blank,
				Block,
				Platform,
				Slope
			};
			Vector2i pos;
			Tile(int x, int y);
			Tile(int x, int y, Type t);
			Tile(Vector2i pos);
			Tile(Vector2i pos, Type t);
			Type type;
			static const int size = 16;
		};
	}
}