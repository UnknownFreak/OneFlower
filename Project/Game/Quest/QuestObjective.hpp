#ifndef	QUESTOBJECTIVE_HPP
#define QUESTOBJECTIVE_HPP

class QuestObjective
{
public:
	//virtual ~QuestObjective();
private:
protected:
#ifdef _DEBUG
public:
#endif
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
	std::pair<std::string,unsigned int> target;

	//The Zone that the player need to reach (Explore or Escort quest only)
	//May add zone requirement for kill quest.
	std::pair<std::string, unsigned int> destination;
	//The destination target inside that zone the player had to reach
	//If not set, player only need to load up the zone.
	std::pair<std::string, unsigned int> targetDestination;

	// The number of times to repeat this.
	size_t count;
	// name of the objective
	std::string objectiveName;
	// description will only be showed in the questLog;
	std::string description;

	Type type;
	ObjectiveState state;

	//If true this will list the objective as a bonus objective.
	bool isBonusObjective;

	// no need for virtual?
	/*virtual void onFail() = 0;
	virtual void onComplete() = 0;
	virtual void onStart() = 0;
	virtual void onUpdate() = 0;
	*/
protected:
	template<class Archive>
	friend void save(Archive& ar, const QuestObjective& quest);
	template<class Archive>
	friend void load(Archive& ar, QuestObjective& quest);
};
#endif