#include "WorldManager.hpp"
#include "Zone.hpp"

#include <Asset\AssetManagerCore.hpp>
#include <Asset/Prefab.hpp>

#include <Core/Component/GameObject.h>
#include <Core/Component/TransformComponent.hpp>

#include <Graphic\Gfx.h>

void WorldManager::startLoad()
{
	_isLoading = true;
	currentZone = nullptr;
	loadState = CHECK_IF_LOADED;
}

void WorldManager::loadSome()
{
	switch (loadState)
	{
	case NOT_SET:
		break;

	case CHECK_IF_LOADED:
		checkIfLoaded();
		break;

	case SWAP_WITH_LOADED:
		swapWithLoaded();
		break;
	case LOAD_FROM_FILE:
		loadFromFile();
		break;

	case LOAD_OBJECTS:
		loadObjects();
		break;

	case INITIALIZE_CHUNKS:
		initializeChunks();
		break;

	case BUILD_CHUNKS:
		buildChunks();
		break;

	case PLACE_TILES:
		placeTiles();
		break;

	case POPULATE_CHUNKS:
		populateChunks();
		break;

	case UNLOAD_OBJECTS:
		unloadObjects();
		break;

	case ERR_LOADING:
		exit(999);
		break;
	case DONE:
		if (refZoneToLoad)
		{
			Engine::GetModule<Asset::AssetManager>().getZoneRequester().requestRemoval(zoneToLoadID.first, zoneToLoadID.second);
			refZoneToLoad = nullptr;
		}
		_isLoading = false;
		break;
	}
}
#ifdef _EDITOR_
void WorldManager::unload()
{
	//switch (loadState)
	//{
	//case NOT_SET:
	//	break;
	//case REQUEST_DBZONE:
	//	requestZoneToLoad();
	//	break;
	//case UNREQUEST_DBZONE:
	//	unrequestZoneToLoad();
	//	break;
	//case PREPARE_LOAD:
	//	prepareLoad();
	//	break;
	//case UNLOAD_OBJECTS:
	//	unloadObjects();
	//	break;
	//case RELOAD_OBJECTS:
	//	isLoading = false;
	//	currentZone = nullptr;
	//	for each (auto var in worldmap)
	//		delete var.second;
	//	worldmap.clear();
	//	return;
	//}
}
#endif

void WorldManager::checkIfLoaded()
{
	if (worldmap.find(zoneToLoadID) != worldmap.end())
		loadState = SWAP_WITH_LOADED;
	else
		loadState = LOAD_FROM_FILE;
}
void WorldManager::swapWithLoaded()
{
	Engine::GetModule<Gfx>().zone = &worldmap[zoneToLoadID];
	loadState = DONE;
}

void WorldManager::loadFromFile()
{
	Requestor<Database::Zone>& req = Engine::GetModule<Asset::AssetManager>().getZoneRequester();
	refZoneToLoad = &req.request(zoneToLoadID.first, zoneToLoadID.second);
	{
		databaseChunkIterator = refZoneToLoad->chunks.begin();

		worldmap[zoneToLoadID].chunk_count_x = refZoneToLoad->chunkCountX;
		worldmap[zoneToLoadID].chunk_count_y = refZoneToLoad->chunkCountY;
		worldmap[zoneToLoadID].chunkList.clear();
	}
	loadState = INITIALIZE_CHUNKS;
}

void WorldManager::loadObjects()
{
	if (prefabIdIterator == refZoneToLoad->prefabs.end())
	{
		loadState = POPULATE_CHUNKS;
		zoneChunkIterator = worldmap[zoneToLoadID].chunkList.begin();
		return;
	}
	Requestor<Asset::Prefab>& req = Engine::GetModule<Asset::AssetManager>().getPrefabRequester();
	Asset::Prefab prefab = req.request(prefabIdIterator->first, prefabIdIterator->second);
	{
		loadedPrefabs[{prefab.fromMod, prefab.ID}] = prefab;
	}
	req.requestRemoval(prefabIdIterator->first, prefabIdIterator->second);
	prefabIdIterator++;
}

void WorldManager::initializeChunks()
{
	Zone& zone = worldmap[zoneToLoadID];
	if (databaseChunkIterator == refZoneToLoad->chunks.end())
	{
		databaseChunkIterator = refZoneToLoad->chunks.begin();
		zoneChunkIterator = worldmap[zoneToLoadID].chunkList.begin();
		current_chunk = 0;
		loadState = BUILD_CHUNKS;
		return;
	}

	zone.chunkList.push_back(Chunk(databaseChunkIterator->pos));
	zone.chunks.insert(&zone.chunkList.rbegin().operator*());
	databaseChunkIterator++;
}


void WorldManager::placeTiles()
{

	if (zoneChunkIterator == worldmap[zoneToLoadID].chunkList.end())
	{
		loadState = LOAD_OBJECTS;
		prefabIdIterator = refZoneToLoad->prefabs.begin();
		databaseChunkIterator = refZoneToLoad->chunks.begin();
		return;
	}

	for (World::Grid::Tile tile : databaseChunkIterator->tiles)
	{
#ifndef _EDITOR_
		if (tile.type != tile.Blank) 
#endif
		{
			zoneChunkIterator->_tiles.push_back(tile);
			if (tile.type != tile.NoCollide)
				zoneChunkIterator->tiles.insert(&zoneChunkIterator->_tiles.rbegin().operator*());
		}
		databaseChunkIterator++;
		zoneChunkIterator++;
	}
}


void WorldManager::buildChunks()
{
	size_t rows = worldmap[zoneToLoadID].chunk_count_x;
	size_t size = worldmap[zoneToLoadID].chunkList.size();
	if (zoneChunkIterator == worldmap[zoneToLoadID].chunkList.end())
	{
		loadState = PLACE_TILES;
		zoneChunkIterator = worldmap[zoneToLoadID].chunkList.begin();
		databaseChunkIterator = refZoneToLoad->chunks.begin();
		return;
	}

	if (current_chunk < rows)
	{
		if (current_chunk != 0)
			zoneChunkIterator->setNeighbourChunk((zoneChunkIterator - 1).operator*(), Chunk::Neighbour::LEFT);
		if (current_chunk < rows - 1)
			zoneChunkIterator->setNeighbourChunk((zoneChunkIterator + 1).operator*(), Chunk::Neighbour::RIGHT);
		zoneChunkIterator->setNeighbourChunk((zoneChunkIterator + rows).operator*(), Chunk::Neighbour::BOTTOM);
	}
	else if (current_chunk > size - rows - 1)
	{
		if (current_chunk != size - rows)
			zoneChunkIterator->setNeighbourChunk((zoneChunkIterator - 1).operator*(), Chunk::Neighbour::LEFT);
		if (current_chunk < size - 1)
			zoneChunkIterator->setNeighbourChunk((zoneChunkIterator + 1).operator*(), Chunk::Neighbour::RIGHT);
		zoneChunkIterator->setNeighbourChunk((zoneChunkIterator - rows).operator*(), Chunk::Neighbour::TOP);
	}
	else
	{
		if (current_chunk % rows != 0)
			zoneChunkIterator->setNeighbourChunk((zoneChunkIterator - 1).operator*(), Chunk::Neighbour::LEFT);
		if (current_chunk % rows != rows - 1)
			zoneChunkIterator->setNeighbourChunk((zoneChunkIterator + 1).operator*(), Chunk::Neighbour::RIGHT);
		zoneChunkIterator->setNeighbourChunk((zoneChunkIterator + rows).operator*(), Chunk::Neighbour::BOTTOM);
		zoneChunkIterator->setNeighbourChunk((zoneChunkIterator - rows).operator*(), Chunk::Neighbour::TOP);
	}
	current_chunk++;
	zoneChunkIterator++;
}

void WorldManager::populateChunks()
{
	if (zoneChunkIterator == worldmap[zoneToLoadID].chunkList.end())
	{
		loadState = UNLOAD_OBJECTS;
		return;
	}

	for (std::pair<const std::pair<Core::String, size_t>, Database::Prefab>& kvp : databaseChunkIterator->prefabs)
		zoneChunkIterator->addGameObject(loadedPrefabs[kvp.first], kvp.second);
	databaseChunkIterator++;
	zoneChunkIterator++;
}

void WorldManager::unloadObjects()
{
	loadedPrefabs.clear();
	loadState = DONE;
}
