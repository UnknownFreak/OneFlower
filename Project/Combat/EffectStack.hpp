#pragma once
#ifndef EffectStack_HPP
#define EffectStack_HPP
#include <vector>
#include "Effect.hpp"

namespace Combat
{

	struct EffectStack
	{
		static EffectStack EMPTY;
		size_t maxStackSize = 100;
		std::vector<Effect> modifiers;
		Core::String effectIcon;
		Enums::EffectType effectType;
		bool hiddenStack;

		template <class T>
		std::vector<std::pair<T, float>> tick(const float& frame_tick)
		{
			std::vector < std::pair<T, float>> modif;

			auto it = modifiers.begin();
			while (it != modifiers.end())
			{
				if (it->tickDelay.tick(frame_tick))
				{
					modif.push_back({ T(*(T*)it->theEffect.get()), 1.f });
					it->tickDelay.reset();
				}
				if (it->effectTime.tick(frame_tick))
				{
					modif.push_back({ T(*(T*)it->theEffect.get()), it->tickDelay.getFraction() });
					it = modifiers.erase(it);
				}
				else
					it++;
			}
			return modif;
		}

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(modifiers);
			ar(effectIcon);
			ar(effectType);
			ar(hiddenStack);
		}
		template<class Archive>
		void load(Archive& ar)
		{
			ar(modifiers);
			ar(effectIcon);
			ar(effectType);
			ar(hiddenStack);
		}
	};
}

#endif