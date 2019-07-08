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
		Core::uuid ID;
		Core::String fromMod;
		Core::Vector2 pos;
		Core::Vector2 oldPos;
		ObjectSaveMode mode = ObjectSaveMode::ADD;

		Prefab() {}
		Prefab(const Prefab& prefab): IObject(prefab), ID(prefab.ID), fromMod(prefab.fromMod), pos(prefab.pos), oldPos(prefab.oldPos), mode(prefab.mode) {}
		Prefab& operator=(const Prefab& pref)
		{
			name = pref.name;
			tag = pref.tag;
			ID = pref.ID;
			fromMod = pref.fromMod;
			pos = pref.pos;
			oldPos = pref.oldPos;
			mode = pref.mode;
			return *this;
		}

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
		std::map<std::pair<Core::String, Core::uuid>, Prefab> prefabs;
		std::vector<World::Grid::Tile> tiles;

		Chunk() {}
		Chunk(const Chunk& chunk) : IRequestable(chunk), pos(chunk.pos), prefabs(chunk.prefabs), tiles(chunk.tiles) {}
		Chunk& operator=(const Chunk& chunk)
		{
			fromMod = chunk.fromMod;
			ID = chunk.ID;
			mode = chunk.mode;
			objectVersion = chunk.objectVersion;
			pos = chunk.pos;
			prefabs = chunk.prefabs;
			tiles = chunk.tiles;
			return *this;
		}

		template<class A>
		void save(A& ar) const
		{
			ar(fromMod, ID, mode, objectVersion);
			ar(pos);

			const Core::String& openedMod = Engine::GetModule<Asset::AssetManager>().openedMod;
			std::map<std::pair<Core::String, Core::uuid>, Prefab> objectsToSave;

			for (std::map<std::pair<Core::String, Core::uuid>, Prefab>::const_iterator i = prefabs.begin(); i != prefabs.end(); i++)
			{
				if (i->second.mode == ObjectSaveMode::DEFAULT)
				{
					if (fromMod == openedMod)
					{
						Prefab prefab = i->second;
						prefab.oldPos = prefab.pos;
						objectsToSave.insert(std::pair<std::pair<Core::String, Core::uuid>, Prefab>(i->first, prefab));
					}
				}
				else if (i->second.mode == ObjectSaveMode::REMOVE)
					if (fromMod != openedMod)
						objectsToSave.insert(std::pair<std::pair<Core::String, Core::uuid>, Prefab>(i->first, i->second));
					else if (i->second.mode == ObjectSaveMode::EDIT)
					{
						Prefab prefab = i->second;
						if (fromMod == openedMod || openedMod == i->second.fromMod)
						{
							prefab.mode = ObjectSaveMode::DEFAULT;
							prefab.oldPos = prefab.pos;
						}
						objectsToSave.insert(std::pair<std::pair<Core::String, Core::uuid>, Prefab>(i->first, prefab));
					}
					else if (i->second.mode == ObjectSaveMode::ADD)
					{
						Prefab prefab = i->second;
						if (fromMod == openedMod)
						{
							prefab.mode = ObjectSaveMode::DEFAULT;
							prefab.oldPos = prefab.pos;
						}
						objectsToSave.insert(std::pair<std::pair<Core::String, Core::uuid>, Prefab>(i->first, prefab));
					}
			}
			ar(objectsToSave.size());
			for (std::map<std::pair<Core::String, Core::uuid>, Prefab>::iterator i = objectsToSave.begin(); i != objectsToSave.end(); i++)
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
			Core::uuid _ID;
			size_t size;
			Prefab prefab;
			ar(fromMod, ID, mode, objectVersion);
			ar(pos);
			ar(size);
			for (size_t i = 0; i < size; i++)
			{
				ar(name);
				ar(_ID);
				ar(prefab);
				if (prefab.mode == ObjectSaveMode::REMOVE)
					if (prefabs.find(std::pair<Core::String, Core::uuid>(name, _ID)) != prefabs.end())
						prefabs.erase(prefabs.find(std::pair<Core::String, Core::uuid>(name, _ID)));
					else if (prefab.mode == ObjectSaveMode::EDIT)
						if (prefabs.find(std::pair<Core::String, Core::uuid>(name, _ID)) != prefabs.end())
							prefabs[std::pair<Core::String, Core::uuid>(name, _ID)].pos = prefab.pos;
						else
							prefabs.insert(std::pair<std::pair<Core::String, Core::uuid>, Prefab>(std::pair<Core::String, Core::uuid>(name, _ID), prefab));
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
		std::vector<std::pair<Core::String, Core::uuid>> prefabs;

		Zone() {}
		Zone(const Zone& zone) : IRequestable(zone), chunkCountX(zone.chunkCountX), chunkCountY(zone.chunkCountY),
			name(zone.name), background(zone.background), loadingScreen(zone.loadingScreen), loadingScreenMessage(zone.loadingScreenMessage),
			chunks(zone.chunks), prefabs(zone.prefabs) {}

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