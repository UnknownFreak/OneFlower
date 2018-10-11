#ifndef CHARACTER_TREE_HPP
#include <map>
#include <Core\String.hpp>

class QuestStages;
class CharacterTree
{

public:
	CharacterTree();

	// character id, the quests it has
	std::map< std::pair < size_t, Core::String>, QuestStages > character_map;


};

class QuestStages
{

};



#endif