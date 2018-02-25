#include "Globals.hpp"

#include <AssetManager\AssetManagerCore.hpp>

#include "IEngineResource\EngineResourceManager.hpp"

ResourceType IEngineResource<Globals>::type = ResourceType::Globals;

Globals::Globals()
{
	AssetManager& am = Engine::Get <AssetManager>();

	putVariableInto(am.getIntRequestor(), longGlobals);
	putVariableInto(am.getDoubleRequestor(), doubleGlobals);
	putVariableInto(am.getStringRequestor(), stringGlobals);
	putVariableInto(am.getStringVectorRequestor(), stringList);
}

const ResourceType & Globals::getType()
{
	return type;
}
