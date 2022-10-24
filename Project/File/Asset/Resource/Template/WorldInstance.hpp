#ifndef WORLDTEMPLATE_HPP
#define WORLDTEMPLATE_HPP

#include <cereal/cereal.hpp>

#include <Interfaces/IRequestable.hpp>

#include <Helpers/Enum/ColliderType.hpp>
#include <Helpers/Enum/TileTypes.hpp>
#include <File/Mod/ModFileUUIDHelper.hpp>
#include <vector>
#include <map>

#include <glm/vec3.hpp>
#include <Object/ObjectStateActivator.hpp>

namespace File::Asset::Resource::Template
{
	struct ObjectInfo
	{
		File::Mod::ModFileUUIDHelper prefab;
		Core::uuid objectId;
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

	struct ObjectChunk : public Interfaces::IRequestable
	{
		std::map<File::Mod::ModFileUUIDHelper, std::vector<ObjectInfo>> objectLocations;

		// Inherited via IRequestable
		virtual Interfaces::TypeInfo getTrait() const override;

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::base_class<IRequestable>(this));
			ar(objectLocations);
		}

		template<class Archive>
		void load(Archive& ar)
		{
			ar(cereal::base_class<IRequestable>(this));
			ar(objectLocations);
		}
	};


	struct WorldInstance : public Interfaces::IRequestable
	{
		Core::String name;
		std::vector<File::Mod::ModFileUUIDHelper> tileAtlases;
		std::vector<File::Mod::ModFileUUIDHelper> prefabs;
		std::vector<File::Mod::ModFileUUIDHelper> tileInfo;
		std::vector<File::Mod::ModFileUUIDHelper> colliderInfo;
		std::vector<File::Mod::ModFileUUIDHelper> objectChunk;

		size_t getLoadingCount() const;

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::base_class<IRequestable>(this));
			ar(tileAtlases);
			ar(prefabs);
			ar(tileInfo);
			ar(colliderInfo);
			ar(objectChunk);
		}

		template<class Archive>
		void load(Archive& ar)
		{
			ar(cereal::base_class<IRequestable>(this));
			ar(tileAtlases);
			ar(prefabs);
			ar(tileInfo);
			ar(colliderInfo);
			ar(objectChunk);
		}

		// Inherited via IRequestable
		virtual Interfaces::TypeInfo getTrait() const override;
	};
}
#endif 