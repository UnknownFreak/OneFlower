#pragma once
#ifndef Skill_HPP
#define Skill_HPP

#include <cereal/cereal.hpp>

#include <Helpers/Enum/CombatSkill.hpp>
#include <Interfaces/IRequestable.hpp>
#include <File/Mod/ModFileUUIDHelper.hpp>
#include <File/Asset/Resource/Prefab.hpp>

#include "Effect.hpp"
#include "Element.hpp"
#include <Helpers/TickTimer.hpp>

class GameObject;

namespace Graphics::UI
{
	class SkillIcon;
	class SkillIconChain;
}

namespace Combat
{
	class Skill : public Interfaces::IRequestable
	{
		// prefab that applies damage and buff/debuffs to the enemy (yes you can buff enemies)
	public:
		File::Mod::ModFileUUIDHelper prefabId;
		File::Mod::ModFileUUIDHelper skillEffectPrefabId;
		// effects that apply to the player
		std::vector<Combat::Effect> skillExecutionEffects;
		std::vector<File::Mod::ModFileUUIDHelper> skillExecutionEffectIds;

		Element getElement();
		void preloadEffect();

		std::unordered_map<Enums::CombatSkill, File::Mod::ModFileUUIDHelper> chainSkillsIds;
		std::unordered_map<Enums::CombatSkill, Skill> chainSkills;

		void getChainedSkills(std::vector<Graphics::UI::SkillIcon>& vec);

	public:

		Skill();

		File::Mod::ModFileUUIDHelper elementId;
		Combat::Element element;
		Core::TickTimer coolDown;
		double cost;
		bool summon;
		bool onSelf;
		float summonPoint;
		Core::String animation;
		Core::String iconTextureName;

		void onSkillExecution(GameObject* owner);
		void update(const float& dt);

		Graphics::UI::SkillIconChain getChain();

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::base_class<IRequestable>(this));
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
			ar(cereal::base_class<IRequestable>(this));
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
		virtual Interfaces::TypeInfo getTrait() const override;

	};
}

#endif