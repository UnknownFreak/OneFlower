#ifndef	QUESTOBJECTIVE_HPP
#define QUESTOBJECTIVE_HPP

class QuestObjective
{
public:
	virtual ~QuestObjective();
private:
protected:
	enum Type
	{
		Escort,
		Explore,
		Work,
		Kill,
		Fetch,
	};
	enum ObjectiveState
	{
		NotStarted,
		Uncompleted,
		Completed,
		Failed,

	};
	
	// Quest* myQuest;
	// unsigned int myQuest;


	std::string objectiveName;

	// description will only be showed in the questLog;
	std::string description;

	//QuestObjective id, only unique within the quest it is assigned to.
	unsigned int ID;

	//List of objectives needed to be completed before this can be progressed;
	std::vector<unsigned int>ObjectiveIDBefore;

	short type;
	short state;
	bool canFail;


	// no need for virtual?
	virtual void onFail() = 0;
	virtual void onComplete() = 0;
	virtual void onStart() = 0;
	virtual void onUpdate() = 0;

};
#endif