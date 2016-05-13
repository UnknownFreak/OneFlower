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
		testSkill.attacks[0].damage = 1337;
		testSkill.attacks[0].timeframe = .35;
		testSkill.attacks[0].duration = .2;
		testSkill.attacks[0].hitbox.position.x = 25;
		testSkill.attacks[0].hitbox.position.y = -35; 
		testSkill.attacks[0].hitbox.size.x = 128;
		testSkill.attacks[0].hitbox.size.y = 32; 
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
			RenderComponent* render = attachedOn->GetComponent<RenderComponent>();
			if (render)
			{
				BaseMessage msg;
				//to replace with skill.animation
				msg.msg = "attack";
				attachedOn->sendMessage(msg, render);
			}
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
				RenderComponent::Facing f = RenderComponent::Facing::Right;
				RenderComponent* render = attachedOn->GetComponent<RenderComponent>();
				if (render)
					f = render->facingDirection;
				if (f == RenderComponent::Facing::Right)
					myHitbox->GetComponent<TransformComponent>()->position += myHitbox->GetComponent<HitboxComponent>()->bounding.position;
				else
				{
					myHitbox->GetComponent<TransformComponent>()->position.x -= myHitbox->GetComponent<HitboxComponent>()->bounding.position.x;
					myHitbox->GetComponent<TransformComponent>()->position.y += myHitbox->GetComponent<HitboxComponent>()->bounding.position.y;
					myHitbox->GetComponent<TransformComponent>()->position.x -= myHitbox->GetComponent<HitboxComponent>()->bounding.size.x;
				}
				Engine::game.addGameObject(myHitbox);
			}
		}
	}
}