#ifndef RenderComponent_H
#define RenderComponent_H
#include <SFML\Graphics\Sprite.hpp>	
#include "IBaseComponent.hpp"
#include "cereal\access.hpp"

class RenderComponent : public IBaseComponent<RenderComponent>
{
public:

	RenderComponent();
	RenderComponent(const RenderComponent & rc);
	RenderComponent(std::string texture);
	sf::Sprite sprite;

	//Closer the bigger the number, Farther away less the number
	int renderlayer = 1;
	
	//Name of texture;
	std::string textureName = "test.png";
private:
	template < class Archive>//, GameObject& go>
	friend void save(Archive& archive, const RenderComponent& rc);
	template < class Archive>//, GameObject& go>
	friend void load(Archive& archive, RenderComponent& rc);
};




#endif