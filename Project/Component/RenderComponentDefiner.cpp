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
	
	if (!Engine::Graphic.loadTexture(textureName))
		throw MissingTextureException(*this);
	else
	{
		 
		sprite.setTexture(*Engine::Graphic.requestTexture(textureName));
		sprite.setOrigin(sprite.getScale().x / 2, sprite.getScale().y / 2);
		size.x = sprite.getTexture()->getSize().x;
		size.y = sprite.getTexture()->getSize().y;
	}

}
RenderComponent::RenderComponent(const RenderComponent &rcp)
{
	REGISTER_EDITOR_VARIABLE(int,renderlayer,Layer);
	REGISTER_EDITOR_VARIABLE(std::string,textureName,Texture);
	textureName = rcp.textureName;
	renderlayer = rcp.renderlayer;
	size.x = rcp.size.x;
	size.y = rcp.size.y;
	if (!Engine::Graphic.loadTexture(textureName))
		throw MissingTextureException(*this);
	else
	{
		sprite.setScale(rcp.sprite.getScale());
		sprite.setTexture(*Engine::Graphic.requestTexture(textureName));
		sprite.setOrigin(sprite.getScale().x / 2, sprite.getScale().y / 2);
		sprite.setTextureRect(sf::IntRect(0,0,size.x,size.y));
	}
}
RenderComponent::RenderComponent(std::string texture)
{
	REGISTER_EDITOR_VARIABLE(int,renderlayer,Layer);
	REGISTER_EDITOR_VARIABLE(std::string,textureName,Texture);
	textureName = texture;
	if (!Engine::Graphic.loadTexture(textureName))
		throw MissingTextureException(*this);
	else
	{
		sprite.setTexture(*Engine::Graphic.requestTexture(textureName));
		sprite.setOrigin(sprite.getScale().x / 2, sprite.getScale().y / 2);
		size.x = sprite.getTexture()->getSize().x;
		size.y = sprite.getTexture()->getSize().y;
	}
}
bool RenderComponent::UpdateFromEditor()
{
	Engine::Graphic.removeFromDrawList(attachedOn);
	Engine::Graphic.insertDrawableObject(attachedOn);

	//Todo: AddException for missing texture

	return true;
}

MissingTextureException::MissingTextureException(RenderComponent &rcpin)
{
	rcpin.textureName = "test.png";
	rcpin.sprite.setTexture(*Engine::Graphic.requestTexture("test.png"));
	rcpin.sprite.setOrigin(rcpin.sprite.getScale().x / 2, rcpin.sprite.getScale().y / 2);
	rcpin.sprite.setTextureRect(sf::IntRect(0, 0, rcpin.size.x, rcpin.size.y));
	rcp = new RenderComponent(rcpin);
}
MissingTextureException::~MissingTextureException()
{

}
const RenderComponent& MissingTextureException::what()
{
	rcp->sprite.setTextureRect(sf::IntRect(0, 0, rcp->size.x, rcp->size.y));
	return *rcp;
}