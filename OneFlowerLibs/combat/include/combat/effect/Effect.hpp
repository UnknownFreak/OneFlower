#pragma once
#ifndef Effect_HPP
#define Effect_HPP

#include <cereal/cereal.hpp>

#include <combat/effect/EffectType.hpp>

#include <file/archive/Requestable.hpp>
#include <combat/Element.hpp>
#include "EffectProperty.hpp"
#include <timer/tickTimer.hpp>

namespace of::component
{
	class Stats;
}

namespace of::combat
{
	class Effect : public of::file::archive::Requestable
	{
		Element getElement();
	public:
		std::shared_ptr<of::component::Stats> owner;

		Effect();
		of::common::String effectIcon = "EffectIconFrame.png";
		Element effectElement;
		of::file::FileId effectElememtId;
		of::combat::EffectType effectType;
		std::shared_ptr<EffectProperty> theEffect;

		of::timer::TickTimer effectTime;
		of::timer::TickTimer tickDelay;
		bool hideFromBuffsUI;

		// Inherited via IRequestable
		virtual of::file::archive::TypeInfo getTrait() const override;

		template<class T>
		void save(T& ar) const
		{
			ar(cereal::base_class<Requestable>(this));
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
			ar(cereal::base_class<Requestable>(this));
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
CEREAL_REGISTER_TYPE(of::combat::Effect);
CEREAL_REGISTER_POLYMORPHIC_RELATION(of::file::archive::Requestable, of::combat::Effect);

#endif