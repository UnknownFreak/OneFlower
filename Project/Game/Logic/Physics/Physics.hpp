#ifndef Physics_HPP
#define Physics_HPP
#include <vector>
#include "../../../Vector.h"
#include "BoundingBox.hpp"
#include "Collider.hpp"

#define PixelInOneMeter 128
class GameObject;
class RigidComponent;
class HitboxComponent;
class TransformComponent;
//HIGH: Do non game related physics like weather water etc???
class PhysicsEngine
{
	friend class Gfx;
public:
	PhysicsEngine();
	void update();

	/*
	void addPhysics(GameObject* obj);
	void addPhysics(HitboxComponent* obj);
	void addPhysics(RigidComponent* obj);
	void removePhysics(RigidComponent* obj);
	void removePhysics(HitboxComponent* obj);
	void removePhysics(GameObject* obj);
	//*/
	void physics();

	//Fix the collision or remake the flow so that sending gameobject is unnecceray 
	Physics::Collider collision(TransformComponent* motion,Physics::BoundingBox box,Vector2 speed);


	const double Gravity = 2;


	//This is for what? (21/03/16)
	//std::vector<RigidComponent*> checkList;

private:
	
	void simulation();

	void gravity();
//	float SweptAABB(RigidComponent* inMotion,HitboxComponent* b22,float& normalx,float& normaly,Vector2 speed);

};
#endif