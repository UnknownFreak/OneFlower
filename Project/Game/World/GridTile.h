#pragma once
#include "../../Vector.h"
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
			int x;
			int y;
			Tile(int x,int y);
			Tile(int x,int y,Type t);
			Type type;
			static const int size = 16;
		};
	}
}