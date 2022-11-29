#include "Globals.hpp"

#include <File/Asset/Manager.hpp>

#include "Module\EngineModuleManager.hpp"

Enums::EngineResourceType Interfaces::IEngineResource<Globals>::type = Enums::EngineResourceType::Globals;

const of::common::String Globals::texturePath = "Textures/";
const of::common::String Globals::skyboxTexturePath = Globals::texturePath + "skybox/";
const of::common::String Globals::uiTexturePath = Globals::texturePath + "Ui/";
const of::common::String Globals::tileTexturePath = Globals::texturePath + "Tiles/";
const of::common::String Globals::meshPath = "Meshes/";
const of::common::String Globals::shaderPath = "Shaders/";
const of::common::String Globals::LIGHT = "light.png";

const of::common::String Globals::GLOBAL_DRAW_HITBOX = "DrawHitbox";
const of::common::String Globals::GLOBAL_DRAW_QT = "DrawQuadTree";

const of::common::String Globals::LOADING_TIMER = "LOADING_TIMER";
const of::common::String Globals::TOTAL_TIME_LOADED = "TOTAL_TIME_LOADED";
const of::common::String Globals::TOTAL_TIME_LOADED_PART = "TOTAL_TIME_LOADED_PART";
const of::common::String Globals::B_GLOBAL_LOADINGSCREENINFO = "B_GLOBAL_LOADINGSCREENINFO";
const of::common::String Globals::B_GLOBAL_SLOW_LOADING = "B_GLOBAL_SLOW_LOADING";

const of::common::String Globals::B_FORCE_SAME_SEED = "B_FPRCE_SAME_SEED";


const float Globals::MAX_SIZE_F = 64.f;
const float Globals::Z_OFFSET = -64.f;

Globals::Globals()
{
	File::Asset::Manager& am = Engine::GetModule<File::Asset::Manager>();

	putVariableInto<PrimitiveSaveable<long>>(am.requestor, longGlobals, Enums::ObjectType::PrimitiveInt);
	putVariableInto<PrimitiveSaveable<double>>(am.requestor, doubleGlobals, Enums::ObjectType::PrimitiveDouble);
	putVariableInto<PrimitiveSaveable<of::common::String>>(am.requestor, stringGlobals, Enums::ObjectType::PrimitiveString);
	putVariableInto<PrimitiveSaveable<std::vector<of::common::String>>>(am.requestor, stringList, Enums::ObjectType::PrimitiveString);

	boolGlobals.insert(std::make_pair(GLOBAL_DRAW_HITBOX, true));
	boolGlobals.insert(std::make_pair(GLOBAL_DRAW_QT, false));
	boolGlobals.insert(std::make_pair(B_GLOBAL_LOADINGSCREENINFO, true));
	boolGlobals.insert(std::make_pair(B_GLOBAL_SLOW_LOADING, false));
	boolGlobals.insert(std::make_pair(B_FORCE_SAME_SEED, false));
}