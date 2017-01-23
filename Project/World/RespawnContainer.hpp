#ifndef RESPAWNCONTAINER_HPP
#define RESPAWNCONTAINER_HPP
#include <vector>

class RespawnContainer
{
	//<zone, typeid, timerToSpawn>
public:
	RespawnContainer() = default;
	std::vector<std::pair<unsigned int, unsigned int/*for now*/>> respawnTable;
private:
	template<class Archive>
	friend void load(Archive&ar, RespawnContainer &rc);
	template<class Archive>
	friend void save(Archive&ar, const RespawnContainer &rc);
};

#endif