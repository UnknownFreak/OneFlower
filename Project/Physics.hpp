#ifndef Physics_HPP
#define Physics_HPP
#include <vector>
//LOW do I really need to include Quad?
#include "PhysicsQuad.hpp"
class GameObject;
class RigidComponent;
class PhysicsEngine
{
public:
	PhysicsEngine();
	void Update();

	void addPhysics(GameObject* obj);
	void addPhysics(HitboxComponent* obj);
	void addPhysics(RigidComponent* obj);

	void removePhysics(RigidComponent* obj);
	void removePhysics(HitboxComponent* obj);
	void removePhysics(GameObject* obj);

private:
	//LOW Move this out of Physics engine?
	std::vector<HitboxComponent*> hitboxes;
	std::vector<RigidComponent*> rigid;
	std::vector<HitboxComponent*> checkList;
	
	PhysicsQuad quad;

};
#endif