#ifndef TileAtlas_HPP
#define TileAtlas_HPP

#include <cereal/types/map.hpp>

#include <Interfaces/IObject.hpp>
#include <Interfaces/IRequestable.hpp>
#include <Helpers/String.hpp>
#include <Helpers/Vector.hpp>
#include <map>

class TileAtlas : public Interfaces::IRequestable, public Interfaces::IObject
{
	std::unordered_map<Core::String, Core::Vector2f> atlas;
	Core::Vector2f def { 0.f, 0.f };
public:

	TileAtlas();
	TileAtlas(const TileAtlas& copy);
	TileAtlas& operator=(const TileAtlas& right);

	void addAtlasPos(const Core::String& tileType, const float& x, const float& y);
	void addAtlasPos(const Core::String& tileType, const Core::Vector2f& vec);
	void removeAtlasPos(const Core::String& tileType);

	Core::Vector2f& get(const Core::String& tileType);

	virtual Interfaces::TypeInfo getTrait() const;

	template <class Archive>
	void save(Archive& saver) const
	{
		saver(cereal::base_class<Interfaces::IObject>(this));
		//saver(cereal::base_class<IRequestable>(this));
		// cereal does not seem to like multi inheritence... save IRequestable using lazy cast
		//saver(cereal::base_class<Interfaces::IRequestable>(this));

		lazyloadsaveconst<Archive, Interfaces::IRequestable>(saver, *this);
		saver(atlas);
	};

	template <class Archive>
	void load(Archive& loader)
	{
		loader(cereal::base_class<Interfaces::IObject>(this));
		//loader(cereal::base_class<IRequestable>(this));
		//loader(cereal::base_class<Interfaces::IRequestable>(this));

		lazyloadsave<Archive, Interfaces::IRequestable>(loader, *this);
		loader(atlas);
	};
};


#endif 