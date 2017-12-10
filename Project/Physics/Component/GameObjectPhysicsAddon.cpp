#include <Core\Component\GameObject.h>
#include "../Collider.hpp"

void GameObject::collision(std::vector<Physics::Collider>& msgs)
{
	Physics::Collider& msg = msgs[0];
	for (std::map<int, BaseComponent*>::iterator it = componentMap.begin(); it != componentMap.end(); ++it)
	{
		it->second->onCollision(msg);
	}
}