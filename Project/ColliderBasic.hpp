#ifndef ColliderBasic_HPP
#define ColliderBasic_HPP

class GameObject;
class Collider
{
public:
	Collider(GameObject* collision);

	GameObject* gameObject;
	bool isTrigger;



};




#endif