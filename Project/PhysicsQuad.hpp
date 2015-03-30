#ifndef PhysicsQuad_HPP
#define PhysicsQuad_HPP
#include <vector>
#include "Vector.h"

class HitboxComponent;
class PhysicsQuad
{
public:
	PhysicsQuad(int level);
	PhysicsQuad(int level,PhysicsQuad* parent);
	Vector2 position[2];
	std::vector<HitboxComponent*> sector[4];
	void sortBox(HitboxComponent*);

	PhysicsQuad* parent;
	PhysicsQuad* child;
	int level;

private:
};

#endif