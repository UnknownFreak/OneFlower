#include "DuelObjective.hpp"

#include <Object/GameObject.hpp>

namespace Questing
{
	size_t DuelObjective::completeOrFailObjective(const bool& forceFail)
	{
		if (!isCompletedOrFailed())
			if (isActive())
				return completeObjective();
			else if (isPendingFailure() || forceFail)
				return failObjective();
		return QuestObjective::completeOrFailObjective(forceFail);
	}

	size_t DuelObjective::onEnemyDefeated(GameObject* go)
	{
		if (go->id == duel && isActive())
			return completeObjective();
		return objectiveId;
	}

	size_t DuelObjective::onItemPickUp(Items::Base*)
	{
		return objectiveId;
	}

	size_t DuelObjective::onItemDropped(Items::Base*)
	{
		return objectiveId;
	}

	ObjectiveState DuelObjective::getCurrentState()
	{
		return ObjectiveState {objectiveState};
	}

	void DuelObjective::restoreState(const ObjectiveState& state)
	{
		QuestObjective::restoreState(state);
	}
}
