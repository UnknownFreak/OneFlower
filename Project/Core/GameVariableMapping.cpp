#include "GameVariableMapping.hpp"
#include "IEngineResource\EngineResourceManager.hpp"
#include "Globals.hpp"
ResourceType IEngineResource<GameVariableMapping>::type = ResourceType::GameVariableMapping;

std::vector<Core::String>& GameVariableMapping::getAnimationList()
{
	std::map<Core::String, std::vector<Core::String>>& list = Engine::Get<Globals>().stringList;
	std::map<Core::String, std::vector<Core::String>>::iterator it = list.begin();
	if (it != list.end())
	{
		return it->second;
	}
	return empty;
}

#ifdef _EDITOR_
Core::String GameVariableMapping::getAnimationVariableName()
{
	return animationVariableId;
}
void GameVariableMapping::setAnimationVariableName(Core::String str)
{
	animationVariableId = str;
}
#endif

const ResourceType & GameVariableMapping::getType()
{
	return type;
}
