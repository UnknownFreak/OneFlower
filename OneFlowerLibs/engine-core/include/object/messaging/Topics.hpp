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
		TRANSFORM_SPEED_MODIFIER,
		ON_DEATH,
		ON_DELETE,
		ON_COLLISION,
		REQUEST_DATA,
	};

	enum class BodyType
	{
		NONE,
		STRING,
		FILE_ID,
		MODIFIER_ID,
		FLOAT_PTR,
		GAMEOBJECT_PTR,
		REQUEST_DATA,
		CUSTOM,
	};

	inline consteval std::string_view to_string(const Topics& topic)
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
		case Topics::ON_DEATH:
			return "ON_DEATH";
		case Topics::ON_DELETE:
			return "ON_DELETE";
		case Topics::ON_COLLISION:
			return "ON_COLLISION";
		case Topics::REQUEST_DATA:
			return "REQUEST_DATA";
		default:
			break;
		}
		return "OF_TOPIC_UNKNOWN";
	}

}