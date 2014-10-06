#ifndef ZoneMap_HPP
#define ZoneMap_HPP
#include <string>
#include <vector>
#include "Tile.h"
//#include "Component\BaseComponent.hpp"
#include "Component\GameObject.h"
#include <cereal\access.hpp>
class ZoneMap
{
public:
	ZoneMap();
	std::string name;
	int id;
	std::vector<Tile> backgrounds;
	std::vector<GameObject> objects;
	void addBackground(Tile &t);
	void addGameObject(GameObject &go);

private:
	template<class Archive>
	friend void save(Archive& ar,const ZoneMap & zm);
	template<class Archive>
	friend void load(Archive& ar, ZoneMap & zm);
};

#endif