#ifndef ObjectiveState_HPP
#define ObjectiveState_HPP

#include <Helpers/Enum/QuestState.hpp>
#include <vector>

namespace Questing
{
	struct ObjectiveState
	{
		Enums::QuestState state;
		size_t unit;
		std::vector<ObjectiveState> recursive;

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(state);
			ar(unit);
			ar(recursive);
		}

		template<class Archive>
		void load(Archive& ar)
		{
			ar(state);
			ar(unit);
			ar(recursive);
		};
	};
}

#endif