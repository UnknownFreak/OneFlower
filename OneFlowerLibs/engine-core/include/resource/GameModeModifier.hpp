#ifndef GameModeModifiers_HPP
#define GameModeModifiers_HPP

#include <vector>
#include <cereal/cereal.hpp>
#include <cereal/types/vector.hpp>

#include <file/FileId.hpp>
#include <trigger/Trigger.hpp>

namespace of::resource
{
	struct GameModeModifier
	{
		std::vector<file::FileId> modifierList;
		std::vector<std::unique_ptr<trigger::Trigger>> onDeathTriggers;
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