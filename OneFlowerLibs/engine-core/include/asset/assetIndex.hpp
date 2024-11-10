#pragma once

#include <asset/objectFlag.hpp>
#include <asset/objectType.hpp>

#include <utils/common/uuid.hpp>
#include <utils/common/String.hpp>

#include <utils/common/Version.hpp>

namespace of::asset
{

	class AssetIndex
	{
		OneVersion modFileVersion;

	public:
		long long row;
		common::uuid ID;

		inline AssetIndex() noexcept : row(0), ID(), modFile(""), type(ObjectType::Undefined), flags(ObjectFlag::NoFlag), modFileVersion(OneVersion(1, 0, 0))
		{
		}


		/*
		Type of object to load:
		Zone - load a zonefile
		Prefab - load a prefab
		Gameobject - load a Gameobject
		Quest - load a quest
		Item - load a item
		//*/
		ObjectType type;
		common::uuid typeId;
		/*
		Flag types:
		EoF - says it is the endof the file - Do not use, it is automatic.
		Override - SourceID - Overrides object with a new one
		AddTo - SourceID - Adds object to source
		RemoveFrom - SourceID - removes object from source.
		Modify - SourceID - Modify flag tells to modifiy that object
		"-" - No flag
		//*/
		ObjectFlag flags;
		/*
		ModFile tells from what mod that object comes from
		//*/
		common::String modFile;

	public:
		template<class Archive>
		void load(Archive& ar)
		{
			OneVersion myVersion = OneVersion::EMPTY;
			ar(myVersion);
			// do difference logic here for changes in this file.
			modFileVersion = myVersion;
			ar(row);
			ar(ID);
			ar(type);
			ar(typeId);
			ar(flags);
			ar(modFile);
		}
		template<class Archive>
		void save(Archive& ar) const
		{
			ar(modFileVersion);
			ar(row);
			ar(ID);
			ar(type);
			ar(typeId);
			ar(flags);
			ar(modFile);
		}
	};
}
