#include "RenderComponent.h"
#include "GameObject.h"
#include "../Gfx.h"

unsigned int IBaseComponent<RenderComponent>::typeID = 1002;

RenderComponent::RenderComponent()
{
	componentName = "RenderComponent";
	sprite.setTexture(*SetGfx()->requestTexture(textureName));
	sprite.setOrigin(sprite.getScale().x / 2,sprite.getScale().y / 2);

}
RenderComponent::RenderComponent(std::string texture)
{
	componentName = "RenderComponent";
	textureName = texture;
	sprite.setTexture(*SetGfx()->requestTexture(textureName));
	sprite.setOrigin(sprite.getScale().x / 2,sprite.getScale().y / 2);

}