#pragma once
#ifndef Effect_HPP
#define Effect_HPP

#include <cereal/cereal.hpp>

#include <combat/effect/EffectType.hpp>

#include <file/archive/Requestable.hpp>
#include <combat/Element.hpp>
#include "EffectProperty.hpp"
#include <resource/TickTimer.hpp>

namespace of::object::component
{
	class Stats;
}

namespace Combat
{
	class Effect : public of::file::archive::Requestable
	{
		Element getElement();
	public:
		std::shared_ptr<of::object::component::Stats> owner;

		Effect();
		of::common::String effectIcon = "EffectIconFrame.png";
		Element effectElement;
		of::file::FileId effectElememtId;
		Enums::EffectType effectType;
		std::shared_ptr<EffectProperty> theEffect;

		of::resource::TickTimer effectTime;
		of::resource::TickTimer tickDelay;
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
CEREAL_REGISTER_TYPE(Combat::Effect);
CEREAL_REGISTER_POLYMORPHIC_RELATION(of::file::archive::Requestable, Combat::Effect);

#endif