#ifndef QUEST_HPP
#define QUEST_HPP

#include<vector>
#include "QuestObjective.hpp"

class Quest
{

public:

private:
	

	enum QuestType
	{
		Combat,
		NoCombat,
		//Mixed,?
	};
	enum QuestState
	{
		NotStarted,
		Started,
		Completed,
		Failed,
	};

	unsigned int ID;

	// When completed it unlocks these quests.
	std::vector<unsigned int> UnlocksQuest;

	// When completed it starts these quests.
	std::vector<unsigned int> StartsQuest;
	std::string title;
	std::string description;
	
	// wether this quest is hidden in the questlog or not.
	bool showInQuestLog;
	std::vector<QuestObjective> objectives;
	bool started;

	// Item id that are rewarded, and number of items
	std::vector<std::pair<unsigned int, int>> ItemRewards;
	unsigned int goldReward;
	/*
	
	// probably use a ID instead of class instance or pointer so we can get 
	// that from list of factions, can also be NULL to not add any reputation.
	Faction factionToGiveReputation;
	Faction factionToRemoveReputation;

	// will probably be the same for most tasks
	size_t reputationToRemove;
	size_t reputationToAdd;
	
	
	*/


protected:
	template<class Archive>
	friend void save(Archive& ar, const Quest quest);
	template<class Archive>
	friend void load(Archive& ar, Quest quest);

};

#endif