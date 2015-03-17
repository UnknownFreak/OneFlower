#include "RenderComponent.h"
#include "../Gfx.h"
#include "../Engine.hpp"
#include "../EditorUI/UIAddon.hpp"
const unsigned int IBaseComponent<RenderComponent>::typeID = 1002;
std::string IBaseComponent<RenderComponent>::componentName = "RenderComponent";

RenderComponent::RenderComponent()
{
	setTexture();
}
RenderComponent::RenderComponent(const RenderComponent &rcp) : textureName(rcp.textureName), renderlayer(rcp.renderlayer), size(rcp.size)
{
		sprite.setScale(rcp.sprite.getScale());
		sprite.setTexture(*Engine::Graphic.requestTexture(textureName),true);
		sprite.setOrigin(sprite.getScale().x / 2, sprite.getScale().y / 2);
		sprite.setTextureRect(sf::IntRect(0,0,size.x,size.y));
}
RenderComponent::RenderComponent(std::string texture) : textureName(texture), size(0,0)
{
	setTexture();
}
void RenderComponent::setTexture()
{
		sprite.setTexture(*Engine::Graphic.requestTexture(textureName),true);
		//spritesetOrigin(spritegetScale().x / 2, spritegetScale().y / 2);
		size.x = sprite.getTexture()->getSize().x;
		size.y = sprite.getTexture()->getSize().y;

}
bool RenderComponent::UpdateFromEditor()
{
	Engine::Graphic.removeFromDrawList(attachedOn);
	Engine::Graphic.insertDrawableObject(attachedOn);

	setTexture();

	return true;
}
void RenderComponent::attachOn(GameObject* attachTo)
{
	RenderComponent::BaseComponent::attachOn(attachTo);

	Engine::Graphic.removeFromDrawList(attachedOn);
	Engine::Graphic.insertDrawableObject(attachedOn);

	REGISTER_EDITOR_VARIABLE(int, renderlayer, Layer);
	REGISTER_EDITOR_VARIABLE(std::string,textureName,Texture);
	REGISTER_EDITOR_VARIABLE(bool,animation,Animation);

}
/*
sf::Sprite& RenderComponent::sprite()
{

	return &image;
}*/

