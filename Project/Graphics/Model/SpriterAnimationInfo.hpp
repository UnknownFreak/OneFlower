#ifndef SpriterAnimationInfo_HPP
#define SpriterAnimationInfo_HPP

#include <vector>

#include <Graphics/Spriter/SpriterEngine/spriterengine.h>

#include <Helpers\String.hpp>

class SpriterAnimationInfo
{
	float currentAnimationTime;

	Core::String currentAnimation;

	SpriterEngine::EntityInstance* instance = NULL;

public:

	SpriterAnimationInfo();
	SpriterAnimationInfo(SpriterEngine::EntityInstance* instance);
	SpriterAnimationInfo(SpriterEngine::EntityInstance* instance, float currentAnimationTime, Core::String currentAnimation);

	SpriterAnimationInfo(const SpriterAnimationInfo& copy);

	SpriterAnimationInfo& operator=(const SpriterAnimationInfo& right);


	template <class Archive>
	void serialize(Archive& ar)
	{
		ar(currentAnimationTime);
		ar(currentAnimation);
	}

	void setAnimation(Core::String animation);
	void updateFrame(const size_t& update_ms);

};

#endif