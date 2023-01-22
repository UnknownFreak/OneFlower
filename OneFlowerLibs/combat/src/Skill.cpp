#include <combat/Skill.hpp>

#include <object/component/Damage.hpp>
#include <object/component/Stats.hpp>
#include <object/component/AttachToParent.hpp>

#include <file/Handler.hpp>

#include <Object/GameObject.hpp>

#include <resource/Prefab.hpp>

/*
#include <Graphics/UI/SkillIcon.hpp>
#include <Graphics/UI/SkillIconChain.hpp>
*/

of::common::uuid of::file::archive::Trait<of::combat::Skill>::typeId = of::common::uuid("3ac2c9b8-d7bf-4028-8979-e240fd087c36");

namespace of::combat
{
	Element Skill::getElement()
	{
		return of::engine::GetModule<of::file::Handler>().archive.requestUniqueInstance<Element>(elementId);
	}

	void Skill::preloadEffect()
	{
		auto& x = of::engine::GetModule<of::file::Handler>().archive;
		x.request<of::resource::Prefab>(prefabId);
		x.request<of::resource::Prefab>(skillEffectPrefabId);
	}

	/*
	void Skill::getChainedSkills(std::vector<Graphics::UI::SkillIcon>& vec)
	{
		for (auto& chain : chainSkills)
		{
			vec.push_back(Graphics::UI::SkillIcon(&chain.second));
			chain.second.getChainedSkills(vec);
		}
	}
	*/

	Skill::Skill() : Requestable()
	{
	}

	glm::vec3 distanceWithAngle(const float &distance, const float& angle)
	{
		float rangle = angle * (3.1415927f / 180.f);
		return glm::vec3{ distance * -std::sin(rangle), distance * std::cos(rangle), 0.f };
	}

	void Skill::onSkillExecution(of::object::GameObject* owner)
	{
		if (coolDown.ready())
		{
			auto stats = owner->getShared<of::object::component::Stats>();
			if (stats && stats->mainStat[Enums::StatType::Mana].current >= cost)
			{
				stats->mainStat[Enums::StatType::Mana].current -= cost;
				coolDown.reset(true);
				owner->get<of::object::component::Stats>()->doEffects(skillExecutionEffects, stats);
				auto& x = of::engine::GetModule<of::file::Handler>().archive;
				of::resource::Prefab* skillPrefab = x.request<of::resource::Prefab>(prefabId);
				of::resource::Prefab* effectPrefab = x.request<of::resource::Prefab>(skillEffectPrefabId);
				of::object::GameObject* skillGo = nullptr;
				of::object::GameObject* effectGo = nullptr;
				if (summon)
				{
					skillGo = skillPrefab->createNewInstance(owner, owner->tag == "player");
					if (effectPrefab)
						effectGo = effectPrefab->createNewInstance(owner, owner->tag == "player");
				}
				else
				{
					auto* transform = owner->get<of::object::component::Transform>();
					auto pos = transform->pos;
					pos += distanceWithAngle(summonPoint, transform->facingAngle);
					skillGo = skillPrefab->createNewInstance(pos, owner->tag == "player");
					if (effectPrefab)
						effectGo = effectPrefab->createNewInstance(pos, owner->tag == "player");
				}

				if (onSelf)
				{
					skillGo->add<of::object::component::AttachToParent>(owner);
					if (effectGo)
						effectGo->add<of::object::component::AttachToParent>(owner);
				}
				auto damage = skillGo->get<of::object::component::Damage>();
				if (damage)
					damage->owner = owner->getShared<of::object::component::Stats>();
			}
		}
	}

	void Skill::update(const float& dt)
	{
		coolDown.tick(dt);
	}

	/*
	Graphics::UI::SkillIconChain Skill::getChain()
	{
		std::vector<Graphics::UI::SkillIcon> v = { Graphics::UI::SkillIcon(this) };
		getChainedSkills(v);
		return Graphics::UI::SkillIconChain(v);
	}
	*/

	of::file::archive::TypeInfo Skill::getTrait() const
	{
		return { of::file::archive::Trait<Skill>::typeId };
	}
};
