#ifndef SKILL_HPP
#define	SKILL_HPP
#include <string>
#include <vector>
#include "Attack.hpp"
class GameObject;

struct Skill
{
	
	enum WeaponType
	{
		None,
		Sword,
		Etc,
	};
	Skill();

	bool updateCastTime();
	double totalCastTime();
	void execute();
	//need this?
	void finish();
	//returns a reference towards a gameobject representing the hit area of the attack, otherwise returns NULL
	GameObject* updateSkill();
	//if true this skill can be selected by the player
	bool canBeUsedByPlayer;

	//name
	std::string name;
	//description
	std::string description;
	//number of attacks the skill does, and how much damage each of that attack does.
	//<int> the attack damage
	//<double> the timeframe the attack gets executed
	std::vector<Attack> attacks;
	
	// time to cast the skill, (frame count?, or in seconds?)
	double castTime;
	// time to wait after the skill is complete, this time user can start a chain
	double afterCast;
	//the timeframes where the attacks cannot be used
	double cooldown;

	//SkillType and animation

	WeaponType skillType = WeaponType::None;
	std::string animationName;

	//if the skill moves the character

	bool movesCharacter;
	double distanceX;
	double distanceY;
	
	std::string modname;
	unsigned int ID;

private:
	//value between start of skill and end of skill;
	//may not be required
	double currentExecuteTime;
	int currentAttack = 0;
protected:
	template<class Archive>
	friend void save(Archive& ar, const Skill& mySkill);
	template<class Archive>
	friend void load(Archive& ar, Skill& mySkill);
};

#endif