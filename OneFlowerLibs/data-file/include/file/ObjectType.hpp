#ifndef ObjectType_HPP
#define ObjectType_HPP

#include <utils/common/string.hpp>

namespace of::file
{
	enum class ObjectType
	{
		Header = 0,
		Prefab,
		Quest,
		Item,
		Model,
		DBZone,
		PrimitiveInt,
		PrimitiveDouble,
		PrimitiveString,
		StringList,
		Element,
		Rank,
		Language,
		TranslationString,
		TileChunk,
		ColliderChunk,
		DialogTree,
		Effect,
		Skill,
		WorldInstance,
		CutScene,
		EndIteration,
		EoF = 254,
		Undefined
	};

	inline common::String to_string(const ObjectType& type)
	{
		switch (type)
		{
		case ObjectType::Header: return "Header";
		case ObjectType::Prefab: return "Prefab";
		case ObjectType::Quest: return "Quest";
		case ObjectType::Item: return "Item";
		case ObjectType::Model: return "Model";
		case ObjectType::DBZone: return "DBZone";
		case ObjectType::PrimitiveInt: return "PrimitiveInt";
		case ObjectType::PrimitiveDouble: return "PrimitiveDouble";
		case ObjectType::PrimitiveString: return "PrimitiveString";
		case ObjectType::StringList: return "StringList";
		case ObjectType::Element: return "Element";
		case ObjectType::Rank: return "Rank";
		case ObjectType::Language: return "Language";
		case ObjectType::TranslationString: return "TranslationString";
		case ObjectType::TileChunk: return "TileChunk";
		case ObjectType::ColliderChunk: return "ColliderChunk";
		case ObjectType::DialogTree: return "DialogTree";
		case ObjectType::Effect: return "Effect";
		case ObjectType::Skill: return "Skill";
		case ObjectType::WorldInstance: return "WorldInstance";
		case ObjectType::CutScene: return "CutScene";
		case ObjectType::EoF: return "EoF";
		case ObjectType::Undefined: return "Undefined";
		default: return "Unknown";

		}
	}
	inline bool hide_from_view(const ObjectType& type)
	{
		switch (type)
		{
		case ObjectType::Header: return true;
		//case ObjectType::Prefab: return "Prefab";
		//case ObjectType::Quest: return "Quest";
		//case ObjectType::Item: return "Item";
		//case ObjectType::Model: return "Model";
		//case ObjectType::DBZone: return "DBZone";
		//case ObjectType::PrimitiveInt: return "PrimitiveInt";
		//case ObjectType::PrimitiveDouble: return "PrimitiveDouble";
		//case ObjectType::PrimitiveString: return "PrimitiveString";
		//case ObjectType::StringList: return "StringList";
		//case ObjectType::Element: return "Element";
		//case ObjectType::Rank: return "Rank";
		case ObjectType::Language: return true;
		case ObjectType::TranslationString: return true;
		case ObjectType::TileChunk: return true;
		case ObjectType::ColliderChunk: return true;
		case ObjectType::WorldInstance: return true;
		case ObjectType::CutScene: return true;
		case ObjectType::EoF: return true;
		case ObjectType::Undefined: return false;
		default: return false;

		}
	}
}
#endif