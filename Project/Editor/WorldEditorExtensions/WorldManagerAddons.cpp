#ifdef _EDITOR_
#ifndef _UNITTESTS_
#include "WorldManagerAddons.hpp"
#include <Asset\AssetManagerCore.hpp>
#include <Core\Component\TransformComponent.hpp>

#include <Graphic\Gfx.h>
#include <Graphic/World/WorldManager.hpp>
#include <Graphic/World/Zone.hpp>

// this always works cause the worldmanageraddon is always initialized after the world manager
ResourceType IEngineResource<WorldManagerAddon>::type = ResourceType::WorldManagerAddon;

WorldManagerAddon::WorldManagerAddon() : myWorldManager(Engine::GetModule<WorldManager>()), currentDBZone(nullptr), unloadingbg()
{
}

void WorldManagerAddon::EditorAddNewZone(Core::String zoneName, Core::String background, Core::String loadingScreen, Core::String loadingScreenMessage, size_t id_to_add, float x, float y)
{

	Database::Zone myDbZone;
	myDbZone.name = zoneName;
	myDbZone.fromMod = Engine::GetModule<Asset::AssetManager>().openedMod;
	myDbZone.ID = id_to_add;
	myDbZone.background = background;
	//myDbZone.background = DBBackgroundSprite(background, 0, 0);

	myDbZone.loadingScreen = loadingScreen;
	myDbZone.loadingScreenMessage = loadingScreenMessage;

	Engine::GetModule<Asset::AssetManager>().getZoneRequester().add(myDbZone);

}
void WorldManagerAddon::EditorEditZone(Core::String zoneName, Core::String background, Core::String loadingScreen, Core::String loadingScreenMessage, size_t id_to_edit, float x, float y)
{
	Database::Zone& refDbZone = Engine::GetModule<Asset::AssetManager>().getZoneRequester().request(myWorldManager.lastLoadedZone.first, myWorldManager.lastLoadedZone.second);

	{
		refDbZone.mode = ObjectSaveMode::EDIT;
		refDbZone.name = zoneName;
		refDbZone.ID = id_to_edit;
		refDbZone.background = background;
		//refDbZone.background.size.x = x;
		//refDbZone.background.size.y = y;

		refDbZone.loadingScreen = loadingScreen;
		refDbZone.loadingScreenMessage = loadingScreenMessage;
	}

	Engine::GetModule<Asset::AssetManager>().getZoneRequester().requestRemoval(myWorldManager.lastLoadedZone.first, myWorldManager.lastLoadedZone.second);

	//EditorSetBackground(background);
}
//void WorldManager::EditorFlagGameObjectForEdit(GameObject* go)
//{
//	for (std::map<std::pair<std::string, size_t>, GameObject*>::iterator
//		i = listOfZoneObjects.begin(); i != listOfZoneObjects.end(); i++)
//	{
//		if (i->second == go)
//		{
//			EditorAllZones[lastLoadedZone].prefabList.find(i->first)->second.mode = ObjectSaveMode::EDIT;
//			EditorAllZones[lastLoadedZone].mode = ObjectSaveMode::EDIT;
//		}
//	}
//}
//
void WorldManagerAddon::EditorLoadZone(Core::String name, unsigned int id_to_load)
{
	myWorldManager.loadZone(name, id_to_load);

	myWorldManager.loadSome();

	currentDBZone = myWorldManager.refZoneToLoad;

	//*change this with listview instead?//*/
	//if (Engine::World.EditorAllZones.find(std::pair<Core::String, size_t>(name, ID)) != Engine::World.EditorAllZones.end())
	//	Engine::World.loadZone(name, ID);
	//else
	//{
	//	//MessageBox(Engine::Window.hWnd, "Could not load Zone", "Err", NULL);
	//}
	/*std::map<unsigned int,std::string>::iterator it = zoneInfo.find(ID);
	if(it != zoneInfo.end())
		loadZone(ID);
	else
		for(it = zoneInfo.begin(); it != zoneInfo.end(); ++it)
			if(it->second == name + ".zone")
			{
				loadZone(it->first);
				break;
			}*/
}

void WorldManagerAddon::EditorRemoveZone()
{
	if(currentDBZone)
		if (currentDBZone->mode == ObjectSaveMode::REMOVE)
			currentDBZone->mode = ObjectSaveMode::EDIT;
		else
			currentDBZone->mode = ObjectSaveMode::REMOVE;
}
Core::String WorldManagerAddon::EditorSave()
{
	if (Engine::GetModule<Asset::AssetManager>().openedMod != "<Not Set>")
	{
		//if(currentDBZone)
			//for (std::map<std::pair<Core::String, size_t>, Database::Prefab>::iterator
			//	i = currentDBZone->prefabList.begin();
			//	i != currentDBZone->prefabList.end(); i++)
			//{
			//	i->second.pos = Engine::GetModule<WorldManager>().listOfZoneObjects[i->first]->GetComponent<Component::Transform>()->position;
			//}
		Engine::GetModule<Asset::AssetManager>().saveGameDatabase(getLoadedMod(), myModHeader);
		Engine::GetModule<OneLogger>().Info("Successfully saved " + Engine::GetModule<Asset::AssetManager>().openedMod + ".");
	}
	else
		Engine::GetModule<OneLogger>().Info("Cannot save mod. No mod loaded!", __FILE__, __LINE__);
	return Engine::GetModule<Asset::AssetManager>().openedMod;
}
std::pair<std::pair<Core::String, size_t>, Database::Prefab> WorldManagerAddon::EditorAddGameObjectToZone(Asset::Prefab& prefab, GameObject* go)
{
	Core::String openedMod = Engine::GetModule<Asset::AssetManager>().openedMod;
	Database::Prefab dbzps;
	dbzps.ID = prefab.ID;
	dbzps.fromMod = prefab.fromMod;
	dbzps.pos = go->GetComponent<Component::Transform>()->position;
	dbzps.oldPos = dbzps.pos;
	dbzps.name = prefab.name;
	size_t ValidID = EditorGetValidID();

	if (currentDBZone)
	{
		currentDBZone->mode = ObjectSaveMode::EDIT;
		//currentDBZone->prefabs.insert(std::pair<std::pair<Core::String, size_t>, Database::Prefab>(std::pair<Core::String, size_t>(openedMod, ValidID), dbzps));

		//Engine::GetModule<WorldManager>().getCurrentZone().objects.push_back(std::pair<std::pair<Core::String, size_t>, GameObject*>(std::pair<Core::String, size_t>(openedMod, ValidID), go));
		Engine::GetModule<WorldManager>().listOfZoneObjects.insert(std::pair<std::pair<Core::String, size_t>, GameObject*>(std::pair<Core::String, size_t>(openedMod, ValidID), go));
	}

	return std::pair<std::pair<Core::String, size_t>, Database::Prefab>(std::pair<Core::String, size_t>(openedMod, ValidID), dbzps);
}
size_t WorldManagerAddon::EditorGetValidID()
{
	WorldManager& world = Engine::GetModule<WorldManager>();
	while (world.listOfZoneObjects.find(std::pair<Core::String, size_t>(Engine::GetModule<Asset::AssetManager>().openedMod, ID)) != world.listOfZoneObjects.end())
		ID++;
	return ID;
}
void WorldManagerAddon::EditorSetBackground(std::string name)
{
	myWorldManager.currentZone->setBackground(name);
	//Engine::game.addSprite(currentZone->getBackground(), true);
}
void WorldManagerAddon::EditorSetBackgroundSize(int x, int y)
{
	myWorldManager.currentZone->getBackground()->size.x = x;
	myWorldManager.currentZone->getBackground()->size.y = y;
	//Engine::game.addSprite(currentZone->getBackground(), true);
}
//void WorldManager::RemoveGameObjectFromZone(GameObject* go)
//{
//	for (std::map<std::pair<std::string, size_t>, DBZonePrefabStruct>::iterator i = EditorAllZones[lastLoadedZone].prefabList.begin();
//		i != EditorAllZones[lastLoadedZone].prefabList.end(); i++)
//	{
//		for (std::vector<std::pair<std::pair<std::string, size_t>, GameObject*>>::iterator it = currentZone->objects.begin();
//			it != currentZone->objects.end(); it++)
//		{
//			if (it->second == go && it->first == i->first)
//			{
//				//currentZone->objects.erase(currentZone->objects.begin() + i);
//				listOfZoneObjects.erase(listOfZoneObjects.find(i->first));
//				EditorAllZones[lastLoadedZone].prefabList.erase(i);
//				return;
//			}
//		}
//	}
//}
//void WorldManager::AddQuest(Quests::Quest quest)
//{
//	quest.fromMod = openedMod;
//	EditorAllQuests.insert(std::pair<std::pair<std::string, unsigned int>, Quests::Quest>(std::pair<std::string, unsigned int>(openedMod, quest.ID), quest));
//}
//void WorldManager::AddItem(Items::Item* item)
//{
//	item->fromMod = openedMod;
//	EditorAllItems.insert(std::pair<std::pair<std::string, unsigned int>, Items::Item*>(std::pair<std::string, unsigned int>(openedMod, item->getID()), item));
//}
std::string WorldManagerAddon::getLoadedMod()
{
	return Engine::GetModule<Asset::AssetManager>().openedMod;
}
void WorldManagerAddon::unloadEditorVariables()
{
	currentDBZone = nullptr;

	//myWorldManager.loadZone("MainMenu", 0);
	while (myWorldManager.isLoading())
		myWorldManager.unload();
	Engine::GetModule<Asset::AssetManager>().getPrefabRequester().clear();
	Engine::GetModule<Asset::AssetManager>().getModelRequester().clear();
	Engine::GetModule<Asset::AssetManager>().getZoneRequester().clear();
	//myWorldManager.editorPrefabContainer.getMap().clear();
	//myModelContainer.clearLists();
}
void WorldManagerAddon::newMod(Core::String modName, std::vector<Core::String> dependencies, bool createMaster)
{
	ModLoader& modLoadOrder = Engine::GetModule<Asset::AssetManager>().getModLoader();
	modLoadOrder.loadOrder.clear();
	if (createMaster)
		modName.append(".main");
	else
		modName.append(".mod");

	myModHeader.name = modName;
	myModHeader.dependencies = dependencies;
	//for each (std::string var in myWorldManager.myModHeader.dependencies)
	//{
	//	loadMods(var);
	//}

	Engine::GetModule<Asset::AssetManager>().openedMod = modName;
	modLoadOrder.loadOrder.insert(std::pair<Core::String, size_t>(modName, modLoadOrder.loadOrder.size()));
	Engine::GetModule<Asset::AssetManager>().saveGameDatabase(modName, myModHeader);
	//unloadEditorVariables();
	Engine::GetModule<Asset::AssetManager>().loadAllEditorVariables();
	Engine::GetModule<OneLogger>().Info("Successfully created mod [" + modName + "].", __FILE__, __LINE__);
}
void WorldManagerAddon::loadMod(Core::String myMod)
{
	Engine::GetModule<Gfx>().bSkipDrawing = true;
	Engine::GetModule<Gfx>().clearBackground();
	ModLoader& modLoadOrder = Engine::GetModule<Asset::AssetManager>().getModLoader();
	unloadEditorVariables();
	Engine::GetModule<Asset::AssetManager>().openedMod = myMod;
	modLoadOrder.loadOrder.clear();
	bool fail = false;
	if (!Engine::GetModule<Asset::AssetManager>().loadModHeader(myMod, myModHeader))
	{
		Engine::GetModule<OneLogger>().Critical("Failed to load mod header for mod [" + myMod +"]!", __FILE__, __LINE__);
		Engine::GetModule<Asset::AssetManager>().openedMod = "<Not Set>";
	}
	else
	{
		for each (Core::String var in myModHeader.dependencies)
		{
			if (loadMods(var))
				fail = true;
		}
	}
	if (fail)
		Engine::GetModule<OneLogger>().Warning("One or more dependency mods failed to load for mod [" + myMod + "].", __FILE__, __LINE__);
	else
		Engine::GetModule<OneLogger>().Fine("Successfully loaded mod dependencies for mod [" + myMod + "].", __FILE__, __LINE__);
	modLoadOrder.loadOrder.insert(std::pair<Core::String, size_t>(myMod, modLoadOrder.loadOrder.size()));
	Engine::GetModule<Asset::AssetManager>().loadAllEditorVariables();
	Engine::GetModule<Gfx>().bSkipDrawing = false;
}
//void WorldManagerAddon::LoadAllEditorVariables()
//{
//	//LoadAllTextureMaps(Engine::ModelContainer);
//	LoadAllZones(EditorAllZones);
//	LoadAllPrefabs(editorPrefabContainer);
//	//LoadAllItems(EditorAllItems);
//	//LoadAllQuests(EditorAllQuests);
//}
std::vector<Core::String> WorldManagerAddon::getModDependencies(Core::String mod)
{
	ModHeader modHdr;
	if (!Engine::GetModule<Asset::AssetManager>().loadModHeader(mod, modHdr))
		return {};
	else
		return modHdr.dependencies;
}

bool WorldManagerAddon::loadMods(Core::String myMod, bool internal_error)
{
	ModLoader& modLoadOrder = Engine::GetModule<Asset::AssetManager>().getModLoader();

	ModHeader modHdr;
	if (!Engine::GetModule<Asset::AssetManager>().loadModHeader(myMod, modHdr))
	{
		Engine::GetModule<OneLogger>().Warning("Failed to load [" + myMod + "] as dependency mod.", __FILE__, __LINE__);
		internal_error = true;
	}
	else
	{
		//std::cout << "checking: " + myMod + "dependencies" << std::endl;
		for each (Core::String var in modHdr.dependencies)
		{
			if (modLoadOrder.loadOrder.find(var) == modLoadOrder.loadOrder.end())
				internal_error = loadMods(var, internal_error);
			else
				Engine::GetModule<OneLogger>().Info("[" + var + "] already loaded, skipping.", __FILE__, __LINE__);
		}
		if (modLoadOrder.loadOrder.find(myMod) == modLoadOrder.loadOrder.end())
		{
			Engine::GetModule<OneLogger>().Info("Adding: " + myMod + "to the mod load order.", __FILE__, __LINE__);
			//std::cout << "adding: " + myMod + "to the modLoadOrder" << std::endl;
			modLoadOrder.loadOrder.insert(std::pair<Core::String, size_t>(myMod, modLoadOrder.loadOrder.size()));
		}
		Engine::GetModule<OneLogger>().Fine("[" + myMod + "] successfully loaded." , __FILE__, __LINE__);
	}
	return internal_error;
}

std::vector<Core::String> WorldManagerAddon::getExtraZoneInfo(Core::String modName, size_t id)
{
	std::vector<Core::String> t;
	Database::Zone& dbzone = Engine::GetModule<Asset::AssetManager>().getZoneRequester().request(modName, id);
	{
		t.push_back(dbzone.background);
		t.push_back(dbzone.loadingScreen);
		t.push_back(dbzone.loadingScreenMessage);
	}
	// Never getting unloaded with editor enabled, use to decrease ref counter
	Engine::GetModule<Asset::AssetManager>().getZoneRequester().requestRemoval(modName, id);
	return t;
}

std::vector<Database::Zone> WorldManagerAddon::getAllDbZones()
{
	Requestor<Database::Zone>& requester = Engine::GetModule<Asset::AssetManager>().getZoneRequester();
	std::vector<Database::Zone> dbzones;
	std::vector<std::pair<Core::String, size_t>> dbzoneIds = requester.listAllCurrentLoadedObjects();
	for each(const std::pair<Core::String, size_t>& p in dbzoneIds)
	{
		Database::Zone& dbref = requester.request(p.first, p.second);
		dbzones.push_back(dbref);
		// reduce the ref counter // Remember with editor mode objects will not be unloaded unless clear() is called;
		requester.requestRemoval(p.first, p.second);
	}
	return dbzones;
}

#endif
#endif