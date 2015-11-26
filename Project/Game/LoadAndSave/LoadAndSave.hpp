#ifndef LoadAndSave_H
#define LoadAndSave_H

#include "../World/ZoneMaker.hpp"
#include "DatabaseIndex.hpp"
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

//void saveZone(ZoneMap& zone);
void saveInfo(std::map<unsigned int,std::string>zoneInfo);
//void loadItem(unsigned int ID,Item& item);
#endif