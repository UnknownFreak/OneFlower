#ifndef Modifier_HPP
#define Modifier_HPP

#include <utils/common/uuid.hpp>
#include <combat/attribute/StatType.hpp>
#include <resource/TickTimer.hpp>

namespace of::combat
{
	struct Modifier
	{
		Enums::StatType attributeToModify;
		bool inf;
		of::resource::TickTimer duration;
		double statModification;
		of::common::uuid modifierId;
		inline bool operator==(const Modifier& other)
		{
			return modifierId == other.modifierId;
		}

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(attributeToModify);
			ar(inf);
			ar(duration);
			ar(statModification);
			ar(modifierId);
		}
		template<class Archive>
		void load(Archive& ar)
		{
			ar(attributeToModify);
			ar(inf);
			ar(duration);
			ar(statModification);
			ar(modifierId);
		}
	};

	struct ModifierStack
	{
		size_t maxStackSize = 100;
		std::vector<Modifier> modifiers;

		double tick(const float& frame_tick)
		{
			double statChange = 0;
			
			auto it = modifiers.begin();
			while (it != modifiers.end())
			{
				if (!it->inf && it->duration.tick(frame_tick))
				{
					statChange += it->statModification;
					it = modifiers.erase(it);
				}
				else
					it++;
			}
			return statChange;
		}


		template<class Archive>
		void save(Archive& ar) const
		{
			ar(maxStackSize);
			ar(modifiers);
		}

		template<class Archive>
		void load(Archive& ar)
		{
			ar(maxStackSize);
			ar(modifiers);
		}
	};
}

#endif // !
