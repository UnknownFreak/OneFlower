#ifndef Physics_HPP
#define Physics_HPP
#include <vector>
#include "BoundingBox.hpp"
#include "Collider.hpp"
//included via collider and Boundingbox
//#include "../Core/Vector.h"

#define PixelInOneMeter 128
class GameObject;
namespace Component
{
	class RigidComponent;
	class HitboxComponent;
	class TransformComponent;
}
//HIGH: Do non game related physics like weather water etc???
class PhysicsEngine
{

	static PhysicsEngine* m_engine;

	PhysicsEngine();

	friend class Gfx;
public:

	static PhysicsEngine& getPhysicsEngine();
	static void deconstruct();
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
	Physics::Collider collision(Component::TransformComponent* motion, Physics::BoundingBox box, Core::Vector2 speed);

	const double Gravity = 2;

	//This is for what? (21/03/16)
	//std::vector<RigidComponent*> checkList;

	void addPhysics(Component::HitboxComponent* obj);
	void addPhysics(Component::RigidComponent* obj);
	void removePhysics(Component::RigidComponent* obj);
	void removePhysics(Component::HitboxComponent* obj);

private:

	std::vector<Component::HitboxComponent*> hitboxes;
	std::vector<Component::RigidComponent*> rigids;

	void simulation();

	void gravity();
	//	float SweptAABB(RigidComponent* inMotion,HitboxComponent* b22,float& normalx,float& normaly,Vector2 speed);
};
#endif