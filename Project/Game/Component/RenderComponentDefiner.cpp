#include "RenderComponent.h"
#include "../Gfx.h"
#include "../../Engine.hpp"
#include <SFML\Graphics\Texture.hpp>
const unsigned int IBaseComponent<RenderComponent>::typeID = 1002;
std::string IBaseComponent<RenderComponent>::componentName = "RenderComponent";
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
}

void RenderComponent::setTexture()
{
	sprite.setTexture(*Engine::Graphic.requestTexture(textureName),true);
}
void RenderComponent::setTexture(std::string texture)
{
	sprite.setTexture(*Engine::Graphic.requestTexture(texture),true);

	textureName = texture;
	size.x = sprite.getTexture()->getSize().x;
	size.y = sprite.getTexture()->getSize().y;
}
void RenderComponent::setTexture(std::string texture,int x,int y,int width,int height)
{
	//fix this
	sprite.setTexture(*Engine::Graphic.requestTexture(texture),false);
	sprite.setTextureRect(sf::IntRect(position.x,position.y,width,height));

	textureName = texture;
	size.x = width;
	size.y = height;
}

void RenderComponent::setAnimation(std::string animationName)
{
	switch (animation)
	{
		case RenderComponent::Static:
			return;
		case RenderComponent::SpriteSheet:
			if (animations.find(animationName) != animations.end())
			{
				currentAnimation = animationName;
			}
			break;
		case RenderComponent::Armature:
		{
		// TODO:
		}
		break;
	}
}

bool RenderComponent::updateFromEditor()
{
	if(animation)
		setAnimation(currentAnimation);
	else
		setTexture(textureName,position.x,position.y,size.x,size.y);

	Engine::Graphic.removeFromdrawList(attachedOn);
	Engine::Graphic.insertdrawableObject(attachedOn);

	return true;
}
void RenderComponent::attachOn(GameObject* attachTo)
{
	RenderComponent::BaseComponent::attachOn(attachTo);

	Engine::Graphic.removeFromdrawList(attachedOn);
	Engine::Graphic.insertdrawableObject(attachedOn);
}
void RenderComponent::updateFrame()
{
	switch (animation)
	{
	case RenderComponent::Static:
		return;
	case RenderComponent::SpriteSheet:
	{
		if (animations.find(currentAnimation) != animations.end())
		{
			if (animations[currentAnimation].CurrentTime > animations[currentAnimation].AnimationTime)
			{
				if (animations[currentAnimation].looping)
					animations[currentAnimation].CurrentTime -= animations[currentAnimation].AnimationTime;
			}
			else
				animations[currentAnimation].CurrentTime += Engine::time.deltaTime();
			{
				sf::IntRect r = animations[currentAnimation].getCurrentAnimationFrame();
				if (!(r.width == r.height == 0))
					sprite.setTextureRect(r);
			}
		}
	}
		break;
	case RenderComponent::Armature:
		//todo
		break;
	default:
		break;

	}
}