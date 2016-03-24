#ifndef QUEST_HPP
#define QUEST_HPP

#include<vector>
#include "QuestObjective.hpp"

class Quest
{

public:
	// this needed?
	Quest() = default;
	Quest(const Quest& copy) = default;
	Quest& operator=(const Quest& copy) = default;
private:
#ifdef _DEBUG
public:
#endif

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

	std::string title;
	std::string description;
	std::string fromMod;
	// wether this quest is hidden in the questlog or not.
	bool showInQuestLog = true;
	std::vector<QuestObjective> objectives;
	bool started;

	// Item id that are rewarded, and number of items
	std::vector<std::pair<std::pair<std::string,unsigned int>, int>> ItemRewards;
	unsigned int goldReward;
	EditorObjectSaveMode mode = EditorObjectSaveMode::ADD;
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
	friend void save(Archive& ar, const Quest& quest);
	template<class Archive>
	friend void load(Archive& ar, Quest& quest);

};

#endif