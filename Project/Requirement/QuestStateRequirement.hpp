#ifndef QuestStateRequirement_HPP
#define QuestStateRequirement_HPP

#include "Requirement.hpp"
#include <File/ModFileUUIDHelper.hpp>
#include <Helpers/Enum/QuestState.hpp>

namespace Requirement
{
	class QuestStateRequirment : public Requirement
	{
	public:
		File::Mod::ModFileUUIDHelper questId;
		Enums::QuestState questState;
		bool checkObjective = false;
		size_t objectiveId = 0;
		// Inherited via Requirement
		virtual bool fullfilled() override;

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(questId);
			ar(questState);
			ar(checkObjective);
			ar(objectiveId);
		}

		template<class Archive>
		void load(Archive& ar)
		{
			ar(questId);
			ar(questState);
			ar(checkObjective);
			ar(objectiveId);
		}

		// Inherited via Requirement
		virtual std::unique_ptr<Requirement> clone() const override;
	};
}

#endif