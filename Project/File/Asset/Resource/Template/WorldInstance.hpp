#ifndef WORLDTEMPLATE_HPP
#define WORLDTEMPLATE_HPP

#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/vector.hpp>

#include <file/archive/Requestable.hpp>
#include <file/FileId.hpp>

#include <Helpers/Enum/ColliderType.hpp>
#include <Helpers/Enum/TileTypes.hpp>
#include <vector>
#include <map>

#include <glm/vec3.hpp>
#include <Object/ObjectStateActivator.hpp>

namespace File::Asset::Resource::Template
{
	struct ObjectInfo
	{
		of::file::FileId prefab;
		of::common::uuid objectId;
		glm::vec3 location;

		Component::ObjectStateActivator activationInfo;

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(objectId);
			ar(location.x, location.y, location.z);
			ar(activationInfo);
		}

		template<class Archive>
		void load(Archive& ar)
		{
			ar(objectId);
			ar(location.x, location.y, location.z);
			ar(activationInfo);
		}
	};

	struct ObjectChunk : public of::file::archive::Requestable
	{
		std::map<of::file::FileId, std::vector<ObjectInfo>> objectLocations;

		// Inherited via IRequestable
		virtual of::file::archive::TypeInfo getTrait() const override;

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::base_class<Requestable>(this));
			ar(objectLocations);
		}

		template<class Archive>
		void load(Archive& ar)
		{
			ar(cereal::base_class<Requestable>(this));
			ar(objectLocations);
		}
	};


	struct WorldInstance : public of::file::archive::Requestable
	{
		of::common::String name;
		std::vector<of::file::FileId> tileAtlases;
		std::vector<of::file::FileId> prefabs;
		std::vector<of::file::FileId> tileInfo;
		std::vector<of::file::FileId> colliderInfo;
		std::vector<of::file::FileId> objectChunk;

		size_t getLoadingCount() const;

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::base_class<Requestable>(this));
			ar(tileAtlases);
			ar(prefabs);
			ar(tileInfo);
			ar(colliderInfo);
			ar(objectChunk);
		}

		template<class Archive>
		void load(Archive& ar)
		{
			ar(cereal::base_class<Requestable>(this));
			ar(tileAtlases);
			ar(prefabs);
			ar(tileInfo);
			ar(colliderInfo);
			ar(objectChunk);
		}

		// Inherited via IRequestable
		virtual of::file::archive::TypeInfo getTrait() const override;
	};

}

CEREAL_REGISTER_TYPE(File::Asset::Resource::Template::ObjectChunk);
CEREAL_REGISTER_POLYMORPHIC_RELATION(of::file::archive::Requestable, File::Asset::Resource::Template::ObjectChunk);
CEREAL_REGISTER_TYPE(File::Asset::Resource::Template::WorldInstance);
CEREAL_REGISTER_POLYMORPHIC_RELATION(of::file::archive::Requestable, File::Asset::Resource::Template::WorldInstance);

#endif 