#ifndef BoundingBox_HPP
#define BoundingBox_HPP
#include "../../../Vector.h"
namespace Physics
{
	class BoundingBox
	{
	public:
		BoundingBox(int x,int y,int w,int h);
		BoundingBox(Vector2 position,Vector2 size);

		Vector2 position;
		Vector2 size;
		bool intersect(BoundingBox other);
	};
}
#endif