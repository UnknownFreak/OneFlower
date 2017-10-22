#ifdef _EDITOR_
#ifndef _UNITTESTS_
#include "WorldManagerAddons.hpp"
#include <AssetManager\AssetManagerCore.hpp>
#include <AssetManager\Database\DBZone.hpp>
#include <World\WorldCore.hpp>
#include <Core\Component\TransformComponent.hpp>
#include <Core\Component\GameObject.h>
#include <World\Zone.hpp>
#include <Graphic\GraphicsCore.hpp>
#include <Logger\Logger.hpp>

// this always works cause the worldmanageraddon is always initialized after the world manager
WorldManagerAddon::WorldManagerAddon() : myWorldManager(Engine::World), myModelContainer(Engine::ModelContainer), currentDBZone(nullptr), unloadingbg()
{
}
void WorldManagerAddon::EditorAddNewZone(Core::String zoneName, Core::String background, Core::String loadingScreen, Core::String loadingScreenMessage, size_t ID, float x, float y)
{

	DBZone myDbZone;
	myDbZone.name = zoneName;
	myDbZone.fromMod = Engine::getAssetManager().openedMod;
	myDbZone.ID = ID;
	myDbZone.background.name = background;
	myDbZone.background.position = Core::Vector2(0, 0);
	myDbZone.background.size.x = x;
	myDbZone.background.size.y = y;
	//myDbZone.background = DBBackgroundSprite(background, 0, 0);

	myDbZone.loadingScreen.name = loadingScreen;
	myDbZone.loadingScreenMessage = loadingScreenMessage;

	if (zoneName == "Tutorial" && ID == 1)
		myDbZone.fromMod = "<__CORE__>";
	Engine::getDBZoneRequester().add(myDbZone);

}
void WorldManagerAddon::EditorEditZone(Core::String zoneName, Core::String background, Core::String loadingScreen, Core::String loadingScreenMessage, size_t ID, float x, float y)
{
	Reference<DBZone>*& refDbZone = Engine::getDBZoneRequester().request(myWorldManager.lastLoadedZone.first, myWorldManager.lastLoadedZone.second);

	{
		DBZone& dbzone = refDbZone->getReferenced();

		dbzone.mode = ObjectSaveMode::EDIT;
		dbzone.name = zoneName;
		dbzone.ID = ID;
		dbzone.background.name = background;
		dbzone.background.size.x = x;
		dbzone.background.size.y = y;

		dbzone.loadingScreen.name = loadingScreen;
		dbzone.loadingScreenMessage = loadingScreenMessage;
	}

	Engine::getDBZoneRequester().requestRemoval(myWorldManager.lastLoadedZone.first, myWorldManager.lastLoadedZone.second);

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
void WorldManagerAddon::EditorLoadZone(Core::String name, unsigned int ID)
{
	myWorldManager.loadZone(name, ID);

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
		if (currentDBZone->getReferenced().mode == ObjectSaveMode::REMOVE)
			currentDBZone->getReferenced().mode = ObjectSaveMode::EDIT;
		else
			currentDBZone->getReferenced().mode = ObjectSaveMode::REMOVE;
}
Core::String WorldManagerAddon::EditorSave()
{
	if (Engine::getAssetManager().openedMod != "<Not Set>")
	{
		if(currentDBZone)
			for (std::map<std::pair<Core::String, size_t>, DBZonePrefabStruct>::iterator
				i = currentDBZone->getReferenced().prefabList.begin();
				i != currentDBZone->getReferenced().prefabList.end(); i++)
			{
				i->second.position = Engine::World.listOfZoneObjects[i->first]->GetComponent<Component::TransformComponent>()->position;
			}
		Engine::getAssetManager().saveGameDatabase(getLoadedMod(), myModHeader);
	}
	else
		OneLogger::Info("Cannot save mod. No mod loaded!");
	return Engine::getAssetManager().openedMod;
}
std::pair<std::pair<Core::String, size_t>, DBZonePrefabStruct> WorldManagerAddon::EditorAddGameObjectToZone(Prefab& prefab, GameObject* go)
{
	Core::String openedMod = Engine::getAssetManager().openedMod;
	DBZonePrefabStruct dbzps;
	dbzps.ID = prefab.ID;
	dbzps.fromMod = prefab.fromMod;
	dbzps.position = go->GetComponent<Component::TransformComponent>()->position;
	dbzps.oldPosition = dbzps.position;
	dbzps.prefabName = prefab.name;
	size_t ValidID = EditorGetValidID();

	if (currentDBZone)
	{
		DBZone& dbref = currentDBZone->getReferenced();
		dbref.mode = ObjectSaveMode::EDIT;
		dbref.prefabList.insert(std::pair<std::pair<Core::String, size_t>, DBZonePrefabStruct>(std::pair<Core::String, size_t>(openedMod, ValidID), dbzps));
		Engine::World.getCurrentZone()->objects.push_back(std::pair<std::pair<Core::String, size_t>, GameObject*>(std::pair<Core::String, size_t>(openedMod, ValidID), go));
		Engine::World.listOfZoneObjects.insert(std::pair<std::pair<Core::String, size_t>, GameObject*>(std::pair<Core::String, size_t>(openedMod, ValidID), go));
	}

	return std::pair<std::pair<Core::String, size_t>, DBZonePrefabStruct>(std::pair<Core::String, size_t>(openedMod, ValidID), dbzps);
}
size_t WorldManagerAddon::EditorGetValidID()
{
	while (Engine::World.listOfZoneObjects.find(std::pair<Core::String, size_t>(Engine::getAssetManager().openedMod, ID)) != Engine::World.listOfZoneObjects.end())
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
	return Engine::getAssetManager().openedMod;
}
void WorldManagerAddon::unloadEditorVariables()
{
	currentDBZone = nullptr;

	myWorldManager.loadZone("MainMenu", 0);
	while (myWorldManager.getIsLoading())
		myWorldManager.unload();
	Engine::getPrefabRequester().clear();
	Engine::getModelRequester().clear();
	Engine::getDBZoneRequester().clear();
	//myWorldManager.editorPrefabContainer.getMap().clear();
	//myModelContainer.clearLists();
}
void WorldManagerAddon::newMod(Core::String modName, std::vector<Core::String> dependencies, bool createMaster)
{
	ModLoader& modLoadOrder = Engine::getAssetManager().getModLoader();
	WorldManagerAddon::EditorAddNewZone("Tutorial", "testBackground.png", "testBackground.png", "Tutorial Zone", 1, 1000, 800);
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

	Engine::getAssetManager().openedMod = modName;
	modLoadOrder.loadOrder.insert(std::pair<Core::String, size_t>(modName, modLoadOrder.loadOrder.size()));
	Engine::getAssetManager().saveGameDatabase("Data\\" + modName, myModHeader);
	//unloadEditorVariables();
	Engine::getAssetManager().loadAllEditorVariables();
	OneLogger::Info("Successfully created mod [" + modName + "].");
}
void WorldManagerAddon::loadMod(Core::String myMod)
{
	ModLoader& modLoadOrder = Engine::getAssetManager().getModLoader();
	unloadEditorVariables();
	Engine::getAssetManager().openedMod = myMod;
	Engine::Graphic.setBackground(unloadingbg);
	modLoadOrder.loadOrder.clear();
	bool fail = false;
	if (!Engine::getAssetManager().loadModHeader(myMod, myModHeader))
	{
		OneLogger::Severe("Failed to load mod header for mod [" + myMod +"]!", __FILE__, __LINE__);
		Engine::getAssetManager().openedMod = "<Not Set>";
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
		OneLogger::Warning("One or more dependency mods failed to load for mod [" + myMod + "].", __FILE__, __LINE__);
	else
		OneLogger::Fine("Successfully loaded mod dependencies for mod [" + myMod + "].", __FILE__, __LINE__);
	modLoadOrder.loadOrder.insert(std::pair<Core::String, size_t>(myMod, modLoadOrder.loadOrder.size()));
	Engine::getAssetManager().loadAllEditorVariables();
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
	if (!Engine::getAssetManager().loadModHeader(mod, modHdr))
		return{};
	else
		return modHdr.dependencies;
}

bool WorldManagerAddon::loadMods(Core::String myMod, bool internal_error)
{
	ModLoader& modLoadOrder = Engine::getAssetManager().getModLoader();

	ModHeader modHdr;
	if (!Engine::getAssetManager().loadModHeader(myMod, modHdr))
	{
		OneLogger::Warning("Failed to load [" + myMod + "] as dependency mod.", __FILE__, __LINE__);
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
				OneLogger::Info("[" + var + "] already loaded, skipping.", __FILE__, __LINE__);
		}
		if (modLoadOrder.loadOrder.find(myMod) == modLoadOrder.loadOrder.end())
		{
			OneLogger::Info("Adding: " + myMod + "to the mod load order.", __FILE__, __LINE__);
			//std::cout << "adding: " + myMod + "to the modLoadOrder" << std::endl;
			modLoadOrder.loadOrder.insert(std::pair<Core::String, size_t>(myMod, modLoadOrder.loadOrder.size()));
		}
		OneLogger::Fine("[" + myMod + "] successfully loaded." , __FILE__, __LINE__);
	}
	return internal_error;
}

std::vector<Core::String> WorldManagerAddon::getExtraZoneInfo(Core::String modName, size_t id)
{
	std::vector<Core::String> t;
	Reference<DBZone>*& dbzone = Engine::getDBZoneRequester().request(modName, id);
	if (dbzone->isValid())
	{
		DBZone& tmp = dbzone->getReferenced();
		t.push_back(tmp.background.name);
		t.push_back(tmp.loadingScreen.name);
		t.push_back(tmp.loadingScreenMessage);
	}
	// Never getting unloaded with editor enabled, use to decrease ref counter
	Engine::getDBZoneRequester().requestRemoval(modName, id);
	return t;
}

std::vector<DBZone> WorldManagerAddon::getAllDbZones()
{
	Requester<DBZone>& requester = Engine::getDBZoneRequester();
	std::vector<DBZone> dbzones;
	std::vector<std::pair<Core::String, size_t>> dbzoneIds = requester.listAllCurrentLoadedObjects();
	for each(const std::pair<Core::String, size_t>& p in dbzoneIds)
	{
		Reference<DBZone>*& dbref = requester.request(p.first, p.second);
		dbzones.push_back(dbref->getReferenced());
		// reduce the ref counter // Remember with editor mode objects will not be unloaded unless clear() is called;
		requester.requestRemoval(p.first, p.second);
	}
	return dbzones;
}

#endif
#endif