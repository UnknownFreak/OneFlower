#ifndef QuestObjective_HPP
#define QuestObjective_HPP

#include <File/Mod/ModFileUUIDHelper.hpp>
#include <Requirement/Requirement.hpp>

#include <Helpers/Enum/QuestState.hpp>

#include <Helpers/uuid.hpp>
#include <Helpers/String.hpp>
#include "ObjectiveState.hpp"

class GameObject;

namespace Items
{
	class Base;
}

namespace Questing
{

	class QuestObjective
	{
		void loadTranslations();
	public:
		bool isActiveOrPendingComplete() const;
		bool isActiveOrPendingFailure() const;
		bool isActive() const;
		bool isNotActive() const;
		bool isPendingComplete() const;
		bool isPendingFailure() const;
		bool isCompletedOrFailed() const;
		bool isCompleted() const;
		bool isFailed() const;

	public:

		inline virtual ~QuestObjective() {};

		bool completeOnPendingComplete;
		bool failOnRequirmentUnfulfilled;
		// only applies to optional objectives
		bool hidden;

		size_t objectiveId;
		size_t failedObjectiveStateId;
		size_t nextQuestObjectiveStateId;

		Core::uuid objectiveName;
		Core::uuid objectiveDescription;
		Core::uuid objectiveCompleteDescription;

		std::unique_ptr<Requirement::Requirement> activationRequirement;

		Core::String translatedObjectiveName;
		Core::String translatedObjectiveDescription;
		Core::String translatedObjectiveCompleteDescription;

		Enums::QuestState objectiveState = Enums::QuestState::NOT_ACTIVE;

		virtual size_t onEnemyDefeated(GameObject* go) = 0;
		virtual size_t onItemPickUp(Items::Base* b) = 0;
		virtual size_t onItemDropped(Items::Base* b) = 0;
		virtual void activateObjective();
		virtual void deactivateObjective();
		virtual size_t completeObjective();
		virtual size_t failObjective();
		virtual size_t completeOrFailObjective(const bool& forceFail=false);
		virtual void updateObjectiveRequirement();
		virtual void resetObjective();

		virtual ObjectiveState getCurrentState() = 0;
		virtual void restoreState(const ObjectiveState& state);

		template <class Archive>
		void save(Archive& ar) const
		{
			ar(completeOnPendingComplete);
			ar(hidden);
			ar(objectiveId);
			ar(failedObjectiveStateId);
			ar(nextQuestObjectiveStateId);
			ar(objectiveName);
			ar(objectiveDescription);
			ar(objectiveCompleteDescription);
			ar(objectiveState);
			ar(activationRequirement);
		}
		template <class Archive>
		void load(Archive& ar)
		{
			ar(completeOnPendingComplete);
			ar(hidden);
			ar(objectiveId);
			ar(failedObjectiveStateId);
			ar(nextQuestObjectiveStateId); 
			ar(objectiveName);
			ar(objectiveDescription);
			ar(objectiveCompleteDescription);
			ar(objectiveState);
			ar(activationRequirement);
			loadTranslations();
		}
	};
}

#endif