#ifndef TileTemplate_HPP
#define TileTemplate_HPP

#include <cereal/access.hpp>
#include <cereal/types/vector.hpp>

#include <Helpers/uuid.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <Helpers/String.hpp>

#include <Helpers/Enum/TileTypes.hpp>

#include <File/Mod/ModFileUUIDHelper.hpp>

#include <Interfaces/IRequestable.hpp>
#include <vector>

namespace File::Asset::Resource::Template
{

	struct TransparencyInfo
	{
		bool set = false;
		glm::vec3 pos{ 0.f, 0.f ,0.f };
		glm::vec2 size{ 0.f, 0.f };

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(set);
			ar(pos.x, pos.y, pos.z);
			ar(size.x, size.y);
		}

		template<class Archive>
		void load(Archive& ar)
		{
			ar(set);
			ar(pos.x, pos.y, pos.z);
			ar(size.x, size.y);
		}
	};

	struct TileTemplate
	{
		glm::vec3 pos;
		Core::String textureCoors;
		Enums::TileTypes type;
		bool hasShadow;
		Core::uuid m_uuid;

		bool operator==(const TileTemplate& other)
		{
			return m_uuid == other.m_uuid;
		}

		bool operator <(const TileTemplate& other)
		{
			return m_uuid < other.m_uuid;
		}

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(m_uuid);
			ar(pos.x, pos.y, pos.z);
			ar(textureCoors);
			ar(type);
			ar(hasShadow);
		}

		template<class Archive>
		void load(Archive& ar)
		{
			ar(m_uuid);
			ar(pos.x, pos.y, pos.z);
			ar(textureCoors);
			ar(type);
			ar(hasShadow);
		}
	};


	struct TileChunk : public Interfaces::IRequestable
	{
		std::vector<TileTemplate> tileInfo;
		TransparencyInfo chunkTransparency;
		int layer;
		Core::String group;
		File::Mod::ModFileUUIDHelper atlas;

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::base_class<IRequestable>(this));
			ar(tileInfo);
			ar(chunkTransparency);
			ar(layer);
			ar(group);
			ar(atlas);
		}
		template <class Archive>
		void load(Archive& ar)
		{
			ar(cereal::base_class<IRequestable>(this));
			ar(tileInfo);
			ar(chunkTransparency);
			ar(layer);
			ar(group);
			ar(atlas);
		}

		// Inherited via IRequestable
		virtual Interfaces::TypeInfo getTrait() const override;
	};
}
#endif