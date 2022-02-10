#ifndef RequirementTrigger_HPP
#define RequirementTrigger_HPP

#include "trigger.hpp"

#include <Requirement/Requirement.hpp>

namespace Trigger
{
	class RequirementTrigger : public Trigger
	{
		std::unique_ptr<Requirement::Requirement> requirement;
		std::unique_ptr<Trigger> trigger;

		// Inherited via Trigger
		virtual void executeInternal() override;

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::base_class<Trigger>(this));
			ar(requirement);
			ar(trigger);
		}
		template<class Archive>
		void load(Archive& ar)
		{
			ar(cereal::base_class<Trigger>(this));
			ar(requirement);
			ar(trigger);
		}

		// Inherited via Trigger
		virtual std::unique_ptr<Trigger> clone() const override;
	};
}

#endif