#ifndef EffectProperty_HPP
#define EffectProperty_HPP

#include <File/Mod/ModFileUUIDHelper.hpp>
#include <Helpers/Enum/Attribute.hpp>
#include "Modifier.hpp"

namespace Combat
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
		Enums::Attribute attributeModifier;
		double modifier;

		DamageEffect() : DamageEffect(0, Enums::Attribute::Unknown, 0) {};
		DamageEffect(const double& damage, const Enums::Attribute& attr, const double& modifier) : damage(damage), attributeModifier(attr), modifier(modifier) {}
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


		File::Mod::ModFileUUIDHelper vfxPrefab;

		VisualEffect() {}
		VisualEffect(const File::Mod::ModFileUUIDHelper& vfx) : vfxPrefab(vfx) {}
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

#endif