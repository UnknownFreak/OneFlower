#ifndef ObjectType_HPP
#define ObjectType_HPP
namespace Enums
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
		EndIteration,
		EoF = 254,
		Undefined
	};

	inline of::common::String to_string(const Enums::ObjectType& type)
	{
		switch (type)
		{
		case Enums::ObjectType::Header: return "Header";
		case Enums::ObjectType::Prefab: return "Prefab";
		case Enums::ObjectType::Quest: return "Quest";
		case Enums::ObjectType::Item: return "Item";
		case Enums::ObjectType::Model: return "Model";
		case Enums::ObjectType::DBZone: return "DBZone";
		case Enums::ObjectType::PrimitiveInt: return "PrimitiveInt";
		case Enums::ObjectType::PrimitiveDouble: return "PrimitiveDouble";
		case Enums::ObjectType::PrimitiveString: return "PrimitiveString";
		case Enums::ObjectType::StringList: return "StringList";
		case Enums::ObjectType::Element: return "Element";
		case Enums::ObjectType::Rank: return "Rank";
		case Enums::ObjectType::Language: return "Language";
		case Enums::ObjectType::TranslationString: return "TranslationString";
		case Enums::ObjectType::TileChunk: return "TileChunk";
		case Enums::ObjectType::ColliderChunk: return "ColliderChunk";
		case Enums::ObjectType::DialogTree: return "DialogTree";
		case Enums::ObjectType::Effect: return "Effect";
		case Enums::ObjectType::Skill: return "Skill";
		case Enums::ObjectType::WorldInstance: return "WorldInstance";
		case Enums::ObjectType::EoF: return "EoF";
		case Enums::ObjectType::Undefined: return "Undefined";
		default: return "Unknown";

		}
	}
	inline bool hide_from_view(const Enums::ObjectType& type)
	{
		switch (type)
		{
		case Enums::ObjectType::Header: return true;
		//case Enums::ObjectType::Prefab: return "Prefab";
		//case Enums::ObjectType::Quest: return "Quest";
		//case Enums::ObjectType::Item: return "Item";
		//case Enums::ObjectType::Model: return "Model";
		//case Enums::ObjectType::DBZone: return "DBZone";
		//case Enums::ObjectType::PrimitiveInt: return "PrimitiveInt";
		//case Enums::ObjectType::PrimitiveDouble: return "PrimitiveDouble";
		//case Enums::ObjectType::PrimitiveString: return "PrimitiveString";
		//case Enums::ObjectType::StringList: return "StringList";
		//case Enums::ObjectType::Element: return "Element";
		//case Enums::ObjectType::Rank: return "Rank";
		case Enums::ObjectType::Language: return true;
		case Enums::ObjectType::TranslationString: return true;
		case Enums::ObjectType::TileChunk: return true;
		case Enums::ObjectType::ColliderChunk: return true;
		case Enums::ObjectType::WorldInstance: return true;
		case Enums::ObjectType::EoF: return true;
		case Enums::ObjectType::Undefined: return false;
		default: return false;

		}
	}
}
#endif