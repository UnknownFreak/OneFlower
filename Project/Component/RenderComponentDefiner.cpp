#include "RenderComponent.h"
#include "../Gfx.h"
#include "../Engine.hpp"
#include "../EditorUI/UIAddon.hpp"
const unsigned int IBaseComponent<RenderComponent>::typeID = 1002;
std::string IBaseComponent<RenderComponent>::componentName = "RenderComponent";
#include <SFML\Graphics\Texture.hpp>
RenderComponent::RenderComponent()
{
	setTexture();
}
RenderComponent::RenderComponent(const RenderComponent &rcp): textureName(rcp.textureName),renderlayer(rcp.renderlayer),size(rcp.size)
{
	sprite.setScale(rcp.sprite.getScale());
	sprite.setTexture(*Engine::Graphic.requestTexture(textureName),true);
	//sprite.setOrigin(sprite.getScale().x / 2,sprite.getScale().y / 2);
	sprite.setTextureRect(sf::IntRect(0,0,size.x,size.y));
}
RenderComponent::RenderComponent(std::string texture): textureName(texture),size(0,0)
{
	setTexture(texture);
}
RenderComponent::RenderComponent(std::string texture,int x,int y) : textureName(texture),size(x,y)
{
	sprite.setTexture(*Engine::Graphic.requestTexture(texture),true);
	animation = false;
}

void RenderComponent::setTexture()
{
	sprite.setTexture(*Engine::Graphic.requestTexture(textureName),true);
}
void RenderComponent::setTexture(std::string texture)
{
	sprite.setTexture(*Engine::Graphic.requestTexture(texture),true);
	animation = false;

	textureName = texture;
	size.x = sprite.getTexture()->getSize().x;
	size.y = sprite.getTexture()->getSize().y;
}
void RenderComponent::setTexture(std::string texture,int x,int y,int width,int height)
{
	sprite.setTexture(*Engine::Graphic.requestTexture(texture),false);
	sprite.setTextureRect(sf::IntRect(position.x,position.y,width,height));

	animation = false;
	textureName = texture;
	size.x = width;
	size.y = height;
}

void RenderComponent::setAnimation(std::string texture,int width,int height)
{
	sprite.setTexture(*Engine::Graphic.requestTexture(texture),false);
	animation = true;
	textureName = texture;
	sprite.setTextureRect(sf::IntRect(0,0,width,height));
	size.x = width;
	size.y = height;
	frame.x = sprite.getTexture()->getSize().x / width;
	frame.y = sprite.getTexture()->getSize().y / height;
}
void RenderComponent::setAnimation(int x,int y,int width,int height)
{
	sprite.setTexture(*Engine::Graphic.requestTexture(textureName),false);
	sprite.setTextureRect(sf::IntRect(x,y,width,height));
	animation = true;
	size.x = width;
	size.y = height;
	frame.x = sprite.getTexture()->getSize().x / width;
	frame.y = sprite.getTexture()->getSize().y / height;
}

bool RenderComponent::UpdateFromEditor()
{
	if(animation)
		setAnimation(0,0,size.x,size.y);
	else
		setTexture(textureName,position.x,position.y,size.x,size.y);

	Engine::Graphic.removeFromDrawList(attachedOn);
	Engine::Graphic.insertDrawableObject(attachedOn);

	return true;
}
void RenderComponent::attachOn(GameObject* attachTo)
{
	RenderComponent::BaseComponent::attachOn(attachTo);

	Engine::Graphic.removeFromDrawList(attachedOn);
	Engine::Graphic.insertDrawableObject(attachedOn);

	REGISTER_EDITOR_VARIABLE(int,renderlayer,Layer);
	REGISTER_EDITOR_VARIABLE(std::string,textureName,Texture);
	REGISTER_EDITOR_VARIABLE(bool,animation,Animation);
	REGISTER_EDITOR_VARIABLE(Vector2,size,RectSize);
	REGISTER_EDITOR_VARIABLE(Vector2,frame,Frames);
	REGISTER_EDITOR_VARIABLE(Vector2,position,Position);
	REGISTER_EDITOR_VARIABLE(double,currentFrame,Frame);
	REGISTER_EDITOR_VARIABLE(int,frameSpeed,AnimationSpeed);
}
void RenderComponent::updateFrame()
{
	if(animation)
	{
		double oldFrame = currentFrame;
		currentFrame += (Engine::time.deltaTime()*(int)((int)frame.x + (int)frame.y))/frameSpeed;
		if((int)currentFrame > (int)oldFrame)
		{
			sf::IntRect rect = sprite.getTextureRect();
			rect.left += rect.width;

			if(rect.left > sprite.getTexture()->getSize().x)
			{
				rect.left = 0;
				rect.top += rect.height;
				if(rect.top > sprite.getTexture()->getSize().y)
					rect.top = 0;
			}
			//LOW: is this needed
			currentFrame -= (int)currentFrame;
			sprite.setTextureRect(rect);
		}
	}
}