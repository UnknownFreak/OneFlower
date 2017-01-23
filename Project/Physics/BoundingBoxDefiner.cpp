#include "BoundingBox.hpp"

Physics::BoundingBox::BoundingBox(float x, float y, int w, int h) : position(x, y), size(w, h)
{
}
Physics::BoundingBox::BoundingBox(Vector2 pos, Vector2i siz) : position(pos), size(siz)
{}

bool Physics::BoundingBox::intersect(Physics::BoundingBox other)
{
	if (position.y + size.y < other.position.y)
		return false;
	else if (other.position.y + other.size.y < position.y)
		return false;
	else if (position.x + size.x < other.position.x)
		return false;
	else if (other.position.x + other.size.x < position.x)
		return false;
	else
		return true;
}