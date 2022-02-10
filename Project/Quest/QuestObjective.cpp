#include "QuestObjective.hpp"

#include <File/AssetManagerCore.hpp>

void Questing::QuestObjective::loadTranslations()
{
	auto& x = Engine::GetModule<Asset::AssetManager>().getLanguage();
	translatedObjectiveName = x.getString(objectiveName);
	translatedObjectiveDescription = x.getString(objectiveDescription);
	translatedObjectiveCompleteDescription = x.getString(objectiveCompleteDescription);
}

bool Questing::QuestObjective::isActiveOrPendingComplete() const
{
	return isActive() || isPendingComplete();
}

bool Questing::QuestObjective::isActiveOrPendingFailure() const
{
	return 	isActive() || isPendingFailure();
}

bool Questing::QuestObjective::isActive() const
{
	return objectiveState == Enums::QuestState::ACTIVE;
}

bool Questing::QuestObjective::isNotActive() const
{
	return objectiveState == Enums::QuestState::NOT_ACTIVE;
}

bool Questing::QuestObjective::isPendingComplete() const
{
	return objectiveState == Enums::QuestState::PENDING_COMPLETE;
}

bool Questing::QuestObjective::isPendingFailure() const
{
	return objectiveState == Enums::QuestState::PENDING_FAILURE;
}

bool Questing::QuestObjective::isCompletedOrFailed() const
{
	return isCompleted() || isFailed();
}

bool Questing::QuestObjective::isCompleted() const
{
	return objectiveState == Enums::QuestState::COMPLETE;
}

bool Questing::QuestObjective::isFailed() const
{
	return objectiveState == Enums::QuestState::FAILED;
}

void Questing::QuestObjective::activateObjective()
{
	if (activationRequirement && activationRequirement->fullfilled() && isNotActive())
	{
		activationRequirement->start();
		objectiveState = Enums::QuestState::ACTIVE;
	}
	else if (activationRequirement == nullptr && isNotActive())
	{
		objectiveState = Enums::QuestState::ACTIVE;
	}
}

void Questing::QuestObjective::deactivateObjective()
{
	if (activationRequirement && !activationRequirement->fullfilled() && isActive())
	{
		if(failOnRequirmentUnfulfilled)
			objectiveState = Enums::QuestState::PENDING_FAILURE;
		else
			objectiveState = Enums::QuestState::NOT_ACTIVE;
		activationRequirement->stop();
	}
}

size_t Questing::QuestObjective::completeObjective()
{
	objectiveState = Enums::QuestState::COMPLETE;
	if(activationRequirement)
		activationRequirement->stop();
	return nextQuestObjectiveStateId;
}

size_t Questing::QuestObjective::failObjective()
{
	objectiveState = Enums::QuestState::FAILED;
	if (activationRequirement)
		activationRequirement->stop();
	return failedObjectiveStateId;
}

size_t Questing::QuestObjective::completeOrFailObjective(const bool& forceFail)
{
	if (! isCompletedOrFailed())
		if (isPendingComplete())
			return completeObjective();
		else if (isPendingFailure() || forceFail)
			return failObjective();
		return objectiveId;
}

void Questing::QuestObjective::updateObjectiveRequirement()
{
	if (activationRequirement)
	{
		if (activationRequirement->fullfilled() && isNotActive())
		{
			objectiveState = Enums::QuestState::ACTIVE;
		}
		if (activationRequirement && !activationRequirement->fullfilled() && isActive())
		{
			if (failOnRequirmentUnfulfilled)
				objectiveState = Enums::QuestState::PENDING_FAILURE;
			else
				objectiveState = Enums::QuestState::NOT_ACTIVE;
		}
	}
}

void Questing::QuestObjective::resetObjective()
{
	if (activationRequirement)
	{
		activationRequirement->stop();
		activationRequirement->reset();
	}
	objectiveState = Enums::QuestState::NOT_ACTIVE;
	activateObjective();
}

void Questing::QuestObjective::restoreState(const ObjectiveState& state)
{
	objectiveState = state.state;
}
