#include "RenderComponent.h"

#include <Asset\AssetManagerCore.hpp>
#include <Core\EngineModule\EngineModuleManager.hpp>
#include "../Gfx.h"

#include <Model\SpriterModel_.hpp>

const unsigned int Component::IBaseComponent<Component::RenderComponent>::typeID = 1002;
Core::String Component::IBaseComponent<Component::RenderComponent>::componentName = "RenderComponent";

namespace Component
{
	RenderComponent::~RenderComponent()
	{
		if(attachedOn)
			Engine::GetModule<Gfx>().removeFromdrawList(attachedOn);
		if (model)
			delete model;
	}
	RenderComponent::RenderComponent()
	{
		setTexture();
	}
	RenderComponent::RenderComponent(const RenderComponent &rcp) : textureName(rcp.textureName), renderlayer(rcp.renderlayer), sprite(rcp.sprite)
	{
	}
	RenderComponent::RenderComponent(Core::String texture) : textureName(texture)
	{
		setTexture(texture);
	}
	RenderComponent::RenderComponent(Core::String texture, int x, int y) : textureName(texture)
	{
		TextureRef* tf = Engine::GetModule<Asset::AssetManager>().textureloader.requestTexture(texture);
		tf->useCount++;
		sprite.setTexture(tf, true);
	}

	RenderComponent * RenderComponent::copy() const
	{
		return new RenderComponent(*this);
	}

	void RenderComponent::setTexture()
	{
		sprite.setTexture(Engine::GetModule<Asset::AssetManager>().textureloader.requestTexture(textureName), true);
	}
	void RenderComponent::setTexture(Core::String texture)
	{
		sprite.setTexture(Engine::GetModule<Asset::AssetManager>().textureloader.requestTexture(texture), true);

		textureName = texture;
		sprite.waitForTextureLoaded();
	}
	void RenderComponent::setTexture(Core::String texture, double x, double y, int width, int height)
	{
		//fix this
		sprite.setTexture(Engine::GetModule<Asset::AssetManager>().textureloader.requestTexture(texture), false);
		sprite.setTextureRect(sf::IntRect((int)x, (int)y, width, height));
		textureName = texture;
	}

	void RenderComponent::setAnimation(Core::String animationName)
	{
		model->setAnimation(animationName);
	}
	void RenderComponent::setFacing(Facing f)
	{
		facingDirection = f;
		if(model->isFaceable())
			if (facingDirection == Facing::Left)
				((Model::SpriterModel*)model)->myEntity->setScale(SpriterEngine::point(-1, 1));
			else
				((Model::SpriterModel*)model)->myEntity->setScale(SpriterEngine::point(1, 1));
	}
	bool RenderComponent::updateFromEditor()
	{
		Engine::GetModule<Gfx>().removeFromdrawList(attachedOn);
		Engine::GetModule<Gfx>().insertDrawableObject(attachedOn);

		return true;
	}
	void RenderComponent::attachOn(GameObject* attachTo)
	{
		RenderComponent::Base::attachOn(attachTo);

		Engine::GetModule<Gfx>().removeFromdrawList(attachedOn);
		Engine::GetModule<Gfx>().insertDrawableObject(attachedOn);
	}
	void RenderComponent::updateFrame(const size_t& update_ms)
	{
		model->updateFrame(update_ms);

		//if (instance.MyEntityInstance)
		//{
		//	if (instance.MyEntityInstance->animationJustFinished(true) && instance.MyEntityInstance->currentAnimationName() == "jump_start")
		//		setAnimation("jump_loop");
		//	if (instance.MyEntityInstance->animationJustFinished(true) && instance.MyEntityInstance->currentAnimationName() == "crouch_down")
		//		setAnimation("crouch_idle");
		//	if (instance.MyEntityInstance->animationJustFinished(true) && instance.MyEntityInstance->currentAnimationName() == "stand_up")
		//		setAnimation("idle");
		//	if (instance.MyEntityInstance->animationJustFinished(true) && instance.MyEntityInstance->currentAnimationName() == "sword_swing_0")
		//		setAnimation("idle");
		//}
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