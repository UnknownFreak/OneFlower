#ifndef WORLDTEMPLATE_HPP
#define WORLDTEMPLATE_HPP

#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/vector.hpp>

#include <file/archive/Requestable.hpp>
#include <file/FileId.hpp>

#include <vector>
#include <map>

#include <glm/vec3.hpp>
#include <object/component/ObjectStateActivator.hpp>

namespace of::resource
{
	struct ObjectInfo
	{
		// prefab not to be saved as it's only used to be cached temporary
		of::file::FileId prefab;
		of::file::FileId layer;

		// save
		of::common::uuid objectId;
		glm::vec3 location;
		bool isUnique;

		of::object::component::ObjectStateActivator activationInfo;

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(objectId);
			ar(location.x, location.y, location.z);
			ar(isUnique);
			ar(activationInfo);
		}

		template<class Archive>
		void load(Archive& ar)
		{
			ar(objectId);
			ar(location.x, location.y, location.z);
			ar(isUnique);
			ar(activationInfo);
		}
	};

	struct ObjectChunk : public of::file::archive::Requestable
	{
		of::file::FileId owningZone;
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
		std::vector<of::file::FileId> prefabs;
		std::vector<of::file::FileId> navMesh;
		std::vector<of::file::FileId> worldGeometry;
		std::vector<of::file::FileId> objectChunk;

		size_t getLoadingCount() const;
		void addTo(const WorldInstance& other, const bool& objectsOnly);

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::base_class<Requestable>(this));
			ar(prefabs);
			ar(navMesh);
			ar(worldGeometry);
			ar(objectChunk);
		}

		template<class Archive>
		void load(Archive& ar)
		{
			ar(cereal::base_class<Requestable>(this));
			ar(prefabs);
			ar(navMesh);
			ar(worldGeometry);
			ar(objectChunk);
		}

		// Inherited via IRequestable
		virtual of::file::archive::TypeInfo getTrait() const override;
	};

}

CEREAL_REGISTER_TYPE(of::resource::ObjectChunk);
CEREAL_REGISTER_POLYMORPHIC_RELATION(of::file::archive::Requestable, of::resource::ObjectChunk);
CEREAL_REGISTER_TYPE(of::resource::WorldInstance);
CEREAL_REGISTER_POLYMORPHIC_RELATION(of::file::archive::Requestable, of::resource::WorldInstance);

#endif 