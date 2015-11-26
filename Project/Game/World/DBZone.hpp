#ifndef DBZONE_HPP
#define DBZONE_HPP
#include <vector>
#include "../Tile.h"

class DBZone
{
public:
	unsigned int ID;
	std::string name;
	Tile background;

	std::vector<std::pair<size_t, Vector2>> prefabList;
#ifdef _DEBUG
	bool isRemoved = false;
#endif
private:
#ifdef _DEBUG
	template<class T>
	friend void save(T& ar, const DBZone& dbz);
#endif
	template<class T>
	friend void load(T& ar, DBZone& dbz);

};

#endif