#include "SpriterAnimationInfo.hpp"

SpriterAnimationInfo::SpriterAnimationInfo() : instance(NULL), currentAnimationTime(0), currentAnimation("")
{
}

SpriterAnimationInfo::SpriterAnimationInfo(SpriterEngine::EntityInstance * instance) : instance(instance), currentAnimationTime(0), currentAnimation("")
{
}

SpriterAnimationInfo::SpriterAnimationInfo(SpriterEngine::EntityInstance * instance, float currentAnimationTime, Core::String currentAnimation) :
	instance(instance), currentAnimationTime(currentAnimationTime), currentAnimation(currentAnimation)
{
}

SpriterAnimationInfo::SpriterAnimationInfo(const SpriterAnimationInfo & copy) : currentAnimationTime(copy.currentAnimationTime), currentAnimation(copy.currentAnimation),
instance(copy.instance)
{
}

SpriterAnimationInfo & SpriterAnimationInfo::operator=(const SpriterAnimationInfo & right)
{
	currentAnimationTime = right.currentAnimationTime;
	currentAnimation = right.currentAnimation;
	instance = right.instance;
	return *this;
}

void SpriterAnimationInfo::setAnimation(Core::String animation)
{
	instance->setCurrentAnimation(animation);
	currentAnimationTime = 0;
}

void SpriterAnimationInfo::updateFrame(const size_t& update_ms)
{
	instance->setCurrentAnimation(currentAnimation);
	currentAnimationTime += update_ms / 10.0f;
	instance->setCurrentTime(currentAnimationTime);
	if (instance->animationJustFinished(true))
		currentAnimationTime = 0.0;
}
