#ifndef HitboxComponent_HPP
#define HitboxComponent_HPP
#include <SFML\Graphics\Rect.hpp>
#include <vector>
#include "../Logic/Physics/BoundingBox.hpp"
#include "IBaseComponent.hpp"
#include "../../Vector.h"
class HitboxComponent:public IBaseComponent < HitboxComponent >
{
public:
	HitboxComponent();
	HitboxComponent(const HitboxComponent &hc);
	HitboxComponent(int x,int y,int w,int h);

	//LOW: Make a Render and Transform constructor ??
	~HitboxComponent();

	void registerCollisionCheck(BaseComponent* component);

	Physics::BoundingBox bounding;


	std::vector<BaseComponent*> collisionCall;

protected:
	void attachOn(GameObject* go);

private:
	sf::Rect<int> box;

	template <class Archive>
	void save(Archive &ar,const HitboxComponent &hc);
	template <class Archive>
	void load(Archive &ar,HitboxComponent &hc);
};
#endif