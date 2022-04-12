#include "Skill.hpp"

#include "Damage.hpp"
#include <File/Asset/Manager.hpp>

#include <Object/GameObject.hpp>
#include "Stats.hpp"

#include <Graphics/Render.hpp>
#include "AttachToParent.hpp"
#include <Graphics/UI/SkillIcon.hpp>
#include <Graphics/UI/SkillIconChain.hpp>

Core::uuid Interfaces::Trait<Combat::Skill>::typeId = Core::uuid("3ac2c9b8-d7bf-4028-8979-e240fd087c36");

namespace Combat
{


	Element Skill::getElement()
	{
		return Engine::GetModule<File::Asset::Manager>().requestor.requestUniqueInstance<Element>(elementId);
	}

	void Skill::preloadEffect()
	{
		auto& x = Engine::GetModule<File::Asset::Manager>().requestor;
		x.request<Asset::Resource::Prefab>(prefabId);
		x.request<Asset::Resource::Prefab>(skillEffectPrefabId);
	}

	void Skill::getChainedSkills(std::vector<Graphics::UI::SkillIcon>& vec)
	{
		for (auto& chain : chainSkills)
		{
			vec.push_back(Graphics::UI::SkillIcon(&chain.second));
			chain.second.getChainedSkills(vec);
		}
	}

	Skill::Skill() : IRequestable()
	{
	}

	void Skill::onSkillExecution(GameObject* owner)
	{
		if (coolDown.ready())
		{
			auto stats = owner->getSharedComponent<Component::Stats>();
			if (stats && stats->mainStat[Enums::Attribute::Mana].current >= cost)
			{
				stats->mainStat[Enums::Attribute::Mana].current -= cost;
				coolDown.reset(true);
				owner->getComponent<Component::Stats>()->doEffects(skillExecutionEffects, stats);
				auto& x = Engine::GetModule<File::Asset::Manager>().requestor;
				Asset::Resource::Prefab* skillPrefab = x.request<Asset::Resource::Prefab>(prefabId);
				Asset::Resource::Prefab* effectPrefab = x.request<Asset::Resource::Prefab>(skillEffectPrefabId);
				GameObject* skillGo = nullptr;
				GameObject* effectGo = nullptr;
				if (summon)
				{
					skillGo = skillPrefab->createNewInstance(owner);
					if (effectPrefab)
						effectGo = effectPrefab->createNewInstance(owner);
				}
				else
				{
					auto* transform = owner->getComponent<Component::Transform>();
					auto pos = transform->pos;
					pos += Core::Vector2f::distanceWithAngle(summonPoint, transform->facingAngle);
					skillGo = skillPrefab->createNewInstance(pos);
					if (effectPrefab)
						effectGo = effectPrefab->createNewInstance(pos);
				}

				if (onSelf)
				{
					skillGo->addComponent<Component::AttachToParent>(owner);
					if (effectGo)
						effectGo->addComponent<Component::AttachToParent>(owner);
				}
				auto damage = skillGo->getComponent<Component::Damage>();
				skillGo->addComponent<Render>();
				if (damage)
					damage->owner = owner->getSharedComponent<Component::Stats>();
			}
		}
	}

	void Skill::update(const float& dt)
	{
		coolDown.tick(dt);
	}

	Graphics::UI::SkillIconChain Skill::getChain()
	{
		std::vector<Graphics::UI::SkillIcon> v = { Graphics::UI::SkillIcon(this) };
		getChainedSkills(v);
		return Graphics::UI::SkillIconChain(v);
	}

	Interfaces::TypeInfo Skill::getTrait() const
	{
		return { Interfaces::Trait<Skill>::typeId };
	}
};
