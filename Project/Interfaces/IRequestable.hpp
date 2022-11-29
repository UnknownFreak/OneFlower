#ifndef IREQUESTABLE_HPP
#define IREQUESTABLE_HPP
#include <utils/common/uuid.hpp>
#include <utils/common/string.hpp>
#include <utils/common/version.hpp>
#include <File/Mod/ModFileUUIDHelper.hpp>
#include <Helpers/Enum/ObjectSaveMode.hpp>
#include <Helpers/Enum/ObjectType.hpp>

namespace Interfaces
{
	struct TypeInfo
	{
		of::common::uuid typeId;
		std::vector<of::common::uuid> parents;

		bool hasTypeId(const of::common::uuid& uuid) const noexcept
		{
			return uuid == typeId || isParentuuid(uuid);
		}
	private:
		bool isParentuuid(const of::common::uuid& uuid) const noexcept
		{
			for (const of::common::uuid& x : parents)
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
		static of::common::uuid typeId;
	};


	struct IRequestable
	{
		
		of::common::String fromMod;
		of::common::uuid ID;
		Enums::ObjectSaveMode mode = Enums::ObjectSaveMode::ADD;
		Enums::ObjectType objectType;

		OneVersion objectVersion;


		inline IRequestable() : IRequestable(Enums::ObjectType::Undefined) {}
		inline IRequestable(const Enums::ObjectType& type) : IRequestable("", of::common::uuid(), OneVersion(0, 0, 0), type) {}
		inline IRequestable(const of::common::String& fromMod, const of::common::uuid& ID, const OneVersion& version, const Enums::ObjectType& type = Enums::ObjectType::Undefined) : fromMod(fromMod), ID(ID), objectVersion(version), objectType(type) {}
		inline IRequestable(const IRequestable& copy) : fromMod(copy.fromMod), ID(copy.ID), mode(copy.mode), objectVersion(copy.objectVersion), objectType(copy.objectType) {}
	
		inline IRequestable(const IRequestable&& rvalreference) noexcept : fromMod(rvalreference.fromMod), ID(rvalreference.ID),
			mode(rvalreference.mode), objectVersion(rvalreference.objectVersion), objectType(rvalreference.objectType) {}
	
		inline IRequestable& operator=(const IRequestable& left) {
			fromMod = left.fromMod;
			ID = left.ID;
			mode = left.mode;
			objectVersion = left.objectVersion;
			objectType = left.objectType;
			return *this;
		}
	
		inline virtual of::common::String getName() const
		{
			return "";
		}

		inline virtual of::common::String getValue() const
		{
			return "";
		}

		inline virtual File::Mod::ModFileUUIDHelper getModfile() const
		{
			return File::Mod::ModFileUUIDHelper(fromMod, ID);
		}

		inline virtual void render()
		{

		}

		inline virtual TypeInfo getTrait() const = 0;

		virtual ~IRequestable() = default;

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(fromMod);
			ar(ID);
			ar(mode);
			ar(objectVersion);
			ar(objectType);
		}

		template<class Archive>
		void load(Archive& ar)
		{
			ar(fromMod);
			ar(ID);
			ar(mode);
			ar(objectVersion);
			ar(objectType);
		}

	};
}


#endif