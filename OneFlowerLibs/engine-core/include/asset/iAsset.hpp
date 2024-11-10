#pragma once

#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>

#include <utils/common/uuid.hpp>
#include <utils/common/String.hpp>
#include <utils/common/Version.hpp>

#include <asset/assetId.hpp>

#include <asset/objectType.hpp>

#include <asset/objectSaveMode.hpp>


namespace of::asset
{
	struct TypeInfo
	{
		common::uuid typeId;
		std::vector<common::uuid> parents;

		bool hasTypeId(const common::uuid& uuid) const noexcept
		{
			return uuid == typeId || isParentuuid(uuid);
		}
	private:
		bool isParentuuid(const common::uuid& uuid) const noexcept
		{
			for (const common::uuid& x : parents)
			{
				if (x == uuid)
					return true;
			}
			return false;
		}
	};

	template<class Ty>
	struct Trait
	{
		static common::uuid typeId;
	};


	struct IAsset
	{
		
		common::String editorName;
		common::String fromMod;
		common::uuid ID;
		ObjectSaveMode mode = ObjectSaveMode::ADD;
		ObjectType objectType;

		OneVersion objectVersion;


		inline IAsset() : IAsset(ObjectType::Undefined) {}
		inline IAsset(const ObjectType& type) : IAsset("", common::uuid(), OneVersion(0, 0, 0), type) {}
		inline IAsset(const common::String& fromMod, const common::uuid& ID, const OneVersion& version, const ObjectType& type = ObjectType::Undefined) : fromMod(fromMod), ID(ID), objectVersion(version), objectType(type) {}
		inline IAsset(const IAsset& copy) : fromMod(copy.fromMod), ID(copy.ID), mode(copy.mode), objectVersion(copy.objectVersion), objectType(copy.objectType) {}
	
		inline IAsset(const IAsset&& rvalreference) noexcept : fromMod(rvalreference.fromMod), ID(rvalreference.ID),
			mode(rvalreference.mode), objectVersion(rvalreference.objectVersion), objectType(rvalreference.objectType), editorName(rvalreference.editorName)
		{
		}
	
		inline IAsset& operator=(const IAsset& left) {
			editorName = left.editorName;
			fromMod = left.fromMod;
			ID = left.ID;
			mode = left.mode;
			objectVersion = left.objectVersion;
			objectType = left.objectType;
			return *this;
		}
	
		inline virtual common::String getName() const
		{
			return editorName;
		}

		inline virtual AssetId getModfile() const
		{
			return AssetId(fromMod, ID);
		}

		inline virtual TypeInfo getTrait() const = 0;

		virtual ~IAsset() = default;

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(editorName);
			ar(fromMod);
			ar(ID);
			ar(mode);
			ar(objectVersion);
			ar(objectType);
		}

		template<class Archive>
		void load(Archive& ar)
		{
			ar(editorName);
			ar(fromMod);
			ar(ID);
			ar(mode);
			ar(objectVersion);
			ar(objectType);
		}

	};
}
CEREAL_REGISTER_TYPE(of::asset::IAsset);
