#ifndef RigidComponent_HPP
#define RigidComponent_HPP
#include "IBaseComponent.hpp"
#include <vector>
#include "../Vector.h"
class RigidComponent :public IBaseComponent < RigidComponent >
{
public:

	//LOW: Remove this if not needed
	//TODO Add other constructors
	RigidComponent();
	~RigidComponent();
	RigidComponent(const RigidComponent & copy) = default;
	void addForce(Vector2 dir, float power);
	void attachOn(GameObject* go);
	std::vector<std::pair<Vector2, double>> forceQueue;

	//Absolute Pixel not half pixel
	Vector2 size;

	//Pixel position relative to Transform
	Vector2 position;

	//Colliding
	bool colliding = false;

	//Colliding Object. [0] up and than go Clock-Wise
	GameObject* colisionDirection[4];

	bool gravity = false;

	//Mass in Kilogram
	int Mass = 10;

	std::vector<GameObject*> entered;

	template<class Archive>
	friend void save(Archive &ar, const RigidComponent& rep);
	template<class Archive>
	friend void load(Archive &ar, RigidComponent& rep);
};

#endif