#ifndef WorldManagerAddons_HPP
#define WorldManagerAddons_HPP

#include <World\WorldManager.hpp>
class WorldManagerAddon
{
	friend class WorldManager;


	std::string getLoadedMod();
	
	std::vector<std::string> getModDependencies(std::string mod);
	void newMod(std::string modName, std::vector<std::string> dependencies);
	std::vector<std::string> loadMod(std::string modName);
	std::string loadMods(std::string modName);
	void EditorAddNewZone(std::string zoneName, std::string background, std::string loadingScreen, std::string loadingScreenMessage, size_t ID, float x, float y);
	void EditorEditZone(std::string zoneName, std::string background, std::string loadingScreen, std::string loadingScreenMessage, size_t ID, float x, float y);
	void EditorLoadZone(std::string zoneName, unsigned int ID);
	void EditorRemoveZone();
	std::string EditorSave();
	//void EditorSetBackground(std::string textureName);
	void EditorSetBackgroundSize(int x, int y);
	std::pair<std::pair<std::string, size_t>, DBZonePrefabStruct> EditorAddGameObjectToZone(Prefab& prefab, GameObject* go);
	void RemoveGameObjectFromZone(GameObject* go);
	
	void EditorFlagGameObjectForEdit(GameObject* go);
	
	//void AddQuest(Quests::Quest quest);
	//void AddItem(Items::Item* item);
	
	friend void LoadAllZones(std::map<std::pair<std::string, unsigned int>, DBZone>& nameOfAllZones);
	//friend void LoadAllPrefabs(PrefabContainer& editorPrefabContainer);
	//friend void LoadAllTextureMaps(SpriterModelContainer& container);
	size_t EditorGetValidID();
	size_t ID = 1;


};



#endif