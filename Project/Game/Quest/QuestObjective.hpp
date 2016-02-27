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
	
	//The Target ID
	size_t target;
	// The number of times to repeat this.
	size_t count;
	// name of the objective
	std::string objectiveName;
	// description will only be showed in the questLog;
	std::string description;

	//List of objectives needed to be completed before this can be progressed;
	std::vector<unsigned int>ObjectiveIDBefore;

	short type;
	short state;

	//If true this will list the objective as a bonus objective.
	bool isBonusObjective;

	// no need for virtual?
	virtual void onFail() = 0;
	virtual void onComplete() = 0;
	virtual void onStart() = 0;
	virtual void onUpdate() = 0;

};
#endif