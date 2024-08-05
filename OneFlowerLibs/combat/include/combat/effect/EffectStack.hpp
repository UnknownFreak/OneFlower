#pragma once
#ifndef EffectStack_HPP
#define EffectStack_HPP
#include <vector>
#include "Effect.hpp"

namespace of::combat
{

	struct EffectStack
	{
		static EffectStack EMPTY;
		size_t maxStackSize = 100;
		std::vector<Effect> modifiers;
		of::common::String effectIcon;
		of::combat::EffectType effectType;
		bool hiddenStack;

		template <class T>
		std::vector<std::pair<T, float>> tick(const float& )
		{
			std::vector < std::pair<T, float>> modif;

			auto it = modifiers.begin();
			while (it != modifiers.end())
			{
				if (it->tickDelay.done())
				{
					modif.push_back({ T(*(T*)it->theEffect.get()), 1.f });
					it->tickDelay.reset();
					it->tickDelay.start();
				}
				if (it->effectTime.done())
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