#ifndef LoadAndSave_H
#define LoadAndSave_H

#include "../ZoneMaker.hpp"
void testLoad();// (Archive& archive, const GameObject& go);
void testSave();// (Archive& archive, const GameObject& go);
void saveZone(ZoneMap& zone);
void saveInfo(std::map<unsigned int,std::string>zoneInfo);

#endif