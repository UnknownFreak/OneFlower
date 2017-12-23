#ifdef _EDITOR_
#ifndef _UNITTESTS_
#include "WorldManagerAddons.hpp"
#include <AssetManager\AssetManagerCore.hpp>
#include <Core\Component\TransformComponent.hpp>

#include <Graphic\Gfx.h>

#include <World\Zone.hpp>


// this always works cause the worldmanageraddon is always initialized after the world manager
ResourceType IEngineResource<WorldManagerAddon>::type = ResourceType::WorldManagerAddon;

WorldManagerAddon::WorldManagerAddon() : myWorldManager(Engine::Get<WorldManager>()), myModelContainer(Engine::ModelContainer), currentDBZone(nullptr), unloadingbg()
{
}

void WorldManagerAddon::EditorAddNewZone(Core::String zoneName, Core::String background, Core::String loadingScreen, Core::String loadingScreenMessage, size_t ID, float x, float y)
{

	DBZone myDbZone;
	myDbZone.name = zoneName;
	myDbZone.fromMod = Engine::Get<AssetManager>().openedMod;
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
	Engine::Get<AssetManager>().getDBZoneRequester().add(myDbZone);

}
void WorldManagerAddon::EditorEditZone(Core::String zoneName, Core::String background, Core::String loadingScreen, Core::String loadingScreenMessage, size_t ID, float x, float y)
{
	Reference<DBZone>*& refDbZone = Engine::Get<AssetManager>().getDBZoneRequester().request(myWorldManager.lastLoadedZone.first, myWorldManager.lastLoadedZone.second);

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

	Engine::Get<AssetManager>().getDBZoneRequester().requestRemoval(myWorldManager.lastLoadedZone.first, myWorldManager.lastLoadedZone.second);

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
	if (Engine::Get<AssetManager>().openedMod != "<Not Set>")
	{
		if(currentDBZone)
			for (std::map<std::pair<Core::String, size_t>, DBZonePrefabStruct>::iterator
				i = currentDBZone->getReferenced().prefabList.begin();
				i != currentDBZone->getReferenced().prefabList.end(); i++)
			{
				i->second.position = Engine::Get<WorldManager>().listOfZoneObjects[i->first]->GetComponent<Component::TransformComponent>()->position;
			}
		Engine::Get<AssetManager>().saveGameDatabase(getLoadedMod(), myModHeader);
	}
	else
		Engine::Get<OneLogger>().Info("Cannot save mod. No mod loaded!", __FILE__, __LINE__);
	return Engine::Get<AssetManager>().openedMod;
}
std::pair<std::pair<Core::String, size_t>, DBZonePrefabStruct> WorldManagerAddon::EditorAddGameObjectToZone(Prefab& prefab, GameObject* go)
{
	Core::String openedMod = Engine::Get<AssetManager>().openedMod;
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
		Engine::Get<WorldManager>().getCurrentZone()->objects.push_back(std::pair<std::pair<Core::String, size_t>, GameObject*>(std::pair<Core::String, size_t>(openedMod, ValidID), go));
		Engine::Get<WorldManager>().listOfZoneObjects.insert(std::pair<std::pair<Core::String, size_t>, GameObject*>(std::pair<Core::String, size_t>(openedMod, ValidID), go));
	}

	return std::pair<std::pair<Core::String, size_t>, DBZonePrefabStruct>(std::pair<Core::String, size_t>(openedMod, ValidID), dbzps);
}
size_t WorldManagerAddon::EditorGetValidID()
{
	WorldManager& world = Engine::Get<WorldManager>();
	while (world.listOfZoneObjects.find(std::pair<Core::String, size_t>(Engine::Get<AssetManager>().openedMod, ID)) != world.listOfZoneObjects.end())
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
	return Engine::Get<AssetManager>().openedMod;
}
void WorldManagerAddon::unloadEditorVariables()
{
	currentDBZone = nullptr;

	myWorldManager.loadZone("MainMenu", 0);
	while (myWorldManager.getIsLoading())
		myWorldManager.unload();
	Engine::Get<AssetManager>().getPrefabRequester().clear();
	Engine::Get<AssetManager>().getModelRequester().clear();
	Engine::Get<AssetManager>().getDBZoneRequester().clear();
	//myWorldManager.editorPrefabContainer.getMap().clear();
	//myModelContainer.clearLists();
}
void WorldManagerAddon::newMod(Core::String modName, std::vector<Core::String> dependencies, bool createMaster)
{
	ModLoader& modLoadOrder = Engine::Get<AssetManager>().getModLoader();
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

	Engine::Get<AssetManager>().openedMod = modName;
	modLoadOrder.loadOrder.insert(std::pair<Core::String, size_t>(modName, modLoadOrder.loadOrder.size()));
	Engine::Get<AssetManager>().saveGameDatabase("Data\\" + modName, myModHeader);
	//unloadEditorVariables();
	Engine::Get<AssetManager>().loadAllEditorVariables();
	Engine::Get<OneLogger>().Info("Successfully created mod [" + modName + "].", __FILE__, __LINE__);
}
void WorldManagerAddon::loadMod(Core::String myMod)
{
	Engine::Get<Gfx>().bSkipDrawing = true;
	Engine::Get<Gfx>().clearBackground();
	ModLoader& modLoadOrder = Engine::Get<AssetManager>().getModLoader();
	unloadEditorVariables();
	Engine::Get<AssetManager>().openedMod = myMod;
	modLoadOrder.loadOrder.clear();
	bool fail = false;
	if (!Engine::Get<AssetManager>().loadModHeader(myMod, myModHeader))
	{
		Engine::Get<OneLogger>().Critical("Failed to load mod header for mod [" + myMod +"]!", __FILE__, __LINE__);
		Engine::Get<AssetManager>().openedMod = "<Not Set>";
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
		Engine::Get<OneLogger>().Warning("One or more dependency mods failed to load for mod [" + myMod + "].", __FILE__, __LINE__);
	else
		Engine::Get<OneLogger>().Fine("Successfully loaded mod dependencies for mod [" + myMod + "].", __FILE__, __LINE__);
	modLoadOrder.loadOrder.insert(std::pair<Core::String, size_t>(myMod, modLoadOrder.loadOrder.size()));
	Engine::Get<AssetManager>().loadAllEditorVariables();
	Engine::Get<Gfx>().bSkipDrawing = false;
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
	if (!Engine::Get<AssetManager>().loadModHeader(mod, modHdr))
		return{};
	else
		return modHdr.dependencies;
}

bool WorldManagerAddon::loadMods(Core::String myMod, bool internal_error)
{
	ModLoader& modLoadOrder = Engine::Get<AssetManager>().getModLoader();

	ModHeader modHdr;
	if (!Engine::Get<AssetManager>().loadModHeader(myMod, modHdr))
	{
		Engine::Get<OneLogger>().Warning("Failed to load [" + myMod + "] as dependency mod.", __FILE__, __LINE__);
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
				Engine::Get<OneLogger>().Info("[" + var + "] already loaded, skipping.", __FILE__, __LINE__);
		}
		if (modLoadOrder.loadOrder.find(myMod) == modLoadOrder.loadOrder.end())
		{
			Engine::Get<OneLogger>().Info("Adding: " + myMod + "to the mod load order.", __FILE__, __LINE__);
			//std::cout << "adding: " + myMod + "to the modLoadOrder" << std::endl;
			modLoadOrder.loadOrder.insert(std::pair<Core::String, size_t>(myMod, modLoadOrder.loadOrder.size()));
		}
		Engine::Get<OneLogger>().Fine("[" + myMod + "] successfully loaded." , __FILE__, __LINE__);
	}
	return internal_error;
}

std::vector<Core::String> WorldManagerAddon::getExtraZoneInfo(Core::String modName, size_t id)
{
	std::vector<Core::String> t;
	Reference<DBZone>*& dbzone = Engine::Get<AssetManager>().getDBZoneRequester().request(modName, id);
	if (dbzone->isValid())
	{
		DBZone& tmp = dbzone->getReferenced();
		t.push_back(tmp.background.name);
		t.push_back(tmp.loadingScreen.name);
		t.push_back(tmp.loadingScreenMessage);
	}
	// Never getting unloaded with editor enabled, use to decrease ref counter
	Engine::Get<AssetManager>().getDBZoneRequester().requestRemoval(modName, id);
	return t;
}

std::vector<DBZone> WorldManagerAddon::getAllDbZones()
{
	Requester<DBZone>& requester = Engine::Get<AssetManager>().getDBZoneRequester();
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