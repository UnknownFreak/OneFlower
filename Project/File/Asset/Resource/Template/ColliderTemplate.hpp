#pragma once

#include <Interfaces/IRequestable.hpp>
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

	struct ColliderChunk : public Interfaces::IRequestable {
		std::vector<ColliderTemplate> colliderInfo;
		int layer;
		Core::String group;
		template<class Archive>
		void save(Archive& ar) const
		{
			ar(colliderInfo);
			ar(layer);
			ar(group);
		}
		template <class Archive>
		void load(Archive& ar)
		{
			ar(colliderInfo);
			ar(layer);
			ar(group);
		}

		// Inherited via IRequestable
		virtual Interfaces::TypeInfo getTrait() const override;
	};
}