#ifndef WorldManagerAddons_HPP
#define WorldManagerAddons_HPP

#include <World\WorldManager.hpp>
class WorldManagerAddon
{
public:
	friend class WorldManager;

	WorldManager& myActualManager;

	WorldManagerAddon();

	Core::String getLoadedMod();
	
	std::vector<Core::String> getModDependencies(Core::String mod);
	std::vector<Core::String> newMod(Core::String modName, std::vector<Core::String> dependencies, bool createMaster);
	std::vector<Core::String> loadMod(Core::String modName);
	Core::String loadMods(Core::String modName);
	void EditorAddNewZone(Core::String zoneName, Core::String background, Core::String loadingScreen, Core::String loadingScreenMessage, size_t ID, float x, float y);
	void EditorEditZone(Core::String zoneName, Core::String background, Core::String loadingScreen, Core::String loadingScreenMessage, size_t ID, float x, float y);
	void EditorLoadZone(Core::String zoneName, unsigned int ID);
	void EditorRemoveZone();
	Core::String EditorSave();
	//void EditorSetBackground(std::string textureName);
	void EditorSetBackgroundSize(int x, int y);
	std::pair<std::pair<Core::String, size_t>, DBZonePrefabStruct> EditorAddGameObjectToZone(Prefab& prefab, GameObject* go);
	void RemoveGameObjectFromZone(GameObject* go);
	
	void EditorFlagGameObjectForEdit(GameObject* go);
	
	//void AddQuest(Quests::Quest quest);
	//void AddItem(Items::Item* item);
	
	friend void LoadAllZones(std::map<std::pair<Core::String, unsigned int>, DBZone>& nameOfAllZones);
	//friend void LoadAllPrefabs(PrefabContainer& editorPrefabContainer);
	//friend void LoadAllTextureMaps(SpriterModelContainer& container);
	size_t EditorGetValidID();
	size_t ID = 1;


};



#endif