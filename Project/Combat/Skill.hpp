#pragma once
#ifndef Skill_HPP
#define Skill_HPP

#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>

#include <Helpers/Enum/CombatSkill.hpp>

#include <file/archive/Requestable.hpp>
#include <file/FileId.hpp>

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
	class Skill : public of::file::archive::Requestable
	{
		// prefab that applies damage and buff/debuffs to the enemy (yes you can buff enemies)
	public:
		of::file::FileId prefabId;
		of::file::FileId skillEffectPrefabId;
		// effects that apply to the player
		std::vector<Combat::Effect> skillExecutionEffects;
		std::vector<of::file::FileId> skillExecutionEffectIds;

		Element getElement();
		void preloadEffect();

		std::unordered_map<Enums::CombatSkill, of::file::FileId> chainSkillsIds;
		std::unordered_map<Enums::CombatSkill, Skill> chainSkills;

		void getChainedSkills(std::vector<Graphics::UI::SkillIcon>& vec);

	public:

		Skill();

		of::file::FileId elementId;
		Combat::Element element;
		Core::TickTimer coolDown;
		double cost;
		bool summon;
		bool onSelf;
		float summonPoint;
		of::common::String animation;
		of::common::String iconTextureName;

		void onSkillExecution(GameObject* owner);
		void update(const float& dt);

		Graphics::UI::SkillIconChain getChain();

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::base_class<Requestable>(this));
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
			ar(cereal::base_class<Requestable>(this));
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
		virtual of::file::archive::TypeInfo getTrait() const override;

	};
}
CEREAL_REGISTER_TYPE(Combat::Skill);
CEREAL_REGISTER_POLYMORPHIC_RELATION(of::file::archive::Requestable, Combat::Skill);
#endif