#pragma once

#include <utils/common/string.hpp>

namespace of::object::messaging
{

	enum class Topics
	{
		ADD_DEATH_TRIGGER,
		ADD_MODIFIER,
		SET_ANIMATION,
		INTERACT,
		TOGGLE_STATE,
		TRANSFORM_SPEED_MODIFIER
	};

	enum class BodyType
	{
		NONE,
		STRING,
		FILE_ID,
		MODIFIER_ID,
		FLOAT_PTR,
		CUSTOM
	};

	inline of::common::String to_string(const Topics& topic)
	{
		switch (topic)
		{
		case Topics::ADD_DEATH_TRIGGER:
			return "OF_TOPIC_ADD_MODIFIER";
		case Topics::ADD_MODIFIER:
			return "OF_TOPIC_ADD_MODIFIER";
		case Topics::SET_ANIMATION:
			return "OF_TOPIC_SET_ANIMATION";
		case Topics::INTERACT:
			return "OF_TOPIC_INTERACT";
		case Topics::TOGGLE_STATE:
			return "TOGGLE_STATE";
		case Topics::TRANSFORM_SPEED_MODIFIER:
			return "TRANSFORM_SPEED_MODIFIER";
		default:
			break;
		}
		return "OF_TOPIC_UNKNOWN";
	}

}