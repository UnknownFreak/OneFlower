#include "PhysicsQuad.hpp"
PhysicsQuad::PhysicsQuad(int plevel)
{
	level = plevel;
}

PhysicsQuad::PhysicsQuad(int plevel,PhysicsQuad* pParent)
{
	level = plevel;
	parent = pParent;
}