#ifndef LoadAndSave_H
#define LoadAndSave_H

#include "../World/DBZone.hpp"
#include "DatabaseIndex.hpp"
#include "PrefabContainer.hpp"
class Item;
void testLoad();// (Archive& archive, const GameObject& go);
void testSave();// (Archive& archive, const GameObject& go);
// Test for new data structure
void databaseTestSave();
void databaseTestLoad();
void databaseTestAdd();
void databaseTestRemove();
// End

void saveGame(GameObject& player, std::string saveFile);
void loadGame(GameObject& player, std::string loadFile);

template<class Archive>
void saveItem(Archive & ar, Item* item);
template<class Archive>
void loadItem(Archive & ar, Item*& item);

#ifdef _DEBUG
void saveGameDatabase(std::string filename, PrefabContainer& prefabs, std::map<unsigned int, DBZone>& EditorAllZones, std::map<unsigned int, Item*>& editorAllItems);
#endif
void saveInfo(std::map<unsigned int,std::string>zoneInfo);
//void loadItem(unsigned int ID,Item& item);

#endif