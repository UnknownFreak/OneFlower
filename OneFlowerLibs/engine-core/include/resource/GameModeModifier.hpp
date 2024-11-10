#pragma once

#include <vector>
#include <cereal/cereal.hpp>
#include <cereal/types/vector.hpp>

#include <asset/assetId.hpp>
#include <trigger/Trigger.hpp>

namespace of::resource
{
	struct GameModeModifier
	{
		std::vector<asset::AssetId> modifierList;
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
