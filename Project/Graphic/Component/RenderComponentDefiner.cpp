#include "RenderComponent.h"

#include "../GraphicsCore.hpp"

const unsigned int IBaseComponent<Component::RenderComponent>::typeID = 1002;
std::string IBaseComponent<Component::RenderComponent>::componentName = "RenderComponent";

namespace Component
{
	RenderComponent::~RenderComponent()
	{
		if(attachedOn)
			Engine::Graphic.removeFromdrawList(attachedOn);
	}
	RenderComponent::RenderComponent()
	{
		setTexture();
	}
	RenderComponent::RenderComponent(const RenderComponent &rcp) : textureName(rcp.textureName), renderlayer(rcp.renderlayer), size(rcp.size), animation(rcp.animation)
		, animations(rcp.animations), instance(rcp.instance), sprite(rcp.sprite)
	{
		//sprite.setOrigin(sprite.getScale().x / 2,sprite.getScale().y / 2);
		sprite.setTextureRect(sf::IntRect(0, 0, size.x, size.y));
	}
	RenderComponent::RenderComponent(std::string texture) : textureName(texture), size(0, 0)
	{
		setTexture(texture);
	}
	RenderComponent::RenderComponent(std::string texture, int x, int y) : textureName(texture), size(x, y)
	{
		TextureRef* tf = Engine::Textureloader.requestTexture(texture);
		tf->useCount++;
		sprite.setTexture(tf, true);
	}

	RenderComponent * RenderComponent::copy()
	{
		return new RenderComponent(*this);
	}

	void RenderComponent::setTexture()
	{
		sprite.setTexture(Engine::Textureloader.requestTexture(textureName), true);
	}
	void RenderComponent::setTexture(std::string texture)
	{
		sprite.setTexture(Engine::Textureloader.requestTexture(texture), true);

		textureName = texture;
		sprite.waitForTextureLoaded();
		size.x = sprite.getTexture()->getSize().x;
		size.y = sprite.getTexture()->getSize().y;
	}
	void RenderComponent::setTexture(std::string texture, double x, double y, int width, int height)
	{
		//fix this
		sprite.setTexture(Engine::Textureloader.requestTexture(texture), false);
		sprite.setTextureRect(sf::IntRect((int)x, (int)y, width, height));
		textureName = texture;
		size.x = width;
		size.y = height;
	}

	void RenderComponent::setAnimation(std::string animationName)
	{
		switch (animation)
		{
		case RenderComponent::AnimationType::Static:
			return;
		case RenderComponent::AnimationType::SpriteSheet:
			if (animations.find(animationName) != animations.end())
			{
				currentAnimation = animationName;
			}
			break;
		case RenderComponent::AnimationType::Armature:
		{
			if (instance.MyEntityInstance)
			{
				if (instance.MyEntityInstance->currentAnimationName() != "sword_swing_0")
				{
					instance.MyEntityInstance->setCurrentTime(0);
					instance.MyEntityInstance->setCurrentAnimation(animationName);
				}
				else if (instance.MyEntityInstance->currentAnimationName() == "sword_swing_0" && instance.MyEntityInstance->animationJustFinished(true))
				{
					instance.MyEntityInstance->setCurrentTime(0);
					instance.MyEntityInstance->setCurrentAnimation(animationName);
				}
			}
		}
		break;
		}
	}
	void RenderComponent::setFacing(Facing f)
	{
		facingDirection = f;
		if (instance.MyEntityInstance)
			if (facingDirection == Facing::Left)
				instance.MyEntityInstance->setScale(SpriterEngine::point(-1, 1));
			else
				instance.MyEntityInstance->setScale(SpriterEngine::point(1, 1));
	}
	bool RenderComponent::updateFromEditor()
	{
		if (animation != AnimationType::Static)
			setAnimation(currentAnimation);
		else
			setTexture(textureName, position.x, position.y, size.x, size.y);

		Engine::Graphic.removeFromdrawList(attachedOn);
		Engine::Graphic.insertDrawableObject(attachedOn);

		return true;
	}
	void RenderComponent::attachOn(GameObject* attachTo)
	{
		RenderComponent::BaseComponent::attachOn(attachTo);

		Engine::Graphic.removeFromdrawList(attachedOn);
		Engine::Graphic.insertDrawableObject(attachedOn);
	}
	void RenderComponent::updateFrame()
	{
		switch (animation)
		{
		case RenderComponent::AnimationType::Static:
			return;
		case RenderComponent::AnimationType::SpriteSheet:
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
		case RenderComponent::AnimationType::Armature:
			if (instance.MyEntityInstance)
			{
				instance.MyEntityInstance->setTimeElapsed(Engine::time.update_ms.asSeconds() * 30);
				if (instance.MyEntityInstance->animationJustFinished(true) && instance.MyEntityInstance->currentAnimationName() == "jump_start")
					setAnimation("jump_loop");
				if (instance.MyEntityInstance->animationJustFinished(true) && instance.MyEntityInstance->currentAnimationName() == "crouch_down")
					setAnimation("crouch_idle");
				if (instance.MyEntityInstance->animationJustFinished(true) && instance.MyEntityInstance->currentAnimationName() == "stand_up")
					setAnimation("idle");
				if (instance.MyEntityInstance->animationJustFinished(true) && instance.MyEntityInstance->currentAnimationName() == "sword_swing_0")
					setAnimation("idle");
			}
			break;
		default:
			break;
		}
	}
	void RenderComponent::getMessage(const BaseMessage message)
	{
		if (message.msg == "walk")
			setAnimation("walk");
		else if (message.msg == "idle")
			setAnimation("idle");
		else if (message.msg == "crouch")
			setAnimation("crouch_down");
		else if (message.msg == "stand_up")
			setAnimation("stand_up");
		else if (message.msg == "jump")
			setAnimation("jump_start");
		else if (message.msg == "attack")
			setAnimation("sword_swing_0");
		else if (message.msg == "right")
			setFacing(Facing::Right);
		else if (message.msg == "left")
			setFacing(Facing::Left);
	}
}