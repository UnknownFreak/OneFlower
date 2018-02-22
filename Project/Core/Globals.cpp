#include "Globals.hpp"

#include <AssetManager\AssetManagerCore.hpp>

#include "IEngineResource\EngineResourceManager.hpp"

ResourceType IEngineResource<Globals>::type = ResourceType::Globals;

Globals::Globals()
{
	AssetManager& am = Engine::Get <AssetManager>();

	Requestor<PrimitiveSaveable<int>>& intRequestor = am.getIntRequestor();
	Requestor<PrimitiveSaveable<double>>& doubleRequestor = am.getDoubleRequestor();
	Requestor<PrimitiveSaveable<Core::String>>& stringRequestor = am.getStringRequestor();
	Requestor<PrimitiveSaveable<std::vector<Core::String>>>& stringVectorRequestor = am.getStringVectorRequestor();

	putVariableInto(intRequestor, longGlobals);
	putVariableInto(doubleRequestor, doubleGlobals);
	putVariableInto(stringRequestor, stringGlobals);
	putVariableInto(stringVectorRequestor, stringList);
}

const ResourceType & Globals::getType()
{
	return type;
}
