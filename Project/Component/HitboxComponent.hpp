#ifndef HitboxComponent_HPP
#define HitboxComponent_HPP
#include "IBaseComponent.hpp"
#include "../Vector.h"
#include "cereal\access.hpp"
#include <SFML\Graphics\Rect.hpp>
class HitboxComponent:public IBaseComponent < HitboxComponent >
{
public:
	HitboxComponent();
	HitboxComponent(const HitboxComponent &hc);
	HitboxComponent(int width,int height);
	//LOW: Make a Render and Transform constructor
	~HitboxComponent();

	//Absolute Pixel not half pixel
	Vector2 size;

	//Pixel position relative to Transform
	Vector2 position;

	//Rect
	sf::Rect<int> box;
	void attachOn(GameObject* go);

	void onCollision();
	void OnClick();
private:
	template <class Archive>
	void save(Archive &ar,const HitboxComponent &hc);
	template <class Archive>
	void load(Archive &ar,HitboxComponent &hc);
};
#endif