#include "AOrBObjective.hpp"

namespace Questing
{
	size_t AOrBObjective::checkABState()
	{
		if (a->objectiveState == Enums::QuestState::COMPLETE)
		{
			b->objectiveState = Enums::QuestState::FAILED;
			return completeObjective();
		}
		else if (b->objectiveState == Enums::QuestState::COMPLETE)
		{
			a->objectiveState = Enums::QuestState::FAILED;
			return failObjective();
		}
		if (a->objectiveState == Enums::QuestState::PENDING_COMPLETE ||
			b->objectiveState == Enums::QuestState::PENDING_FAILURE)
		{
			objectiveState = Enums::QuestState::PENDING_COMPLETE;
		}
		else if (b->objectiveState == Enums::QuestState::PENDING_COMPLETE ||
			a->objectiveState == Enums::QuestState::PENDING_FAILURE)
		{
			objectiveState = Enums::QuestState::PENDING_FAILURE;
		}
		else
		{
			objectiveState = Enums::QuestState::ACTIVE;
		}
		return objectiveId;
	}

	void AOrBObjective::activateObjective()
	{
		a->activateObjective();
		b->activateObjective();
		QuestObjective::activateObjective();
	}

	void AOrBObjective::deactivateObjective()
	{
		a->deactivateObjective();
		b->deactivateObjective();
		QuestObjective::deactivateObjective();
	}

	size_t AOrBObjective::onEnemyDefeated(GameObject* go)
	{
		if (isActive())
		{
			a->onEnemyDefeated(go);
			b->onEnemyDefeated(go);
		}
		return checkABState();
	}
	size_t AOrBObjective::onItemPickUp(Items::Base* ib)
	{
		if (isActive())
		{
			a->onItemPickUp(ib);
			b->onItemPickUp(ib);
		}
		return checkABState();
	}
	size_t AOrBObjective::onItemDropped(Items::Base* ib)
	{
		if (isActive())
		{
			a->onItemDropped(ib);
			b->onItemDropped(ib);
		}
		return checkABState();
	}
	void AOrBObjective::resetObjective()
	{
		a->resetObjective();
		b->resetObjective();
		QuestObjective::resetObjective();
	}
	ObjectiveState AOrBObjective::getCurrentState()
	{
		return ObjectiveState{ objectiveState, 0, {a->getCurrentState(), b->getCurrentState()} };
	}
	void AOrBObjective::restoreState(const ObjectiveState& state)
	{
		QuestObjective::restoreState(state);
		a->restoreState(state.recursive[0]);
		b->restoreState(state.recursive[1]);
	}
}

