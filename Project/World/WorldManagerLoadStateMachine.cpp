#include "WorldManager.hpp"

#include "Zone.hpp"

#include <Core/Component/GameObject.h>
#include <Core/Component/TransformComponent.hpp>

#include <Graphic/GraphicsCore.hpp>


void WorldManager::startLoad()
{
	isLoading = true;
	currentZone = nullptr;
	loadState = STATE_REQUEST_DBZONE;
}

void WorldManager::loadSome()
{
	switch (loadState)
	{
	case STATE_NOT_SET:
		break;
	case STATE_REQUEST_DBZONE:
		requestZoneToLoad();
		break;
	case STATE_UNREQUEST_DBZONE:
		unrequestZoneToLoad();
		break;
	case STATE_PREPARE_LOAD:
		prepareLoad();
		break;
	case STATE_UNLOAD_OBJECTS:
		unloadObjects();
		break;
	case STATE_RELOAD_OBJECTS:
		reloadObjects();
		break;
	case STATE_DONE:
		lastLoadedZone = zoneToLoadID;
		isLoading = false;
		break;
	case STATE_ERR_LOADING:
		isLoading = false;
		break;
	default:
		break;
	}
}
#ifdef _EDITOR_
void WorldManager::unload()
{
	switch (loadState)
	{
	case STATE_NOT_SET:
		break;
	case STATE_REQUEST_DBZONE:
		requestZoneToLoad();
		break;
	case STATE_UNREQUEST_DBZONE:
		unrequestZoneToLoad();
		break;
	case STATE_PREPARE_LOAD:
		prepareLoad();
		break;
	case STATE_UNLOAD_OBJECTS:
		unloadObjects();
		break;
	case STATE_RELOAD_OBJECTS:
		isLoading = false;
		for each (auto var in worldmap)
			delete var.second;
		worldmap.clear();
		addMainMenu();
		return;
	}
}
#endif

void WorldManager::requestZoneToLoad()
{
	refZoneToLoad = Engine::Get<AssetManager>().getDBZoneRequester().request(zoneToLoadID.first, zoneToLoadID.second);

	if (worldmap.find(std::pair<Core::String, size_t>(zoneToLoadID.first, zoneToLoadID.second)) == worldmap.end())
	{
		if (refZoneToLoad->isValid())
		{
			DBZone& refzone = refZoneToLoad->getReferenced();
			zoneToLoadID = std::pair<std::string, size_t>(zoneToLoadID.first, zoneToLoadID.second);
			worldmap.insert(std::pair<std::pair<Core::String, size_t>, Zone*>(zoneToLoadID, new Zone(refzone)));
		}
	}
	loadState = STATE_PREPARE_LOAD;
}

void WorldManager::unrequestZoneToLoad()
{
	Engine::Get<AssetManager>().getDBZoneRequester().requestRemoval(zoneToLoadID.first, zoneToLoadID.second);
	refZoneToLoad = nullptr;
	Engine::Get<Gfx>().setBackground(currentZone->background);
	loadState = STATE_DONE;
}


void WorldManager::prepareLoad()
{
	if (!refZoneToLoad->isValid())
		loadState = STATE_ERR_LOADING;
	DBZone& dbzone = refZoneToLoad->getReferenced();
#ifdef _EDITOR_

	if (lastLoadedZone.second != 0)
	{
		totalToLoad = dbzone.prefabList.size();
		currentObjIterator = dbzone.prefabList.begin();
	}

	currentObjIteratorUnload = listOfZoneObjects.begin();
	totalToLoad += dbzone.prefabList.size();
#else
	totalToLoad = listOfZoneObjects.size();
	currentObjIteratorUnload = listOfZoneObjects.begin();
	totalToLoad += zoneToLoad.prefabList.size();
#endif
	//Engine::game.addSprite(worldmap[zoneToLoadID]->getBackground(), true);
	currentZone = worldmap[zoneToLoadID];
	//loadingScreenProgress.setMax(totalToLoad);
	totalLoaded = 0;
	currentObj = 0;
	loadState = STATE_UNLOAD_OBJECTS;
}


void WorldManager::unloadObjects()
{
	if (lastLoadedZone.second != 0)
	{
		if (currentObj == listOfZoneObjects.size())
		{
			loadState = STATE_RELOAD_OBJECTS;
			listOfZoneObjects.clear();
			currentObj = 0;
#ifdef _EDITOR_
			if (!refZoneToLoad->isValid())
				loadState = STATE_ERR_LOADING;
			DBZone& dbzone = refZoneToLoad->getReferenced();
			currentObjIterator = dbzone.prefabList.begin();
#else
			currentObjIterator = zoneToLoad.prefabList.begin();
#endif
			return;
		}
#ifdef _EDITOR_
		currentObjIterator->second.position = listOfZoneObjects[currentObjIteratorUnload->first]->GetComponent<Component::TransformComponent>()->position;
		currentObjIterator++;
#endif
		//Engine::game.requestRemoveal(listOfZoneObjects[currentObjIteratorUnload->first]);
		currentObj++;
		totalLoaded++;
		currentObjIteratorUnload++;
		//loadingScreenProgress.setValue(totalLoaded);
	}
	else
	{
		loadState = STATE_RELOAD_OBJECTS;
#ifdef _EDITOR_
		if (!refZoneToLoad->isValid())
			loadState = STATE_ERR_LOADING;
		DBZone& dbzone = refZoneToLoad->getReferenced();
		currentObjIterator = dbzone.prefabList.begin();
#else
		currentObjIterator = zoneToLoad.prefabList.begin();
#endif
	}
}
void WorldManager::reloadObjects()
{
#ifdef _EDITOR_
	if (!refZoneToLoad->isValid())
		loadState = STATE_ERR_LOADING;
	DBZone& dbzone = refZoneToLoad->getReferenced();
	if (currentObj == dbzone.prefabList.size())
	{
		loadState = STATE_UNREQUEST_DBZONE;
		//loadState = 1337;
		return;
	}
	else
	{
		{
			Reference<Prefab>*& prefab = Engine::Get<AssetManager>().getPrefabRequester().request(currentObjIterator->second.fromMod, currentObjIterator->second.ID);
			//std::map<std::pair<std::string, size_t>, Prefab>::iterator it = editorPrefabContainer.find(currentObjIterator->second.fromMod, currentObjIterator->second.ID);
			if (prefab->isValid())
			{

				GameObject* go = prefab->getReferenced().createFromPrefab();
				go->GetComponent<Component::TransformComponent>()->position = currentObjIterator->second.position;

				worldmap[zoneToLoadID]->objects.push_back(std::pair<std::pair<std::string, size_t>, GameObject*>(currentObjIterator->first, go));
				listOfZoneObjects.insert(std::pair<std::pair<std::string, size_t>, GameObject*>(currentObjIterator->first, go));
				//Engine::game.addGameObject(go);
			}
			Engine::Get<AssetManager>().getPrefabRequester().requestRemoval(currentObjIterator->second.fromMod, currentObjIterator->second.ID);
		}
		currentObj++;
		currentObjIterator++;
		totalLoaded++;
	}
#else
	// will need rework since stuff have changed.
	if (currentObj == zoneToLoad.prefabList.size())
	{
		loadState = STATE_UNREQUEST_DBZONE;
	}
	else
	{
		DBZonePrefabStruct prefabID = zoneToLoad.prefabList[currentObjIterator->first];
		{
			Prefab toLoad;
			toLoad.name = "NotInit";
			//if (loadPrefab(prefabID.fromMod, prefabID.ID, toLoad))
			{
				GameObject* go = toLoad.createFromPrefab();
				go->GetComponent<Component::TransformComponent>()->position = prefabID.position;

				worldmap[zoneToLoadID]->objects.push_back(std::pair<std::pair<Core::String, size_t>, GameObject*>(currentObjIterator->first, go));
				listOfZoneObjects.insert(std::pair<std::pair<Core::String, size_t>, GameObject*>(currentObjIterator->first, go));
				//Engine::game.addGameObject(go);
			}
		}
		currentObj++;
		totalLoaded++;
		currentObjIterator++;
	}
#endif
	//loadingScreenProgress.setValue(totalLoaded);
}
