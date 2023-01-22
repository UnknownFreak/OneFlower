#ifndef EffectProperty_HPP
#define EffectProperty_HPP

#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>

#include <file/FileId.hpp>
#include <combat/attribute/StatType.hpp>
#include <combat/Modifier.hpp>

namespace of::combat
{
	struct EffectProperty
	{
		virtual ~EffectProperty() = default;
		template<class Ar>
		void save(Ar& ) const
		{
		}

		template<class Ar>
		void load(Ar& )
		{
		}
	};

	struct BarrierEffect : public EffectProperty
	{
		double barrierStrength;
		float barrierDuration;

		BarrierEffect() : BarrierEffect(0.f, 0) {}
		BarrierEffect(const float& duration, const double& strength) : barrierDuration(duration), barrierStrength(strength) {}
		BarrierEffect(const BarrierEffect& copy) : BarrierEffect(copy.barrierDuration, copy.barrierStrength) {};

		template<class Ar>
		void save(Ar& ar) const
		{
			ar(barrierDuration);
			ar(barrierStrength);
		}

		template<class Ar>
		void load(Ar& ar)
		{
			ar(barrierDuration);
			ar(barrierStrength);
		}
	};

	struct DamageEffect : public EffectProperty
	{
		double damage;
		Enums::StatType attributeModifier;
		double modifier;

		DamageEffect() : DamageEffect(0, Enums::StatType::Unknown, 0) {};
		DamageEffect(const double& damage, const Enums::StatType& attr, const double& modifier) : damage(damage), attributeModifier(attr), modifier(modifier) {}
		DamageEffect(const DamageEffect& copy) : DamageEffect(copy.damage, copy.attributeModifier, copy.modifier) {}

		template<class Ar>
		void save(Ar& ar) const
		{
			ar(damage);
			ar(attributeModifier);
			ar(modifier);
		}

		template<class Ar>
		void load(Ar& ar)
		{
			ar(damage);			
			ar(attributeModifier);
			ar(modifier);
		}
	};

	struct VisualEffect : public EffectProperty
	{
		of::file::FileId vfxPrefab;

		VisualEffect() {}
		VisualEffect(const of::file::FileId& vfx) : vfxPrefab(vfx) {}
		VisualEffect(const VisualEffect& copy): vfxPrefab(copy.vfxPrefab) {}

		template<class Ar>
		void save(Ar& ar) const
		{
			ar(vfxPrefab);
		}

		template<class Ar>
		void load(Ar& ar)
		{
			ar(vfxPrefab);
			loadVfx();
		}
	private:
		void loadVfx();
	};

	struct ModifierEffect : public EffectProperty
	{
		bool applied;
		Modifier modifier;

		template<class Ar>
		void save(Ar& ar) const
		{
			ar(applied);
			ar(modifier);
		}

		template<class Ar>
		void load(Ar& ar)
		{
			ar(applied);
			ar(modifier);
		}
	};
}

CEREAL_REGISTER_TYPE(of::combat::EffectProperty);
CEREAL_REGISTER_TYPE(of::combat::DamageEffect);
CEREAL_REGISTER_TYPE(of::combat::BarrierEffect);
CEREAL_REGISTER_TYPE(of::combat::VisualEffect);
CEREAL_REGISTER_TYPE(of::combat::ModifierEffect);
CEREAL_REGISTER_POLYMORPHIC_RELATION(of::combat::EffectProperty, of::combat::DamageEffect);
CEREAL_REGISTER_POLYMORPHIC_RELATION(of::combat::EffectProperty, of::combat::BarrierEffect);
CEREAL_REGISTER_POLYMORPHIC_RELATION(of::combat::EffectProperty, of::combat::VisualEffect);
CEREAL_REGISTER_POLYMORPHIC_RELATION(of::combat::EffectProperty, of::combat::ModifierEffect);

#endif