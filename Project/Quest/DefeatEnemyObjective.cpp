#include "DefeatEnemyObjective.hpp"

#include <Object/GameObject.hpp>

namespace Questing
{
	size_t DefeatEnemyObjective::onEnemyDefeated(GameObject* go)
	{
		if (isActive() && (go->id == enemy || go->tag == tag))
		{
			currentDefeatCount++;
		}
		if (defeatCount == currentDefeatCount)
		{
			if (completeOnPendingComplete)
				return completeObjective();
			else
				objectiveState = Enums::QuestState::PENDING_COMPLETE;
		}
		return objectiveId;
	}

	size_t DefeatEnemyObjective::onItemPickUp(Items::Base*)
	{
		return objectiveId;
	}

	size_t DefeatEnemyObjective::onItemDropped(Items::Base*)
	{
		return objectiveId;
	}

	void DefeatEnemyObjective::resetObjective()
	{
		QuestObjective::resetObjective();
		currentDefeatCount = 0;
	}

	ObjectiveState DefeatEnemyObjective::getCurrentState()
	{
		return ObjectiveState{objectiveState, currentDefeatCount};
	}

	void DefeatEnemyObjective::restoreState(const ObjectiveState& state)
	{
		QuestObjective::restoreState(state);
		currentDefeatCount = state.unit;
	}
}
