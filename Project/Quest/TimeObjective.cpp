#include "TimeObjective.hpp"

namespace Questing
{
	size_t TimeObjective::onEnemyDefeated(GameObject* )
	{
		return objectiveId;
	}
	size_t TimeObjective::onItemPickUp(Items::Base* )
	{
		return objectiveId;
	}
	size_t TimeObjective::onItemDropped(Items::Base* )
	{
		return objectiveId;
	}
	ObjectiveState TimeObjective::getCurrentState()
	{
		return ObjectiveState{objectiveState};
	}
	void TimeObjective::restoreState(const ObjectiveState& state)
	{
		QuestObjective::restoreState(state);
		if (objectiveState == Enums::QuestState::ACTIVE)
		{
			timeToSurvive.start();
		}
	}
	size_t TimeObjective::completeObjective()
	{
		timeToSurvive.stop();
		return QuestObjective::completeObjective();
	}
	size_t TimeObjective::failObjective()
	{
		timeToSurvive.stop();
		return QuestObjective::failObjective();
	}
	void TimeObjective::activateObjective()
	{
		QuestObjective::activateObjective();
		timeToSurvive.start();
	}
	void TimeObjective::deactivateObjective()
	{
		QuestObjective::deactivateObjective();
		timeToSurvive.stop();
	}
	void TimeObjective::resetObjective()
	{
		QuestObjective::resetObjective();
		timeToSurvive.stop();
		timeToSurvive.reset();
	}
	void TimeObjective::updateObjectiveRequirement()
	{
		QuestObjective::updateObjectiveRequirement();
		if (timeToSurvive.fullfilled())
		{
			objectiveState = fullfilledState;
		}
		else
		{
			objectiveState = Enums::QuestState::ACTIVE;
		}

	}
}