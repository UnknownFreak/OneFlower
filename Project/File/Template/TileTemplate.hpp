#ifndef TileTemplate_HPP
#define TileTemplate_HPP

#include <cereal/access.hpp>
#include <cereal/types/vector.hpp>

#include <Helpers/uuid.hpp>
#include <Helpers/Vector.hpp>
#include <Helpers/Vector3.hpp>
#include <Helpers/String.hpp>

#include <Helpers/Enum/TileTypes.hpp>

#include <File/ModFileUUIDHelper.hpp>

#include <Interfaces/IRequestable.hpp>
#include <vector>

struct TransparencyInfo
{
	bool set = false;
	Core::Vector3f pos { 0.f, 0.f ,0.f };
	Core::Vector2f size { 0.f, 0.f };

	template<class Archive>
	void save(Archive& ar) const
	{
		ar(set);
		ar(pos);
		ar(size);
	}

	template<class Archive>
	void load(Archive& ar)
	{
		ar(set);
		ar(pos);
		ar(size);
	}
};

struct TileTemplate
{
	Core::Vector3f pos;
	File::Mod::ModFileUUIDHelper atlas;
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
		ar(pos);
		//ar(atlas);
		ar(textureCoors);
		ar(type);
		ar(hasShadow);
	}

	template<class Archive>
	void load(Archive& ar)
	{
		ar(m_uuid);
		ar(pos);
		//ar(atlas);
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

#endif