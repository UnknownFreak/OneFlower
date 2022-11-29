#pragma once
#ifndef Effect_HPP
#define Effect_HPP

#include <cereal/cereal.hpp>

#include <Helpers/Enum/EffectType.hpp>

#include <Interfaces/IRequestable.hpp>
#include "Element.hpp"
#include "EffectProperty.hpp"
#include <Helpers/TickTimer.hpp>

namespace Component
{
	class Stats;
}

namespace Combat
{
	class Effect : public Interfaces::IRequestable
	{
		Element getElement();
	public:
		std::shared_ptr<Component::Stats> owner;

		Effect();
		of::common::String effectIcon = "EffectIconFrame.png";
		Element effectElement;
		File::Mod::ModFileUUIDHelper effectElememtId;
		Enums::EffectType effectType;
		std::shared_ptr<EffectProperty> theEffect;

		Core::TickTimer effectTime;
		Core::TickTimer tickDelay;
		bool hideFromBuffsUI;

		// Inherited via IRequestable
		virtual Interfaces::TypeInfo getTrait() const override;

		template<class T>
		void save(T& ar) const
		{
			ar(cereal::base_class<Interfaces::IRequestable>(this));
			ar(effectType);
			ar(effectTime);
			ar(effectIcon);
			ar(effectElememtId);
			ar(tickDelay);
			ar(theEffect);
			ar(hideFromBuffsUI);
		}

		template<class T>
		void load(T& ar)
		{
			ar(cereal::base_class<Interfaces::IRequestable>(this));
			ar(effectType);
			ar(effectTime);
			ar(effectIcon);
			ar(effectElememtId);
			ar(tickDelay);
			ar(theEffect);
			ar(hideFromBuffsUI);
			effectElement = getElement();
			if (tickDelay.maxTime == 0.f)
				tickDelay.maxTime = 0.1f;
		}

	};
}


#endif