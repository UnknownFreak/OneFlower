#include "ReputationComponent.hpp"
#include "GameObject.h"
#include "IBaseComponent.hpp"

#include "../../Engine.hpp"

const unsigned int IBaseComponent<ReputationComponent>::typeID = 1023;
std::string IBaseComponent<ReputationComponent>::componentName = "ReputationComponent";

ReputationComponent::ReputationComponent()
{
	names[0] = "Hated";
	names[1] = "Neutral";
	names[2] = "Friendly";
	names[3] = "Honoured";
	names[4] = "Revered";
	names[5] = "Exalted";
	requierment[0] = -1;
	requierment[1] = 0;
	requierment[2] = 3000;
	requierment[3] = 6000;
	requierment[4] = 12000;
	requierment[5] = 21000;
}

void ReputationComponent::attachOn(GameObject* go)
{
	BaseComponent::attachOn(go);
}

void ReputationComponent::increaseReputation(std::string faction,int x)
{
	//a map iterator.
	std::map<std::string,int>::iterator it;
	std::map<std::string,int>::iterator itSecond;
	//looping through the map iterator to find the faction.
	for(it = rep.begin(); it != rep.end(); ++it)
		if(it->first == faction)
			break;
	for(itSecond = levels.begin(); itSecond != levels.end(); ++itSecond)
		if(itSecond->first == faction)
			break;

	//if the map is not in the end add x to reps second value.
	if(it != rep.end())
	{
		if(it->second < requierment[5])
		{
			it->second += x;
		}
		if(it->second >= requierment[itSecond->second + 1] && itSecond->second <= 5)
		{
			++itSecond->second;
		}
	}
	//if the map do not contain the faction add a new faction.
	else
		addNewRep(faction,x);
}

void ReputationComponent::decreaseReputation(std::string faction,int x)
{
	std::map<std::string,int>::iterator it;
	std::map<std::string,int>::iterator itSecond;
	for(it = rep.begin(); it != rep.end(); ++it)
		if(it->first == faction)
			break;
	for(itSecond = levels.begin(); itSecond != levels.end(); ++itSecond)
		if(itSecond->first == faction)
			break;

	if(it != rep.end())
	{
		if(it->second > -5000)
		{
			it->second -= x;
		}
		if(it->second < requierment[itSecond->second] && itSecond->second >= 0)
		{
			--itSecond->second;
			if(itSecond->second < 0)
			{
				itSecond->second = 0;
			}
		}
	}
	else
		addNewRep(faction,-x);
}

std::string ReputationComponent::getStanding()
{
	return names[level];
}

void ReputationComponent::showRep(std::string a,int x,int y)
{
	name = a;
	reputation = x;
	repStanding = names[y];
}

void ReputationComponent::addNewRep(std::string name,int value)
{
	rep.insert(std::make_pair(name,value));
	levels.insert(std::make_pair(name,1));
}

void ReputationComponent::removeRep(std::string name)
{
	std::map<std::string,int>::iterator it;
	std::map<std::string,int>::iterator itSecond;

	for(it = rep.begin(); it != rep.end(); ++it)
		if(it->first == name)
		{
			rep.erase(it);
			break;
		}
	for(itSecond = levels.begin(); itSecond != levels.end(); ++itSecond)
		if(it->first == name)
		{
			levels.erase(itSecond);
			break;
		}
}