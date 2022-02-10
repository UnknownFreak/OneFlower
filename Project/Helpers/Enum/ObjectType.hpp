#ifndef ObjectType_HPP
#define ObjectType_HPP
namespace Enums
{
	enum class ObjectType
	{
		Header = 0,
		Zone,
		Prefab,
		GameObject,
		Quest,
		Item,
		ModelContainer,
		SpriteSheetMap,
		Model,
		DBZone,
		TextureMap,
		PrimitiveInt,
		PrimitiveDouble,
		PrimitiveString,
		StringList,
		Element,
		Rank,
		TileAtlas,
		Language,
		TileChunk,
		ColliderChunk,
		DialogTree,
		Effect,
		Skill,
		WorldInstance,
		EoF = 254,
		Undefined
	};

	inline Core::String to_string(const Enums::ObjectType& type)
	{
		switch (type)
		{
		case Enums::ObjectType::Header: return "Header";
		case Enums::ObjectType::Zone: return "Zone";
		case Enums::ObjectType::Prefab: return "Prefab";
		case Enums::ObjectType::GameObject: return "GameObject";
		case Enums::ObjectType::Quest: return "Quest";
		case Enums::ObjectType::Item: return "Item";
		case Enums::ObjectType::ModelContainer: return "ModelContainer";
		case Enums::ObjectType::SpriteSheetMap: return "SpriteSheetMap";
		case Enums::ObjectType::Model: return "Model";
		case Enums::ObjectType::DBZone: return "DBZone";
		case Enums::ObjectType::TextureMap: return "TextureMap";
		case Enums::ObjectType::PrimitiveInt: return "PrimitiveInt";
		case Enums::ObjectType::PrimitiveDouble: return "PrimitiveDouble";
		case Enums::ObjectType::PrimitiveString: return "PrimitiveString";
		case Enums::ObjectType::StringList: return "StringList";
		case Enums::ObjectType::Element: return "Element";
		case Enums::ObjectType::Rank: return "Rank";
		case Enums::ObjectType::TileAtlas: return "TileAtlas";
		case Enums::ObjectType::Language: return "Language";
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
}
#endif