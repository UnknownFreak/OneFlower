#ifndef HealthTresholdRequirement_HPP
#define HealthTresholdRequirement_HPP

#include "Requirement.hpp"

#include <Helpers/Enum/HealthTresholdComparitor.hpp>
#include <utils/common/uuid.hpp>

namespace Requirement
{

	class HealthTresholdRequirement : public Requirement
	{
	public:
		of::common::uuid objectId;
		Enums::HealthTresholdComparitor comparitor = Enums::HealthTresholdComparitor::LessThan;
		double percentage;

		// Inherited via Requirement
		virtual bool fullfilled() override;

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(objectId);
			ar(comparitor);
			ar(percentage);
		}

		template<class Archive>
		void load(Archive& ar)
		{
			ar(objectId);
			ar(comparitor);
			ar(percentage);
		}

		// Inherited via Requirement
		virtual std::unique_ptr<Requirement> clone() const override;
	};
}

#endif