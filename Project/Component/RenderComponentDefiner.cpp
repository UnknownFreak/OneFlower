#include "RenderComponent.h"
#include "../Gfx.h"
#include "../Engine.hpp"
#include "../EditorUI/UIAddon.hpp"
const unsigned int IBaseComponent<RenderComponent>::typeID = 1002;
std::string IBaseComponent<RenderComponent>::componentName = "RenderComponent";

RenderComponent::RenderComponent()
{
	REGISTER_EDITOR_VARIABLE(int,renderlayer,Layer);
	REGISTER_EDITOR_VARIABLE(std::string,textureName,Texture); 
	
	sprite.setTexture(*Engine::Graphic.requestTexture(textureName));
	sprite.setOrigin(sprite.getScale().x / 2,sprite.getScale().y / 2);

}
RenderComponent::RenderComponent(const RenderComponent &rcp)
{
	REGISTER_EDITOR_VARIABLE(int,renderlayer,Layer);
	REGISTER_EDITOR_VARIABLE(std::string,textureName,Texture);
	componentName = rcp.componentName;
	textureName = rcp.textureName;
	renderlayer = rcp.renderlayer;
	sprite.setScale(rcp.sprite.getScale());
	sprite.setTexture(*Engine::Graphic.requestTexture(textureName));
	sprite.setOrigin(sprite.getScale().x / 2, sprite.getScale().y / 2);
}
RenderComponent::RenderComponent(std::string texture)
{
	REGISTER_EDITOR_VARIABLE(int,renderlayer,Layer);
	REGISTER_EDITOR_VARIABLE(std::string,textureName,Texture);
	componentName = "RenderComponent";
	textureName = texture;
	sprite.setTexture(*Engine::Graphic.requestTexture(textureName));
	sprite.setOrigin(sprite.getScale().x / 2,sprite.getScale().y / 2);
}
bool RenderComponent::UpdateFromEditor()
{
	Engine::Graphic.removeFromDrawList(attachedOn);
	Engine::Graphic.insertDrawableObject(attachedOn);

	return true;
}