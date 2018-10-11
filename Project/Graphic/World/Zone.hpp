#ifndef ZONE_HPP
#define ZONE_HPP

#include <vector>
#include <cereal/types/vector.hpp>

#include "Chunk.hpp"
#include <Asset/Database/DatabaseObjects.hpp>
#include <Asset/IRequestable.hpp>
#include <Asset/Prefab.hpp>
#include <Core/String.hpp>
#include <Physics\QuadTree.hpp>
#include <Graphic\BackgroundSprite.hpp>

class WorldManager;
class GameObject;

class Zone : public sf::Drawable, public IRequestable
{
	friend class WorldManager;

private:

	size_t chunk_count_x = 0;
	size_t chunk_count_y = 0;

#ifdef _UNITTESTS_
public:
#endif
	std::vector<Chunk> chunkList;

#ifdef _DEBUG
public:
#endif
	BackgroundSprite background;
	Core::String name;

	BackgroundSprite loadScreen;
	Core::String loadingScreenMessage = "";

	QuadTree chunks;

public:

	std::vector<std::pair<std::pair<Core::String, size_t>, GameObject*>> objects;
	BackgroundSprite* getBackground();

	BackgroundSprite* getLoadingScreen();
	const Core::String& getLoadingScreenMessage() const;

	Core::String& getName();

	void update();

	Zone();
	Zone(const size_t chunk_count_x, const size_t chunk_count_y);
	Zone(Zone &zone);
	~Zone();
	Zone& operator=(const Zone &z);

#ifdef _DEBUG
	void setBackground(Core::String name);
#endif

public:

	template<class Archive>
	void save(Archive &ar) const
	{
		ar(cereal::base_class<IRequestable>(this));
		ar(prefabs);
		//ar(name);
		//ar(background);
		//ar(loadScreen);
		//ar(loadingScreenMessage);
		//ar(objects.size());
		//for (std::vector<std::pair<std::pair<Core::String, size_t>, GameObject*>>::const_iterator i = objects.begin(); i != objects.end(); i++)
		//{
		//	ar(i->first.first);
		//	ar(i->first.second);
		//	ar(*i->second);
		//}
	}
	template<class Archive>
	void load(Archive &ar)
	{
		//size_t size = 0;
		//BackgroundSprite t;
		ar(cereal::base_class<IRequestable>(this));
		ar(prefabs);
		//ar(name);
		//ar(t);
		//background = t;
		//ar(t);
		//loadScreen = t;
		//ar(loadingScreenMessage);
		//ar(size);
		//for (size_t i = 0; i < size; i++)
		//{
		//	Core::String name;
		//	size_t ID;
		//	GameObject* obj = new GameObject();
		//	ar(name);
		//	ar(ID);
		//	ar(*obj);
		//	objects.push_back(std::pair<std::pair<Core::String, size_t>, GameObject*>(std::pair<Core::String, size_t>(name, ID), obj));
		//}
	}

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
};

#endif ZONE_HPP