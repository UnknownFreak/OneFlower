#include "Globals.hpp"

#include <Asset\AssetManagerCore.hpp>

#include "EngineModule\EngineModuleManager.hpp"

ResourceType IEngineResource<Globals>::type = ResourceType::Globals;

const Core::String Globals::texturePath = "Textures/";
const Core::String Globals::tileTexturePath= Globals::texturePath+"Tiles/";


Globals::Globals()
{
	Asset::AssetManager& am = Engine::GetModule<Asset::AssetManager>();

	putVariableInto(am.getIntRequestor(), longGlobals);
	putVariableInto(am.getDoubleRequestor(), doubleGlobals);
	putVariableInto(am.getStringRequestor(), stringGlobals);
	putVariableInto(am.getStringVectorRequestor(), stringList);
}

const ResourceType & Globals::getType()
{
	return type;
}
