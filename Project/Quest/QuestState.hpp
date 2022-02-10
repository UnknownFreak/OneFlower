#ifndef QuestStateContainer_HPP
#define  QuestStateContainer_HPP

#include <unordered_map>
#include <Helpers/Enum/QuestState.hpp>
#include "ObjectiveState.hpp"

namespace Questing
{
	struct QuestState
	{

		size_t questStateId;
		Enums::QuestState questState;
		std::unordered_map<size_t, ObjectiveState> objectiveStates;
		std::unordered_map<size_t, std::vector<ObjectiveState>> bonusObjectiveStates;

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(questStateId);
			ar(questState);
			ar(objectiveStates);
			ar(bonusObjectiveStates);
		}

		template<class Archive>
		void load(Archive& ar)
		{
			ar(questStateId);
			ar(questState);
			ar(objectiveStates);
			ar(bonusObjectiveStates);
		}
	};
}

#endif