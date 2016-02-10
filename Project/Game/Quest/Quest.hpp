#ifndef QUEST_HPP
#define QUEST_HPP

#include<vector>
#include "QuestObjective.hpp"

class Quest
{

public:



private:
	std::vector<QuestObjective> objectives;
	bool started;
protected:
	template<class Archive>
	friend void save(Archive& ar, const Quest quest);
	template<class Archive>
	friend void load(Archive& ar, Quest quest);


};

#endif