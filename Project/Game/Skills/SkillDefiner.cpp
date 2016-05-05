#include "Skill.hpp"
#include <iostream>
#include "../Component/GameObject.h"
#include "../Component/HitboxComponent.hpp"
#include "../Component/TimerComponent.hpp"
#include "../../Engine.hpp"
Skill::Skill() : name("None"), description(""), attacks(), castTime(0), afterCast(0)
{

}
void Skill::execute()
{
	std::cout << "execute skill <START>" << std::endl;
	currentAttack = 0;
	currentExecuteTime = 0;
}
void Skill::finish()
{
	if (attacks.size() != currentAttack)
		if (currentExecuteTime > attacks[currentAttack].timeframe)
		{
			std::cout << "Executing attack <" << currentAttack + 1 << "> of <" << attacks.size() << ">, with damage <" << attacks[currentAttack].damage << ">"
				<< " at timestamp <" << currentExecuteTime << ">" << " Where execute time was supposed to be <" << attacks[currentAttack].timeframe << ">" << std::endl;
			currentAttack++;
		}
	std::cout << "execute skill <FINISH> at timestamp <" << currentExecuteTime << ">" << " Where total skill duration was supposed to be <" << totalCastTime() << ">" << std::endl;
}
GameObject* Skill::updateSkill()
{
	if (attacks.size() != currentAttack)
		if (currentExecuteTime > attacks[currentAttack].timeframe)
		{
			std::cout << "Executing attack <" << currentAttack + 1 << "> of <" << attacks.size() << ">, with damage <" << attacks[currentAttack].damage << ">"
				<< " at timestamp <" << currentExecuteTime << ">" << " Where execute time was supposed to be <" << attacks[currentAttack].timeframe << ">" << std::endl;
			GameObject* myHitbox = new GameObject();
			myHitbox->AddComponent<HitboxComponent>(attacks[currentAttack].hitbox.position.x,
				attacks[currentAttack].hitbox.position.y,
				attacks[currentAttack].hitbox.size.x,
				attacks[currentAttack].hitbox.size.y);
			myHitbox->AddComponent<Component::Timer>(attacks[currentAttack].duration);
			currentAttack++;
			return myHitbox;
		}
	return NULL;
}
double Skill::totalCastTime()
{
	return castTime + afterCast;
}

bool Skill::updateCastTime()
{
	currentExecuteTime += Engine::time.deltaTime();;
	if (currentExecuteTime > totalCastTime())
		return true;
	return false;
}

Attack::Attack() : hitbox(0, 8, 8, 8), damage(0), timeframe(0), duration(0), ProjectileDistance(0)
{

}