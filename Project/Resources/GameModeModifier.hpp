#ifndef GameModeModifiers_HPP
#define GameModeModifiers_HPP

#include <vector>

#include <Combat/Modifier.hpp>
#include <Trigger/Trigger.hpp>

namespace Resource
{
	struct GameModeModifier
	{
		std::vector<Combat::Modifier> modifierList;
		std::vector<std::unique_ptr<Trigger::Trigger>> onDeathTriggers;
		//
		// AI behaviour
		//

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(modifierList);
			ar(onDeathTriggers);
		}

		template<class Archive>
		void load(Archive& ar)
		{
			ar(modifierList);
			ar(onDeathTriggers);
		}
	};
}

#endif