#include "CombatComponenet.hpp"
#include "GameObject.h"
#include "TransformComponent.hpp"
#include "HitboxComponent.hpp"
#include "../../Engine.hpp"
#include <iostream>
const unsigned int IBaseComponent<Component::Combat>::typeID = 123213;
std::string IBaseComponent<Component::Combat>::componentName = "CombatComponent";
namespace Component
{
	Combat::Combat() : testSkill()
	{
		testSkill.name = "TestAttack";
		testSkill.attacks.push_back(Attack());
		testSkill.attacks.push_back(Attack());
		testSkill.attacks[0].damage = 1337;
		testSkill.attacks[0].timeframe = .2;
		testSkill.attacks[0].duration = .2;
		testSkill.attacks[0].hitbox.position.x = 32+8;
		testSkill.attacks[0].hitbox.position.y = 32-8;
		testSkill.attacks[1].damage = 9001;
		testSkill.attacks[1].timeframe = .2;
		testSkill.attacks[1].duration = .2;
		testSkill.attacks[1].hitbox.position.x = 64;
		testSkill.attacks[1].hitbox.position.y = 0;
		testSkill.attacks[1].hitbox.size.x = 32;
		testSkill.attacks[1].hitbox.size.y = 32;
		testSkill.castTime = .5;
	}
	void Combat::attachOn(GameObject* attachTo)
	{
		Combat::BaseComponent::attachOn(attachTo);
	}
	void Combat::execute()
	{
		if (executingSkill == false)
		{
			testSkill.execute();
			executingSkill = true;
		}
	}
	void Combat::update()
	{
		if (testSkill.updateCastTime())
		{
			executingSkill = false;
			testSkill.finish();
		}
		else
		{
			GameObject* myHitbox = testSkill.updateSkill();
			if (myHitbox != NULL)
			{
				myHitbox->GetComponent<TransformComponent>()->position = this->attachedOn->GetComponent<TransformComponent>()->position;
				//rework this to use the animation and get the point where attack is spawned from
				myHitbox->GetComponent<TransformComponent>()->position += myHitbox->GetComponent<HitboxComponent>()->bounding.position;
				Engine::game.addGameObject(myHitbox);
			}
		}
	}
}