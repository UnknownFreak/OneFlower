#ifndef WORLDTEMPLATE_HPP
#define WORLDTEMPLATE_HPP

#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/vector.hpp>

#include <asset/iAsset.hpp>
#include <asset/assetId.hpp>

#include <vector>
#include <map>

#include <glm/vec3.hpp>
#include <component/objectStateActivator.hpp>

namespace of::resource
{
	struct ObjectInfo
	{
		// prefab not to be saved as it's only used to be cached temporary
		of::asset::AssetId prefab;
		of::asset::AssetId layer;

		// save
		of::common::uuid objectId;
		glm::vec3 location;
		bool isUnique;

		of::component::ObjectStateActivator activationInfo;

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

	struct ObjectChunk : public of::asset::IAsset
	{
		of::asset::AssetId owningZone;
		std::map<of::asset::AssetId, std::vector<ObjectInfo>> objectLocations;

		// Inherited via IRequestable
		virtual of::asset::TypeInfo getTrait() const override;

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::base_class<IAsset>(this));
			ar(objectLocations);
		}

		template<class Archive>
		void load(Archive& ar)
		{
			ar(cereal::base_class<IAsset>(this));
			ar(objectLocations);
		}
	};


	struct WorldInstance : public of::asset::IAsset
	{
		of::common::String name;
		of::common::String skybox;
		std::vector<of::asset::AssetId> prefabs;
		std::vector<of::asset::AssetId> navMesh;
		std::vector<of::asset::AssetId> worldGeometry;
		std::vector<of::asset::AssetId> objectChunk;
		std::vector<of::asset::AssetId> cutScenes;

		size_t getLoadingCount() const;
		void addTo(const WorldInstance& other, const bool& objectsOnly);

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::base_class<IAsset>(this));
			ar(name);
			ar(skybox);
			ar(prefabs);
			ar(navMesh);
			ar(worldGeometry);
			ar(objectChunk);
			ar(cutScenes);
		}

		template<class Archive>
		void load(Archive& ar)
		{
			ar(cereal::base_class<IAsset>(this));
			ar(name);
			ar(skybox);
			ar(prefabs);
			ar(navMesh);
			ar(worldGeometry);
			ar(objectChunk);
			ar(cutScenes);
		}

		// Inherited via IRequestable
		virtual of::asset::TypeInfo getTrait() const override;
	};

}

CEREAL_REGISTER_TYPE(of::resource::ObjectChunk);
CEREAL_REGISTER_POLYMORPHIC_RELATION(of::asset::IAsset, of::resource::ObjectChunk);
CEREAL_REGISTER_TYPE(of::resource::WorldInstance);
CEREAL_REGISTER_POLYMORPHIC_RELATION(of::asset::IAsset, of::resource::WorldInstance);

#endif 