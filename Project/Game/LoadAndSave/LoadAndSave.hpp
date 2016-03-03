#ifndef LoadAndSave_H
#define LoadAndSave_H

#include "../World/DBZone.hpp"
#include "DatabaseIndex.hpp"
#include "PrefabContainer.hpp"
#include "../LoadAndSave/ModHeader.hpp"
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
bool loadModHeader(std::string modName, ModHeader& myheader);


template<class Archive>
void saveItem(Archive & ar, Item* item);
template<class Archive>
void loadItem(Archive & ar, Item*& item);

#ifdef _DEBUG
void saveGameDatabase(std::string filename,ModHeader& modhdr ,PrefabContainer& prefabs, std::map<std::pair<std::string,size_t>, DBZone>& EditorAllZones, std::map<unsigned int, Item*>& editorAllItems);
#endif
void saveInfo(std::map<unsigned int,std::string>zoneInfo);
//void loadItem(unsigned int ID,Item& item);

#endif