#include "Quest.hpp"

#include <File/SaveFile.hpp>
#include <File/AssetManagerCore.hpp>

Core::uuid Interfaces::Trait<Questing::Quest>::typeId = Core::uuid("68b5b7cf-7d7e-45b5-be82-0a046efd68a7");

void Questing::Quest::loadStrings()
{
	auto& x = Engine::GetModule<Asset::AssetManager>().getLanguage();
	translatedQuestName = x.getString(questName);
	translatedQuestDescription = x.getString(questDescription);
	translatedQuestLine = x.getString(questLine);
}

Questing::Quest::Quest()
{
}

Questing::Quest::Quest(const Quest& copy) : requireInteractionOnPendingObjectives(copy.requireInteractionOnPendingObjectives),
questName(copy.questName), questDescription(copy.questDescription), questLine(copy.questLine), nextQuest(copy.nextQuest),
nextQuestOnFailure(copy.nextQuestOnFailure), hidden(copy.hidden), questState(copy.questState),
currentObjectiveId(copy.currentObjectiveId), completedStateId(copy.completedStateId), failedStateId(copy.failedStateId),
IRequestable(copy)
{
}

Questing::Quest::Quest(Quest&& copy) noexcept: requireInteractionOnPendingObjectives(copy.requireInteractionOnPendingObjectives),
questName(copy.questName), questDescription(copy.questDescription), questLine(copy.questLine), nextQuest(copy.nextQuest),
nextQuestOnFailure(copy.nextQuestOnFailure), hidden(copy.hidden), questState(copy.questState),
currentObjectiveId(copy.currentObjectiveId), completedStateId(copy.completedStateId), failedStateId(copy.failedStateId),
objectiveMap(std::move(copy.objectiveMap)),
optionalObjectives(std::move(copy.optionalObjectives)),
IRequestable(copy)
{
}

Questing::Quest& Questing::Quest::operator=(const Questing::Quest& copy)
{
	IRequestable::operator=(copy);
	requireInteractionOnPendingObjectives = copy.requireInteractionOnPendingObjectives;

	questName = copy.questName;
	questDescription = copy.questDescription;
	questLine = copy.questLine;

	nextQuest = copy.nextQuest;
	nextQuestOnFailure = copy.nextQuestOnFailure;

	hidden = copy.hidden;
	questState = copy.questState;

	currentObjectiveId = copy.currentObjectiveId;
	completedStateId = copy.completedStateId;
	failedStateId = copy.failedStateId;

	//std::transform(
	//	std::move_iterator(copy.optionalObjectives.begin()),
	//	std::move_iterator(copy.optionalObjectives.end()),
	//	std::back_inserter(optionalObjectives), [](std::pair < size_t, std::unique_ptr<QuestObjective>>&& entry) {return std::move(entry.second);
	//	});

	//objectiveMap = std::move(objectiveMap);
	//optionalObjectives = std::move(optionalObjectives);
	// TODO: insert return statement here
	return *this;
}

void Questing::Quest::failQuest()
{
	questState = Enums::QuestState::FAILED;
	if (nextQuestOnFailure.uuid != Core::uuid::nil())
	{
		//Engine::GetModule<Questing>().startQuest(nextQuestOnFailure);
		// UiPopup that next quest started
	}
	// UiPopup that quest failed
}

void Questing::Quest::completeQuest()
{
	questState = Enums::QuestState::COMPLETE;
	if (nextQuest.uuid != Core::uuid::nil())
	{
		//Engine::GetModule<Questing>().startQuest(nextQuest);
		// UiPopup that next quest started

	}
	// UiPopup that quest completed

}

void Questing::Quest::startQuest()
{
	objectiveMap[currentObjectiveId]->activateObjective();
	questState = Enums::QuestState::ACTIVE;
	Engine::GetModule<File::SaveFile>().setQuestState(getModfile(), getQuestState());
}

void Questing::Quest::updateQuest()
{
	if (currentObjectiveId == completedStateId)
		completeQuest();
	else if (currentObjectiveId == failedStateId)
		failQuest();
	else
		startNextObjectiveIfNotActive();
	Engine::GetModule<File::SaveFile>().setQuestState(getModfile(), getQuestState());
}

void Questing::Quest::startNextObjectiveIfNotActive()
{
	if (objectiveMap.find(currentObjectiveId) != objectiveMap.end() && objectiveMap[currentObjectiveId]->isNotActive())
	{
		objectiveMap[currentObjectiveId]->activateObjective();
		//for (auto& optional : optionalObjectives[currentObjectiveId])
		//{
		//	if (optional->isNotActive())
		//		optional->activateObjective();
		//}
		if (objectiveMap.find(currentObjectiveId) != objectiveMap.end() && objectiveMap[currentObjectiveId]->isCompletedOrFailed() && !(currentObjectiveId == completedStateId || currentObjectiveId == failedStateId))
		{
			// Should fix a lock if the objective is completed as it is started.
			interactWithNpc();
		}
	}
}

void Questing::Quest::resetCurrentObjective()
{
	magic(&Questing::QuestObjective::resetObjective);
}

void Questing::Quest::onEnemyDefeated(GameObject* go)
{
	if (questState == Enums::QuestState::ACTIVE)
	{
		currentObjectiveId = magic(&Questing::QuestObjective::onEnemyDefeated, go);
		updateQuest();
	}
}

void Questing::Quest::onItemDropped(Items::Base* b)
{
	if (questState == Enums::QuestState::ACTIVE)
	{
		currentObjectiveId = magic(&Questing::QuestObjective::onItemDropped, b);
		updateQuest();
	}
}

void Questing::Quest::onItemPicked(Items::Base* b)
{
	if (questState == Enums::QuestState::ACTIVE)
	{
		currentObjectiveId = magic(&Questing::QuestObjective::onItemPickUp, b);
		updateQuest();
	}
}

void Questing::Quest::interactWithNpc()
{
	if (questState == Enums::QuestState::ACTIVE)
	{
		currentObjectiveId = magic<size_t, Questing::QuestObjective, const bool&>(&Questing::QuestObjective::completeOrFailObjective, false);
		updateQuest();
	}
}

void Questing::Quest::updateRequirement()
{
	if (questState == Enums::QuestState::ACTIVE)
	{
		magic(&Questing::QuestObjective::updateObjectiveRequirement);
	}
}


Interfaces::TypeInfo Questing::Quest::getTrait() const
{
	return { Interfaces::Trait<Questing::Quest>::typeId };
}

Questing::QuestState Questing::Quest::getQuestState() const
{
	std::unordered_map<size_t, ObjectiveState> objectives;
	std::unordered_map<size_t, std::vector<ObjectiveState>> bObjectives;
	if (questState == Enums::QuestState::COMPLETE || questState == Enums::QuestState::FAILED)
		return { currentObjectiveId, questState };
	for (auto& x : objectiveMap)
		objectives[x.first] = x.second->getCurrentState();

	for (auto& x : optionalObjectives)
		for (auto& y : x.second)
			if (bObjectives.find(x.first) != bObjectives.end())
				bObjectives[x.first].push_back(y->getCurrentState());
			else
				bObjectives[x.first] = { y->getCurrentState() };
	return { currentObjectiveId, questState, objectives, bObjectives };
}

void Questing::Quest::setQuestState()
{
	auto& saveFile = Engine::GetModule<File::SaveFile>();
	if (saveFile.isQuestStored(getModfile()))
	{
		auto state = saveFile.getQuestState(getModfile());
		currentObjectiveId = state.questStateId;
		questState = state.questState;
		if (questState == Enums::QuestState::COMPLETE || questState == Enums::QuestState::FAILED)
			return;

		for (auto& x : objectiveMap)
			x.second->restoreState(state.objectiveStates.at(x.first));

		for (auto& x : optionalObjectives)
		{
			size_t idx = 0;
			for (auto& y : x.second)
			{
				y->restoreState(state.bonusObjectiveStates.at(x.first)[idx]);
				++idx;
			}
		}
	}
}
