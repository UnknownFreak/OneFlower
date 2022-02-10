#ifndef Quest_HPP
#define Quest_HPP

#include <Helpers/Enum/QuestState.hpp>
#include "QuestObjective.hpp"
#include "QuestState.hpp"

#include <Interfaces/IRequestable.hpp>
#include <Helpers/String.hpp>

#include <unordered_map>

namespace Questing
{
	class Quest : public Interfaces::IRequestable
	{
		template<class U = size_t, class Tc, class ...Targs>
		U magic(U(Tc::* fn)(Targs...), Targs...args)
		{
			for (auto& optional : optionalObjectives[currentObjectiveId])
			{
				(optional.get()->*fn)(args...);
				if (!requireInteractionOnPendingObjectives)
					optional->completeOrFailObjective();
			}
			return (objectiveMap[currentObjectiveId].get()->*fn)(args...);
		}
		void loadStrings();
	public:

		bool requireInteractionOnPendingObjectives;

		Core::uuid questName;
		Core::uuid questDescription;
		Core::uuid questLine;

		ModFileUUIDHelper nextQuest;
		ModFileUUIDHelper nextQuestOnFailure;

		Core::String translatedQuestName;
		Core::String translatedQuestDescription;
		Core::String translatedQuestLine;

		bool hidden;
		Enums::QuestState questState;

		size_t currentObjectiveId = 0;
		size_t completedStateId = 0;
		size_t failedStateId = 0;
		std::unordered_map<size_t, std::unique_ptr<QuestObjective>> objectiveMap;
		std::unordered_map<size_t, std::vector<std::unique_ptr<QuestObjective>>> optionalObjectives;

		Quest();
		Quest(const Quest& copy);
		Quest(Quest&& copy) noexcept;
		Quest& operator= (const Quest &);

		void failQuest();
		void completeQuest();

		void startQuest();
		void updateQuest();
		void startNextObjectiveIfNotActive();
		void resetCurrentObjective();

		void onEnemyDefeated(GameObject* go);
		void onItemDropped(Items::Base* b);
		void onItemPicked(Items::Base* b);
		void interactWithNpc();
		void updateRequirement();

		virtual Interfaces::TypeInfo getTrait() const override;

		Questing::QuestState getQuestState() const;
		void setQuestState();

		template <class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::base_class<Interfaces::IRequestable>(this));
			ar(requireInteractionOnPendingObjectives);
			ar(questName);
			ar(questDescription);
			ar(questLine);
			ar(nextQuest);
			ar(nextQuestOnFailure);
			ar(hidden);
			ar(questState);
			ar(currentObjectiveId);
			ar(completedStateId);
			ar(failedStateId);
			ar(objectiveMap);
			ar(optionalObjectives);
		}

		template <class Archive>
		void load(Archive& ar)
		{
			ar(cereal::base_class<Interfaces::IRequestable>(this));
			ar(requireInteractionOnPendingObjectives);
			ar(questName);
			ar(questDescription);
			ar(questLine);
			ar(nextQuest);
			ar(nextQuestOnFailure);
			ar(hidden);
			ar(questState);
			ar(currentObjectiveId);
			ar(completedStateId);
			ar(failedStateId);
			ar(objectiveMap);
			ar(optionalObjectives);
			loadStrings();
			setQuestState();
		}
	};
}

#endif