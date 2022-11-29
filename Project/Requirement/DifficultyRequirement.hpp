#ifndef DifficultyRequirement_HPP
#define DifficultyRequirement_HPP

#include "Requirement.hpp"
#include <utils/common/uuid.hpp>
#include <Helpers/Enum/DifficultyLevels.hpp>

namespace Requirement
{
	class DifficultyRequirement : public Requirement
	{
	public:

		Enums::DifficultyLevel level;
		of::common::uuid customDiff;

		// Inherited via Requirement
		virtual bool fullfilled() override;

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(level);
			ar(customDiff);
		}
		template <class Archive>
		void load(Archive& ar)
		{
			ar(level);
			ar(customDiff);
		}


		// Inherited via Requirement
		virtual std::unique_ptr<Requirement> clone() const override;

	};
}

#endif