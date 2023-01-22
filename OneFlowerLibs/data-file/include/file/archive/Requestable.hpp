#ifndef IREQUESTABLE_HPP
#define IREQUESTABLE_HPP

#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>

#include <utils/common/uuid.hpp>
#include <utils/common/String.hpp>
#include <utils/common/Version.hpp>
#include <file/FileId.hpp>

#include <file/ObjectType.hpp>

#include <file/archive/ObjectSaveMode.hpp>


namespace of::file::archive
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


	struct Requestable
	{
		
		common::String fromMod;
		common::uuid ID;
		ObjectSaveMode mode = ObjectSaveMode::ADD;
		ObjectType objectType;

		OneVersion objectVersion;


		inline Requestable() : Requestable(ObjectType::Undefined) {}
		inline Requestable(const ObjectType& type) : Requestable("", common::uuid(), OneVersion(0, 0, 0), type) {}
		inline Requestable(const common::String& fromMod, const common::uuid& ID, const OneVersion& version, const ObjectType& type = ObjectType::Undefined) : fromMod(fromMod), ID(ID), objectVersion(version), objectType(type) {}
		inline Requestable(const Requestable& copy) : fromMod(copy.fromMod), ID(copy.ID), mode(copy.mode), objectVersion(copy.objectVersion), objectType(copy.objectType) {}
	
		inline Requestable(const Requestable&& rvalreference) noexcept : fromMod(rvalreference.fromMod), ID(rvalreference.ID),
			mode(rvalreference.mode), objectVersion(rvalreference.objectVersion), objectType(rvalreference.objectType) {}
	
		inline Requestable& operator=(const Requestable& left) {
			fromMod = left.fromMod;
			ID = left.ID;
			mode = left.mode;
			objectVersion = left.objectVersion;
			objectType = left.objectType;
			return *this;
		}
	
		inline virtual common::String getName() const
		{
			return "";
		}

		inline virtual common::String getValue() const
		{
			return "";
		}

		inline virtual FileId getModfile() const
		{
			return FileId(fromMod, ID);
		}

		inline virtual TypeInfo getTrait() const = 0;

		virtual ~Requestable() = default;

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
CEREAL_REGISTER_TYPE(of::file::archive::Requestable);


#endif