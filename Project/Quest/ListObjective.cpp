#include "ListObjective.hpp"

namespace Questing
{
	size_t ListObjective::recalculateList()
	{
		bool fail = false;
		bool pending_fail = false;
		size_t pending_complete = 0;
		size_t is_complete = 0;
		for (auto& i : list)
		{
			if (fail)
				i->failObjective();
			if (i->isFailed())
				fail = true;
			else if (i->isPendingFailure())
				pending_fail = true;
			else if (i->isCompleted())
			{
				pending_complete++;
				is_complete++;
			}
			else if (i->isPendingComplete())
				pending_complete++;

		}
		if (fail)
			return failObjective();

		bool complete = is_complete == list.size();

		if (pending_fail)
		{
			objectiveState = Enums::QuestState::PENDING_FAILURE;
		}
		else if (pending_complete == list.size() || complete)
		{
			objectiveState = Enums::QuestState::PENDING_COMPLETE;
			if (completeOnPendingComplete || complete)
			{
				return completeObjective();
			}
		}
		else
			objectiveState = Enums::QuestState::ACTIVE;

		return objectiveId;
	}
	void ListObjective::activateObjective()
	{
		for (auto& i : list)
		{
			i->activateObjective();
		}
		QuestObjective::activateObjective();
	}
	void ListObjective::deactivateObjective()
	{
		for (auto& i : list)
		{
			i->deactivateObjective();
		}
		QuestObjective::deactivateObjective();
	}
	size_t ListObjective::onEnemyDefeated(of::object::GameObject* go)
	{
		for (auto& i : list)
		{
			i->onEnemyDefeated(go);
		}
		return recalculateList();
	}
	size_t ListObjective::onItemPickUp(Items::Base* b)
	{
		for (auto& i : list)
		{
			i->onItemPickUp(b);
		}
		return recalculateList();
	}
	size_t ListObjective::onItemDropped(Items::Base* b)
	{
		for (auto& i : list)
		{
			i->onItemDropped(b);
		}
		return recalculateList();
	}
	void ListObjective::resetObjective()
	{
		QuestObjective::resetObjective();
		for (auto& it : list)
			it->resetObjective();
	}
	ObjectiveState ListObjective::getCurrentState()
	{
		std::vector<ObjectiveState> subStates;
		for (auto& i : list)
			subStates.push_back(i->getCurrentState());
		return ObjectiveState {objectiveState, 0, subStates};
	}

	void ListObjective::restoreState(const ObjectiveState& state)
	{
		QuestObjective::restoreState(state);
		size_t idx = 0;
		for (auto& i : list)
		{
			i->restoreState(state.recursive[idx]);
			++idx;
		}
	}
}