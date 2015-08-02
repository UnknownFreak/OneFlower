#ifndef Physics_HPP
#define Physics_HPP
#include <vector>
#define PixelInOneMeter 128
class GameObject;
class RigidComponent;
class HitboxComponent;
#include "Vector.h"
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

private:
	std::pair<GameObject*,double> collision(RigidComponent* inMotion,Vector2 speed);
	void simulation();
	void gravity();
	float SweptAABB(RigidComponent* inMotion,HitboxComponent* b22,float& normalx,float& normaly,Vector2 speed);

	//LOW Move this out of Physics engine?
	std::vector<HitboxComponent*> hitboxes;
	std::vector<RigidComponent*> rigid;
	std::vector<RigidComponent*> checkList;
};
#endif