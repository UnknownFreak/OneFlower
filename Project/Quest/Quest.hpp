#ifndef Quest_HPP
#define Quest_HPP

#include <cereal/cereal.hpp>

#include <Helpers/Enum/QuestState.hpp>
#include "QuestObjective.hpp"
#include "QuestState.hpp"

#include <file/archive/Requestable.hpp>
#include <utils/common/string.hpp>

#include <unordered_map>

namespace Questing
{
	class Quest : public of::file::archive::Requestable
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

		of::common::uuid questName;
		of::common::uuid questDescription;
		of::common::uuid questLine;

		of::file::FileId nextQuest;
		of::file::FileId nextQuestOnFailure;

		of::common::String translatedQuestName;
		of::common::String translatedQuestDescription;
		of::common::String translatedQuestLine;

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

		void onEnemyDefeated(of::object::GameObject* go);
		void onItemDropped(Items::Base* b);
		void onItemPicked(Items::Base* b);
		void interactWithNpc();
		void updateRequirement();

		virtual of::file::archive::TypeInfo getTrait() const override;

		Questing::QuestState getQuestState() const;
		void setQuestState();

		template <class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::base_class<Requestable>(this));
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
			ar(cereal::base_class<Requestable>(this));
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
CEREAL_REGISTER_TYPE(Questing::Quest);
CEREAL_REGISTER_POLYMORPHIC_RELATION(of::file::archive::Requestable, Questing::Quest);
#endif