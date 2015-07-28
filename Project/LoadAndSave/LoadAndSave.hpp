#ifndef LoadAndSave_H
#define LoadAndSave_H

#include "../ZoneMaker.hpp"

class Item;
void testLoad();// (Archive& archive, const GameObject& go);
void testSave();// (Archive& archive, const GameObject& go);
void saveZone(ZoneMap& zone);
void saveInfo(std::map<unsigned int,std::string>zoneInfo);
void loadItem(unsigned int ID, Item& item);
#endif