#ifndef LoadAndSave_H
#define LoadAndSave_H

#include "../World/DBZone.hpp"
#include "DatabaseIndex.hpp"
#include "PrefabContainer.hpp"
#include "../LoadAndSave/ModHeader.hpp"
#include "../Quest/Quest.hpp"
class Item;
void testLoad();// (Archive& archive, const GameObject& go);
void testSave();// (Archive& archive, const GameObject& go);

void saveGame(GameObject& player, std::string saveFile);
void loadGame(GameObject& player, std::string loadFile);
bool loadModHeader(std::string modName, ModHeader& myheader);


template<class Archive>
void saveItem(Archive & ar, Item* item);
template<class Archive>
void loadItem(Archive & ar, Item*& item);


#ifdef _DEBUG
void saveGameDatabase(
	std::string filename, ModHeader& modhdr,
	PrefabContainer& prefabs,
	std::map<std::pair<std::string, size_t>, DBZone>& EditorAllZones,
	std::map<std::pair<std::string, size_t>, Item*>& editorAllItems,
	std::map<std::pair<std::string,size_t>,Quest>& EditorAllQuests);
#endif
//void loadItem(unsigned int ID,Item& item);

#endif