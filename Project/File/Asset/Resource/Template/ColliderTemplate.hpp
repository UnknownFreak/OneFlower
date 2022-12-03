#pragma once

#include <file/archive/Requestable.hpp>
#include <vector>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <Helpers/Enum/ColliderType.hpp>

namespace File::Asset::Resource::Template
{
	struct ColliderTemplate
	{
		glm::vec3 pos;
		glm::vec2 size;
		Enums::ColliderType type;

		bool isRoof = false;

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(pos.x, pos.y, pos.z);
			ar(size.x, size.y);
			ar(type);
			ar(isRoof);
		}
		template <class Archive>
		void load(Archive& ar)
		{
			ar(pos.x, pos.y, pos.z);
			ar(size.x, size.y);
			ar(type);
			ar(isRoof);
		}
	};

	struct ColliderChunk : public of::file::archive::Requestable {
		std::vector<ColliderTemplate> colliderInfo;
		int layer;
		of::common::String group;
		template<class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::base_class<Requestable>(this));
			ar(colliderInfo);
			ar(layer);
			ar(group);
		}
		template <class Archive>
		void load(Archive& ar)
		{
			ar(cereal::base_class<Requestable>(this));
			ar(colliderInfo);
			ar(layer);
			ar(group);
		}

		// Inherited via IRequestable
		virtual of::file::archive::TypeInfo getTrait() const override;
	};
}
CEREAL_REGISTER_TYPE(File::Asset::Resource::Template::ColliderChunk);
CEREAL_REGISTER_POLYMORPHIC_RELATION(of::file::archive::Requestable, File::Asset::Resource::Template::ColliderChunk);
