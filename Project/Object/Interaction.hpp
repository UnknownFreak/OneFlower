#ifndef Interaction_HPP
#define Interaction_HPP

#include <Requirement/Requirement.hpp>
#include <Trigger/Trigger.hpp>

namespace Object
{
	struct Interaction
	{
		Interaction() = default;
		Interaction(const Interaction& )
		{
			// TODO: fix copy ctor
			//interactionRequirement = copy.interactionRequirement.get()->clone();
		}

		of::common::String actorAnimation;
		of::common::String interactionAnimation;
		of::common::String interactionState;

		std::unique_ptr<Requirement::Requirement> interactionRequirement;
		std::unique_ptr<Trigger::Trigger> interactionTrigger;

		std::vector<std::tuple<of::common::uuid, bool, bool, short>> interactions;

	};
}

#endif