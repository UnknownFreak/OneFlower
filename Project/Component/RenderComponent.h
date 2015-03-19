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

	bool UpdateFromEditor();
	void attachOn(GameObject* go);
	void updateFrame();
	//Closer the bigger the number, Farther away less the number
	int renderlayer = 1;


	bool animation = false;

	//size of the rectangle for animation
	Vector2 size;

	//Name of texture;
	std::string textureName = "test.png";

	sf::Sprite sprite;
	float currentFrame = 1;

private:
	//For non animation texture
	void setTexture();
	//the size of each frame, For animation use
	void setTexture(int x,int y);
	template < class Archive>//, GameObject& go>
	friend void save(Archive& archive, const RenderComponent& rc);
	template < class Archive>//, GameObject& go>
	friend void load(Archive& archive, RenderComponent& rc);
};


#endif