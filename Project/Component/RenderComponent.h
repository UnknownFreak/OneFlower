#ifndef RenderComponent_H
#define RenderComponent_H
#include <SFML\Graphics\Sprite.hpp>	
#include "IBaseComponent.hpp"
#include "cereal\access.hpp"

class RenderComponent : public IBaseComponent<RenderComponent>
{
public:

	RenderComponent();
	RenderComponent(std::string texture);

	sf::Sprite sprite;
	int renderlayer = 1;
	std::string textureName = "test.png";
private:
	template < class Archive>//, GameObject& go>
	friend void save(Archive& archive, const RenderComponent& rc);
	template < class Archive>//, GameObject& go>
	friend void load(Archive& archive, RenderComponent& rc);
};




#endif