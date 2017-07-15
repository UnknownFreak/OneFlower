#ifdef _EDITOR_
#include "WorldManagerAddons.hpp"
#include <AssetManager\AssetManagerCore.hpp>
#include <AssetManager\Database\DBZone.hpp>
#include <World\WorldCore.hpp>
#include <Core\Component\TransformComponent.hpp>
#include <Core\Component\GameObject.h>
#include <World\Zone.hpp>

#include <Logger\Logger.hpp>

// this always works cause the worldmanageraddon is always initialized after the world manager
WorldManagerAddon::WorldManagerAddon() : myActualManager(Engine::World), myModelContainer(Engine::ModelContainer)
{
}
void WorldManagerAddon::EditorAddNewZone(Core::String zoneName, Core::String background, Core::String loadingScreen, Core::String loadingScreenMessage, size_t ID, float x, float y)
{

	DBZone myDbZone;
	myDbZone.name = zoneName;
	myDbZone.fromMod = AssetManagerCore::openedMod;
	myDbZone.ID = ID;
	myDbZone.background.name = background;
	myDbZone.background.position = Core::Vector2(0, 0);
	myDbZone.background.size.x = x;
	myDbZone.background.size.y = y;
	//myDbZone.background = DBBackgroundSprite(background, 0, 0);

	myDbZone.loadingScreen.name = loadingScreen;
	myDbZone.loadingScreenMessage = loadingScreenMessage;

	if (zoneName == "Tutorial" && ID == 1)
	{
		myDbZone.fromMod = "<__CORE__>";
		Engine::World.EditorAllZones.insert(std::pair<std::pair<Core::String, size_t>, DBZone>(std::pair<Core::String, size_t>("<__CORE__>", ID), myDbZone));
	}
	else
		Engine::World.EditorAllZones.insert(std::pair<std::pair<Core::String, size_t>, DBZone>(std::pair<Core::String, size_t>(AssetManagerCore::openedMod, ID), myDbZone));
}
void WorldManagerAddon::EditorEditZone(Core::String zoneName, Core::String background, Core::String loadingScreen, Core::String loadingScreenMessage, size_t ID, float x, float y)
{
	myActualManager.EditorAllZones[myActualManager.lastLoadedZone].mode = ObjectSaveMode::EDIT;
	myActualManager.EditorAllZones[myActualManager.lastLoadedZone].name = zoneName;
	myActualManager.EditorAllZones[myActualManager.lastLoadedZone].ID = ID;
	myActualManager.EditorAllZones[myActualManager.lastLoadedZone].background.name = background;
	myActualManager.EditorAllZones[myActualManager.lastLoadedZone].background.size.x = x;
	myActualManager.EditorAllZones[myActualManager.lastLoadedZone].background.size.y = y;

	myActualManager.EditorAllZones[myActualManager.lastLoadedZone].loadingScreen.name = loadingScreen;
	myActualManager.EditorAllZones[myActualManager.lastLoadedZone].loadingScreen.position.x = 0;
	myActualManager.EditorAllZones[myActualManager.lastLoadedZone].loadingScreen.position.y = 0;
	myActualManager.EditorAllZones[myActualManager.lastLoadedZone].loadingScreenMessage = loadingScreenMessage;
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
	//*change this with listview instead?//*/
	if (Engine::World.EditorAllZones.find(std::pair<Core::String, size_t>(name, ID)) != Engine::World.EditorAllZones.end())
		Engine::World.loadZone(name, ID);
	else
	{
		//MessageBox(Engine::Window.hWnd, "Could not load Zone", "Err", NULL);
	}
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
	if (Engine::World.EditorAllZones[Engine::World.lastLoadedZone].mode == ObjectSaveMode::REMOVE)
		Engine::World.EditorAllZones[Engine::World.lastLoadedZone].mode = ObjectSaveMode::EDIT;
	else
		Engine::World.EditorAllZones[Engine::World.lastLoadedZone].mode = ObjectSaveMode::REMOVE;
}
Core::String WorldManagerAddon::EditorSave()
{
	if (AssetManagerCore::openedMod != "<Not Set>")
	{
		for (std::map<std::pair<Core::String, size_t>, DBZonePrefabStruct>::iterator
			i = Engine::World.EditorAllZones[Engine::World.lastLoadedZone].prefabList.begin();
			i != Engine::World.EditorAllZones[Engine::World.lastLoadedZone].prefabList.end(); i++)
		{
			i->second.position = Engine::World.listOfZoneObjects[i->first]->GetComponent<Component::TransformComponent>()->position;
		}
		AssetManagerCore::saveGameDatabase(getLoadedMod(), myActualManager.myModHeader, myActualManager.editorPrefabContainer, myActualManager.EditorAllZones);
	}
	else
		Logger::Info("Cannot save mod. No mod loaded!");
	return AssetManagerCore::openedMod;
}
std::pair<std::pair<Core::String, size_t>, DBZonePrefabStruct> WorldManagerAddon::EditorAddGameObjectToZone(Prefab& prefab, GameObject* go)
{
	DBZonePrefabStruct dbzps;
	dbzps.ID = prefab.ID;
	dbzps.fromMod = prefab.fromMod;
	dbzps.position = go->GetComponent<Component::TransformComponent>()->position;
	dbzps.oldPosition = dbzps.position;
	dbzps.prefabName = prefab.name;
	size_t ValidID = EditorGetValidID();
	Engine::World.EditorAllZones[Engine::World.lastLoadedZone].mode = ObjectSaveMode::EDIT;
	Engine::World.EditorAllZones[Engine::World.lastLoadedZone].prefabList.insert(std::pair<std::pair<Core::String, size_t>, DBZonePrefabStruct>(std::pair<Core::String, size_t>(AssetManagerCore::openedMod, ValidID), dbzps));
	Engine::World.getCurrentZone()->objects.push_back(std::pair<std::pair<Core::String, size_t>, GameObject*>(std::pair<Core::String, size_t>(AssetManagerCore::openedMod, ValidID), go));
	Engine::World.listOfZoneObjects.insert(std::pair<std::pair<Core::String, size_t>, GameObject*>(std::pair<Core::String, size_t>(AssetManagerCore::openedMod, ValidID), go));

	return std::pair<std::pair<Core::String, size_t>, DBZonePrefabStruct>(std::pair<Core::String, size_t>(AssetManagerCore::openedMod, ValidID), dbzps);
}
size_t WorldManagerAddon::EditorGetValidID()
{
	while (Engine::World.listOfZoneObjects.find(std::pair<Core::String, size_t>(AssetManagerCore::openedMod, ID)) != Engine::World.listOfZoneObjects.end())
		ID++;
	return ID;
}
void WorldManagerAddon::EditorSetBackground(std::string name)
{
	myActualManager.currentZone->setBackground(name);
	//Engine::game.addSprite(currentZone->getBackground(), true);
}
void WorldManagerAddon::EditorSetBackgroundSize(int x, int y)
{
	myActualManager.currentZone->getBackground()->size.x = x;
	myActualManager.currentZone->getBackground()->size.y = y;
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
	return AssetManagerCore::openedMod;
}
void WorldManagerAddon::unloadEditorVariables()
{
	myActualManager.loadZone("MainMenu", 0);

	while (myActualManager.getIsLoading())
		myActualManager.unload();
	myActualManager.editorPrefabContainer.getMap().clear();
	myModelContainer.clearLists();
}
void WorldManagerAddon::newMod(Core::String modName, std::vector<Core::String> dependencies, bool createMaster)
{
	WorldManagerAddon::EditorAddNewZone("Tutorial", "test.png", "test.png", "Tutorial Zone", 1, 1000, 800);
	myActualManager.modLoadOrder.loadOrder.clear();
	if (createMaster)
		modName.append(".main");
	else
		modName.append(".mod");

	myActualManager.myModHeader.name = modName;
	myActualManager.myModHeader.dependencies = dependencies;
	//for each (std::string var in myActualManager.myModHeader.dependencies)
	//{
	//	loadMods(var);
	//}
	AssetManagerCore::openedMod = modName;
	myActualManager.modLoadOrder.loadOrder.insert(std::pair<Core::String, size_t>(modName, myActualManager.modLoadOrder.loadOrder.size()));
	AssetManagerCore::saveGameDatabase("Data\\" + modName, myActualManager.myModHeader, myActualManager.editorPrefabContainer, myActualManager.EditorAllZones);
	//unloadEditorVariables();
	//AssetManagerCore::loadAllEditorVariables();
	Logger::Info("Successfully created mod [" + modName + "]");
}
void WorldManagerAddon::loadMod(Core::String myMod)
{
	unloadEditorVariables();
	AssetManagerCore::openedMod = myMod;
	myActualManager.modLoadOrder.loadOrder.clear();
	bool fail = false;
	if (!AssetManagerCore::loadModHeader(myMod, myActualManager.myModHeader))
	{
		Logger::Severe("Failed to load mod header for mod [" + myMod +"]");
		AssetManagerCore::openedMod = "<Not Set>";
	}
	else
	{
		for each (Core::String var in myActualManager.myModHeader.dependencies)
		{
			if (loadMods(var))
				fail = true;
		}
	}
	if (fail)
		Logger::Warning("One or more dependency mods failed to load for mod [" + myMod + "]", __FILE__, __LINE__);
	else
		Logger::Fine("Successfully loaded mod dependencies for mod [" + myMod + "]", __FILE__, __LINE__);
	myActualManager.modLoadOrder.loadOrder.insert(std::pair<Core::String, size_t>(myMod, myActualManager.modLoadOrder.loadOrder.size()));
	AssetManagerCore::loadAllEditorVariables();
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
	if (!AssetManagerCore::loadModHeader(mod, modHdr))
		return{};
	else
		return modHdr.dependencies;
}

bool WorldManagerAddon::loadMods(Core::String myMod, bool internal_error)
{
	ModHeader modHdr;
	if (!AssetManagerCore::loadModHeader(myMod, modHdr))
	{
		Logger::Warning("Failed to load [" + myMod + "] as dependency mod", __FILE__, __LINE__);
		internal_error = true;
	}
	else
	{
		//std::cout << "checking: " + myMod + "dependencies" << std::endl;
		for each (Core::String var in modHdr.dependencies)
		{
			if (myActualManager.modLoadOrder.loadOrder.find(var) == myActualManager.modLoadOrder.loadOrder.end())
				internal_error = loadMods(var, internal_error);
			else
				Logger::Info("[" + var + "] already loaded, skipping", __FILE__, __LINE__);
		}
		if (myActualManager.modLoadOrder.loadOrder.find(myMod) == myActualManager.modLoadOrder.loadOrder.end())
		{
			//std::cout << "adding: " + myMod + "to the modLoadOrder" << std::endl;
			myActualManager.modLoadOrder.loadOrder.insert(std::pair<Core::String, size_t>(myMod, myActualManager.modLoadOrder.loadOrder.size()));
		}
		Logger::Fine("[" + myMod + "] successfully loaded" , __FILE__, __LINE__);
	}
	return internal_error;
}
#endif