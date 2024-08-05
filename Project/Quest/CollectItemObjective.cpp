#include "CollectItemObjective.hpp"

#include <Items/Item.hpp>

#include <file/SaveFile.hpp>

#include <Items/Inventory.hpp>

namespace Questing
{
	void CollectItemObjective::activateObjective()
	{
		QuestObjective::activateObjective();
		if (objectiveState == Enums::QuestState::ACTIVE)
		{
			// TODO: change to objectInstanceHandler instead
			auto& player = of::engine::GetModule<of::file::SaveFile>().player;
			auto inventory = player->get<of::component::Inventory>();
			if (inventory)
			{
				if (inventory->getItemStack(itemId) >= itemCount)
				{
					if (completeOnPendingComplete)
						completeObjective();
					objectiveState = Enums::QuestState::PENDING_COMPLETE;
				}
			}
		}
	}
	size_t CollectItemObjective::onEnemyDefeated(of::object::GameObject*)
	{
		return objectiveId;
	}

	size_t CollectItemObjective::onItemPickUp(Items::Base* b)
	{
		if (isActiveOrPendingComplete())
		{
			if (itemId == b->getModfile() && b->stackSize >= itemCount)
			{
				if (completeOnPendingComplete)
					return completeObjective();
				objectiveState = Enums::QuestState::PENDING_COMPLETE;
			}
		}
		return objectiveId;
	}

	size_t CollectItemObjective::onItemDropped(Items::Base* b)
	{
		if (isActiveOrPendingComplete())
		{
			if (itemId == b->getModfile() && b->stackSize < itemCount)
				objectiveState = Enums::QuestState::ACTIVE;
		}
		return objectiveId;
	}

	ObjectiveState CollectItemObjective::getCurrentState()
	{
		return ObjectiveState{objectiveState, 0};
	}

	void CollectItemObjective::restoreState(const ObjectiveState& state)
	{
		QuestObjective::restoreState(state);
	}
}