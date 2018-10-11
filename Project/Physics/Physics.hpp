#ifndef Physics_HPP
#define Physics_HPP
#include <vector>

#include <Core\Rect.hpp>
#include <Core\EngineModule\IEngineModule.hpp>

#include "Collider.hpp"
#include "QuadTree.hpp"

#define PixelInOneMeter 128
class GameObject;
namespace Component
{
	class RigidComponent;
	class HitboxComponent;
	class Transform;
}
//HIGH: Do non game related physics like weather water etc???
class PhysicsEngine : public IEngineResource<PhysicsEngine>
{

	friend class Gfx;
public:
	PhysicsEngine();

	void update();

	const ResourceType& getType()
	{
		return type;
	}

	/*
	void addPhysics(GameObject* obj);
	void removePhysics(GameObject* obj);
	//*/
	void physics();

	//Fix the collision or remake the flow so that sending gameobject is unnecceray
	Physics::Collider collision(Component::Transform* motion, Core::FloatRect box, Core::Vector2 speed);

	const double Gravity = 2;

	//This is for what? (21/03/16)
	//std::vector<RigidComponent*> checkList;

	void addPhysics(Component::HitboxComponent* obj);
	void addPhysics(Component::RigidComponent* obj);
	void removePhysics(Component::RigidComponent* obj);
	void removePhysics(Component::HitboxComponent* obj);

private:

	QuadTree quadTree;
	std::vector<Component::HitboxComponent*> hitboxes;
	std::vector<Component::RigidComponent*> rigids;

	void simulation();

	void gravity();
	//	float SweptAABB(RigidComponent* inMotion,HitboxComponent* b22,float& normalx,float& normaly,Vector2 speed);
};
#endif