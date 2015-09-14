#ifndef Physics_HPP
#define Physics_HPP
#include <vector>
#include "../../../Vector.h"
#include "BoundingBox.hpp"
#define PixelInOneMeter 128
class GameObject;
class RigidComponent;
class HitboxComponent;

class PhysicsEngine
{
	friend class Gfx;
public:
	PhysicsEngine();
	void update();

	void addPhysics(GameObject* obj);
	void addPhysics(HitboxComponent* obj);
	void addPhysics(RigidComponent* obj);

	void removePhysics(RigidComponent* obj);
	void removePhysics(HitboxComponent* obj);
	void removePhysics(GameObject* obj);
	const double Gravity = 9.82;
	void physics();
	void simulation();

private:
	
	class Collider
	{
	public:
	/*	
		Collider();
		Collider(RigidComponent*);
		Collider(HitboxComponent*);
	//*/
		//Global Position on screen
		Vector2 position;
		Vector2 size;
		Vector2 offset;
	};
	Collider collision(Physics::BoundingBox box,Vector2 speed);
	void gravity();
//	float SweptAABB(RigidComponent* inMotion,HitboxComponent* b22,float& normalx,float& normaly,Vector2 speed);

	//LOW Move this out of Physics engine?
	std::vector<HitboxComponent*> hitboxes;
	std::vector<RigidComponent*> rigid;
	std::vector<RigidComponent*> checkList;
};
#endif