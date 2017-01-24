#include "WorldManagerAddons.hpp"
#include <AssetManager\AssetManagerCore.hpp>
#include <AssetManager\Database\DBZone.hpp>
#include <World\WorldCore.hpp>
#include <Core\Component\TransformComponent.hpp>
#include <Core\Component\GameObject.h>
#include <World\Zone.hpp>
#ifdef _DEBUG
void WorldManagerAddon::EditorAddNewZone(std::string zoneName, std::string background, std::string loadingScreen, std::string loadingScreenMessage, size_t ID, float x, float y)
{

	DBZone myDbZone;
	myDbZone.name = zoneName;
	myDbZone.fromMod = AssetManagerCore::openedMod;
	myDbZone.ID = ID;
	myDbZone.background.name = background;
	myDbZone.background.position = Vector2(0, 0);
	myDbZone.background.size.x = x;
	myDbZone.background.size.y = y;
	//myDbZone.background = DBBackgroundSprite(background, 0, 0);

	myDbZone.loadingScreen.name = loadingScreen;
	myDbZone.loadingScreenMessage = loadingScreenMessage;

	if (zoneName == "Tutorial" && ID == 1)
	{
		myDbZone.fromMod = "Tutorial";
		Engine::World.EditorAllZones.insert(std::pair<std::pair<std::string, size_t>, DBZone>(std::pair<std::string, size_t>("Tutorial", ID), myDbZone));
	}
	else
		Engine::World.EditorAllZones.insert(std::pair<std::pair<std::string, size_t>, DBZone>(std::pair<std::string, size_t>(AssetManagerCore::openedMod, ID), myDbZone));
}
void WorldManagerAddon::EditorEditZone(std::string zoneName, std::string background, std::string loadingScreen, std::string loadingScreenMessage, size_t ID, float x, float y)
{
	Engine::World.EditorAllZones[Engine::World.lastLoadedZone].mode = ObjectSaveMode::EDIT;
	Engine::World.EditorAllZones[Engine::World.lastLoadedZone].name = zoneName;
	Engine::World.EditorAllZones[Engine::World.lastLoadedZone].ID = ID;
	Engine::World.EditorAllZones[Engine::World.lastLoadedZone].background.name = background;
	Engine::World.EditorAllZones[Engine::World.lastLoadedZone].background.size.x = x;
	Engine::World.EditorAllZones[Engine::World.lastLoadedZone].background.size.y = y;

	Engine::World.EditorAllZones[Engine::World.lastLoadedZone].loadingScreen.name = loadingScreen;
	Engine::World.EditorAllZones[Engine::World.lastLoadedZone].loadingScreen.position.x = 0;
	Engine::World.EditorAllZones[Engine::World.lastLoadedZone].loadingScreen.position.y = 0;
	Engine::World.EditorAllZones[Engine::World.lastLoadedZone].loadingScreenMessage = loadingScreenMessage;
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
void WorldManagerAddon::EditorLoadZone(std::string name, unsigned int ID)
{
	//*change this with listview instead?//*/
	if (Engine::World.EditorAllZones.find(std::pair<std::string, size_t>(name, ID)) != Engine::World.EditorAllZones.end())
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
std::string WorldManagerAddon::EditorSave()
{
	if (AssetManagerCore::openedMod != "<Not Set>")
	{
		for (std::map<std::pair<std::string, size_t>, DBZonePrefabStruct>::iterator
			i = Engine::World.EditorAllZones[Engine::World.lastLoadedZone].prefabList.begin(); i != Engine::World.EditorAllZones[Engine::World.lastLoadedZone].prefabList.end(); i++)
		{
			i->second.position = Engine::World.listOfZoneObjects[i->first]->GetComponent<Component::TransformComponent>()->position;
		}
		//saveGameDatabase(getLoadedMod(), myModHeader, editorPrefabContainer, EditorAllZones, EditorAllItems, EditorAllQuests);
	}
	return AssetManagerCore::openedMod;
}
std::pair<std::pair<std::string, size_t>, DBZonePrefabStruct> WorldManagerAddon::EditorAddGameObjectToZone(Prefab& prefab, GameObject* go)
{
	DBZonePrefabStruct dbzps;
	dbzps.ID = prefab.ID;
	dbzps.fromMod = prefab.fromMod;
	dbzps.position = go->GetComponent<Component::TransformComponent>()->position;
	dbzps.oldPosition = dbzps.position;
	dbzps.prefabName = prefab.name;
	size_t ValidID = EditorGetValidID();
	Engine::World.EditorAllZones[Engine::World.lastLoadedZone].mode = ObjectSaveMode::EDIT;
	Engine::World.EditorAllZones[Engine::World.lastLoadedZone].prefabList.insert(std::pair<std::pair<std::string, size_t>, DBZonePrefabStruct>(std::pair<std::string, size_t>(AssetManagerCore::openedMod, ValidID), dbzps));
	Engine::World.getCurrentZone()->objects.push_back(std::pair<std::pair<std::string, size_t>, GameObject*>(std::pair<std::string, size_t>(AssetManagerCore::openedMod, ValidID), go));
	Engine::World.listOfZoneObjects.insert(std::pair<std::pair<std::string, size_t>, GameObject*>(std::pair<std::string, size_t>(AssetManagerCore::openedMod, ValidID), go));

	return std::pair<std::pair<std::string, size_t>, DBZonePrefabStruct>(std::pair<std::string, size_t>(AssetManagerCore::openedMod, ValidID), dbzps);
}
size_t WorldManagerAddon::EditorGetValidID()
{
	while (Engine::World.listOfZoneObjects.find(std::pair<std::string, size_t>(AssetManagerCore::openedMod, ID)) != Engine::World.listOfZoneObjects.end())
	{
		ID++;
	}
	return ID;
}
//void WorldManager::EditorSetBackground(std::string name)
//{
//	currentZone->setBackground(name);
//	Engine::game.addSprite(currentZone->getBackground(), true);
//}
//void WorldManager::EditorSetBackgroundSize(int x, int y)
//{
//	currentZone->getBackground()->size.x = x;
//	currentZone->getBackground()->size.y = y;
//	Engine::game.addSprite(currentZone->getBackground(), true);
//}
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
//std::string WorldManager::getLoadedMod()
//{
//	return openedMod;
//}
//void WorldManager::newMod(std::string modName, std::vector<std::string> dependencies)
//{
//	modLoadOrder.loadOrder.clear();
//	myModHeader.name = modName;
//	myModHeader.dependencies = dependencies;
//	for each (std::string var in myModHeader.dependencies)
//	{
//		loadMods(var);
//	}
//	openedMod = modName;
//	modLoadOrder.loadOrder.insert(std::pair<std::string, size_t>(modName, modLoadOrder.loadOrder.size()));
//	LoadAllEditorVariables();
//}
//std::vector<std::string> WorldManager::loadMod(std::string myMod)
//{
//	std::vector<std::string> myFailed;
//	openedMod = myMod;
//	modLoadOrder.loadOrder.clear();
//	if (!loadModHeader(myMod, myModHeader))
//	{
//		myFailed.push_back("Error loading Mod!");
//		openedMod = "<Not Set>";
//	}
//	else
//	{
//		for each (std::string var in myModHeader.dependencies)
//		{
//			std::string myReturn = loadMods(var);
//			if (myReturn != "<Fine>")
//				myFailed.push_back(myReturn);
//		}
//	}
//	modLoadOrder.loadOrder.insert(std::pair<std::string, size_t>(myMod, modLoadOrder.loadOrder.size()));
//	std::cout << "Mod loaded in this order\n";
//	for each (auto it in modLoadOrder.loadOrder)
//		std::cout << it.first << " - " << it.second << "\n";
//	LoadAllEditorVariables();
//	return myFailed;
//}
//void WorldManager::LoadAllEditorVariables()
//{
//	//LoadAllTextureMaps(Engine::ModelContainer);
//	LoadAllZones(EditorAllZones);
//	LoadAllPrefabs(editorPrefabContainer);
//	//LoadAllItems(EditorAllItems);
//	//LoadAllQuests(EditorAllQuests);
//}
//std::vector<std::string> WorldManager::getModDependencies(std::string mod)
//{
//	ModHeader modHdr;
//	if (!loadModHeader(mod, modHdr))
//	{
//		return{};
//	}
//	else
//	{
//		return modHdr.dependencies;
//	}
//}
//std::string WorldManager::loadMods(std::string myMod)
//{
//	ModHeader modHdr;
//	if (!AssetManagerCore::loadModHeader(myMod, modHdr))
//	{
//		return "Failed to load dependency mod: " + myMod;
//	}
//	else
//	{
//		//std::cout << "checking: " + myMod + "dependencies" << std::endl;
//		for each (std::string var in modHdr.dependencies)
//		{
//			loadMods(var);
//		}
//		if (modLoadOrder.loadOrder.find(myMod) == modLoadOrder.loadOrder.end())
//		{
//			//std::cout << "adding: " + myMod + "to the modLoadOrder" << std::endl;
//			modLoadOrder.loadOrder.insert(std::pair<std::string, size_t>(myMod, modLoadOrder.loadOrder.size()));
//		}
//	}
//	return "<Fine>";
//}
#endif