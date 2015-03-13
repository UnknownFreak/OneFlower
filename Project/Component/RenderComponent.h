#ifndef RenderComponent_H
#define RenderComponent_H
#include <SFML\Graphics\Sprite.hpp>	
#include "IBaseComponent.hpp"
#include "cereal\access.hpp"
#include <exception>
#include "../Vector.h"

class RenderComponent : public IBaseComponent<RenderComponent>
{
public:

	RenderComponent();
	RenderComponent(const RenderComponent & rc);
	RenderComponent(std::string texture);
	sf::Sprite sprite;
	bool UpdateFromEditor();
	//Closer the bigger the number, Farther away less the number
	int renderlayer = 1;
	Vector2 size;
	//Name of texture;
	std::string textureName = "test.png";
	void attachOn(GameObject* go);
private:
	void setTexture();
	template < class Archive>//, GameObject& go>
	friend void save(Archive& archive, const RenderComponent& rc);
	template < class Archive>//, GameObject& go>
	friend void load(Archive& archive, RenderComponent& rc);
};


#endif