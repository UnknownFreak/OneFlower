#ifndef DATABASEOBJECTS_HPP
#define DATABASEOBJECTS_HPP

#include <map>
#include <vector>
#include <cereal/types/vector.hpp>
#include <cereal/types/utility.hpp>

#include "../ObjectSaveMode.hpp"
#include "../IRequestable.hpp"
#include "../IObject.hpp"

#include <Core/String.hpp>
#include <Core/Vector.h>

#include <Graphic/World/GridTile.h>

namespace Database
{
	struct Prefab : IObject
	{
		size_t ID;
		Core::String fromMod;
		Core::Vector2 pos;
		Core::Vector2 oldPos;
		ObjectSaveMode mode = ObjectSaveMode::ADD;

		template <class A>
		void save(A& ar) const
		{
			ar(ID);
			ar(fromMod);
			ar(pos);
			ar(oldPos);
			ar(mode);
		}
		
		template <class A>
		void load(A& ar)
		{
			ar(ID);
			ar(fromMod);
			ar(pos);
			ar(oldPos);
			ar(mode);
		}
	};

	struct Chunk : public IRequestable
	{
		Core::Vector2 pos;
		std::map<std::pair<Core::String, size_t>, Prefab> prefabs;
		std::vector<World::Grid::Tile> tiles;

		template<class A>
		void save(A& ar) const
		{
			cereal::base_class<IRequestable>(this);
			ar(pos);

			Engine::Dispose();

			const Core::String& openedMod = Engine::GetModule<Asset::AssetManager>().openedMod;
			std::map<std::pair<Core::String, size_t>, Prefab> objectsToSave;

			for (std::map<std::pair<Core::String, size_t>, Prefab>::const_iterator i = prefabs.begin(); i != prefabs.end(); i++)
			{
				if (i->second.mode == ObjectSaveMode::DEFAULT)
				{
					if (fromMod == openedMod)
					{
						Prefab prefab = i->second;
						prefab.oldPos = prefab.pos;
						objectsToSave.insert(std::pair<std::pair<Core::String, size_t>, Prefab>(i->first, prefab));
					}
				}
				else if (i->second.mode == ObjectSaveMode::REMOVE)
					if (fromMod != openedMod)
						objectsToSave.insert(std::pair<std::pair<Core::String, size_t>, Prefab>(i->first, i->second));
					else if (i->second.mode == ObjectSaveMode::EDIT)
					{
						Prefab prefab = i->second;
						if (fromMod == openedMod || openedMod == i->second.fromMod)
						{
							prefab.mode = ObjectSaveMode::DEFAULT;
							prefab.oldPos = prefab.pos;
						}
						objectsToSave.insert(std::pair<std::pair<Core::String, size_t>, Prefab>(i->first, prefab));
					}
					else if (i->second.mode == ObjectSaveMode::ADD)
					{
						Prefab prefab = i->second;
						if (fromMod == openedMod)
						{
							prefab.mode = ObjectSaveMode::DEFAULT;
							prefab.oldPos = prefab.pos;
						}
						objectsToSave.insert(std::pair<std::pair<Core::String, size_t>, Prefab>(i->first, prefab));
					}
			}
			ar(objectsToSave.size());
			for (std::map<std::pair<Core::String, size_t>, Prefab>::iterator i = objectsToSave.begin(); i != objectsToSave.end(); i++)
			{
				ar(i->first.first);
				ar(i->first.second);
				ar(i->second);
			}
			ar(tiles);
		}

		template <class A>
		void load(A& ar)
		{
			Core::String name;
			size_t ID;
			size_t size;
			Prefab prefab;
			cereal::base_class<IRequestable>(this);
			ar(pos);
			ar(size);
			for (size_t i = 0; i < size; i++)
			{
				ar(name);
				ar(ID);
				ar(prefab);
				if (prefab.mode == ObjectSaveMode::REMOVE)
					if (prefabs.find(std::pair<Core::String, size_t>(name, ID)) != prefabs.end())
						prefabs.erase(prefabs.find(std::pair<Core::String, size_t>(name, ID)));
					else if (prefab.mode == ObjectSaveMode::EDIT)
						if (prefabs.find(std::pair<Core::String, size_t>(name, ID)) != prefabs.end())
							prefabs[std::pair<Core::String, size_t>(name, ID)].pos = prefab.pos;
						else
							prefabs.insert(std::pair<std::pair<Core::String, size_t>, Prefab>(std::pair<Core::String, size_t>(name, ID), prefab));
			}
			ar(tiles);
		}
	};
	struct Zone : public IRequestable
	{
		size_t chunkCountX;
		size_t chunkCountY;
		Core::String name;
		Core::String background;
		Core::String loadingScreen;
		Core::String loadingScreenMessage;

		std::vector<Chunk> chunks;
		std::vector<std::pair<Core::String, size_t>> prefabs;

		template <class A>
		void save(A& ar) const
		{
			ar(chunkCountX, chunkCountY);
			ar(name);
			ar(background);
			ar(loadingScreen);
			ar(loadingScreenMessage);
			ar(chunks);
			ar(prefabs);
		}

		template <class A>
		void load(A& ar)
		{
			ar(chunkCountX, chunkCountY);
			ar(name);
			ar(background);
			ar(loadingScreen);
			ar(loadingScreenMessage);
			ar(chunks);
			ar(prefabs);
		}
	};
}
#endif