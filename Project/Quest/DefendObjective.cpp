#include "DefendObjective.hpp"

#include <Object/GameObject.hpp>

namespace Questing
{
	size_t DefendObjective::completeOrFailObjective(const bool& forceFail)
	{
		if (!isCompletedOrFailed())
			if (isActive() && completeRequirement && completeRequirement->fullfilled() ||
				isActive() && !completeRequirement)
				return completeObjective();
			else if (isPendingFailure() || forceFail)
				return failObjective();
		return QuestObjective::completeOrFailObjective(forceFail);
	}

	void DefendObjective::activateObjective()
	{
		QuestObjective::activateObjective();
		completeRequirement->start();
	}

	void DefendObjective::deactivateObjective()
	{
		QuestObjective::deactivateObjective();
		completeRequirement->stop();
	}

	size_t DefendObjective::onEnemyDefeated(GameObject* go)
	{
		if (go->id == defend && isActive())
			return failObjective();
		return objectiveId;
	}

	size_t DefendObjective::onItemPickUp(Items::Base* )
	{
		return objectiveId;
	}

	size_t DefendObjective::onItemDropped(Items::Base* )
	{
		return objectiveId;
	}

	void DefendObjective::resetObjective()
	{
		QuestObjective::resetObjective();
		completeRequirement->reset();
	}

	ObjectiveState DefendObjective::getCurrentState()
	{
		return ObjectiveState {objectiveState, 0};
	}

	void DefendObjective::restoreState(const ObjectiveState& state)
	{
		QuestObjective::restoreState(state);
	}
}