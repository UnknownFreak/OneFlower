#pragma once

#include <Interfaces/IRequestable.hpp>
#include <vector>

#include <Helpers/Vector.hpp>
#include <Helpers/Vector3.hpp>
#include <Helpers/Enum/ColliderType.hpp>

namespace File::Asset::Resource::Template
{
	struct ColliderTemplate
	{
		Core::Vector3f pos;
		Core::Vector2f size;
		Enums::ColliderType type;

		bool isRoof = false;

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(pos);
			ar(size);
			ar(type);
			ar(isRoof);
		}
		template <class Archive>
		void load(Archive& ar)
		{
			ar(pos);
			ar(size);
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