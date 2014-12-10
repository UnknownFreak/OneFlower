#ifndef EnvironmentColliderComponent_H
#define EnvironmentColliderComponent_H
#include <SFML\Graphics\Sprite.hpp>
#include "IBaseComponent.hpp"

class EnvironmentColliderComponent : public IBaseComponent<EnvironmentColliderComponent>
{
public:
	EnvironmentColliderComponent();
	EnvironmentColliderComponent(const EnvironmentColliderComponent &ecc);
	std::string getTypeName();
	//Make a moving object collide with an obstacle (not collision detection)
	void environmentCollision(sf::Sprite *movingSprite, sf::Sprite obstacleSprite);
private:
};

#endif