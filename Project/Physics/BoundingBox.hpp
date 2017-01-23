#ifndef BoundingBox_HPP
#define BoundingBox_HPP
#include <Core/Vector.h>
namespace Physics
{
	class BoundingBox
	{
	public:
		BoundingBox(float x, float y, int w, int h);
		BoundingBox(Vector2 position, Vector2i size);

		Vector2 position;
		Vector2i size;
		bool intersect(BoundingBox other);
	};
}
#endif