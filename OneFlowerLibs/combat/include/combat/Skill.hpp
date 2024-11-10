#pragma once

#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>

#include <combat/CombatSkill.hpp>

#include <asset/iAsset.hpp>

#include <combat/effect/Effect.hpp>
#include "Element.hpp"
#include <timer/tickTimer.hpp>

namespace of::object
{
	class GameObject;
}
/*
namespace Graphics::UI
{
	class SkillIcon;
	class SkillIconChain;
}
*/

namespace of::combat
{
	class Skill : public of::asset::IAsset
	{
		// prefab that applies damage and buff/debuffs to the enemy (yes you can buff enemies)
	public:
		of::asset::AssetId prefabId;
		of::asset::AssetId skillEffectPrefabId;
		// effects that apply to the player
		std::vector<of::combat::Effect> skillExecutionEffects;
		std::vector<of::asset::AssetId> skillExecutionEffectIds;

		Element getElement();
		void preloadEffect();

		std::unordered_map<Enums::CombatSkill, of::asset::AssetId> chainSkillsIds;
		std::unordered_map<Enums::CombatSkill, Skill> chainSkills;

		//void getChainedSkills(std::vector<Graphics::UI::SkillIcon>& vec);

	public:

		Skill();

		of::asset::AssetId elementId;
		of::combat::Element element;
		of::timer::TickTimer coolDown;
		double cost;
		bool summon;
		bool onSelf;
		float summonPoint;
		of::common::String animation;
		of::common::String iconTextureName;

		void onSkillExecution(of::object::GameObject* owner);
		void update(const float& dt);

		//Graphics::UI::SkillIconChain getChain();

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::base_class<IAsset>(this));
			ar(elementId);
			ar(coolDown);
			ar(cost);
			ar(animation);
			ar(prefabId);
			ar(skillEffectPrefabId);
			ar(summon);
			ar(onSelf);
			ar(summonPoint);
			ar(iconTextureName);
		}

		template<class Archive>
		void load(Archive& ar)
		{
			ar(cereal::base_class<IAsset>(this));
			ar(elementId);
			element = getElement();
			ar(coolDown);
			ar(cost);
			ar(animation);
			ar(prefabId);
			ar(skillEffectPrefabId);
			ar(summon);
			ar(onSelf);
			ar(summonPoint);
			ar(iconTextureName);
			preloadEffect();
		}

		// Inherited via IRequestable
		virtual of::asset::TypeInfo getTrait() const override;

	};
}
CEREAL_REGISTER_TYPE(of::combat::Skill);
CEREAL_REGISTER_POLYMORPHIC_RELATION(of::asset::IAsset, of::combat::Skill);
