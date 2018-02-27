#include "GameVariableMapping.hpp"
ResourceType IEngineResource<GameVariableMapping>::type = ResourceType::GameVariableMapping;

const ResourceType & GameVariableMapping::getType()
{
	return type;
}
