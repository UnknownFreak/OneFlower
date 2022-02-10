#include "Globals.hpp"

#include <File/AssetManagerCore.hpp>

#include "Module\EngineModuleManager.hpp"

Enums::EngineResourceType Interfaces::IEngineResource<Globals>::type = Enums::EngineResourceType::Globals;

const Core::String Globals::texturePath = "Textures/";
const Core::String Globals::uiTexturePath = Globals::texturePath + "Ui/";
const Core::String Globals::tileTexturePath = Globals::texturePath + "Tiles/";
const Core::String Globals::LIGHT = "light.png";
sf::ConvexShape Globals::shape;
sf::Font Globals::font;

const Core::String Globals::GLOBAL_DRAW_HITBOX = "DrawHitbox";
const Core::String Globals::GLOBAL_DRAW_QT = "DrawQuadTree";

const Core::String Globals::LOADING_TIMER = "LOADING_TIMER";
const Core::String Globals::TOTAL_TIME_LOADED = "TOTAL_TIME_LOADED";
const Core::String Globals::TOTAL_TIME_LOADED_PART = "TOTAL_TIME_LOADED_PART";
const Core::String Globals::B_GLOBAL_LOADINGSCREENINFO = "B_GLOBAL_LOADINGSCREENINFO";
const Core::String Globals::B_GLOBAL_SLOW_LOADING = "B_GLOBAL_SLOW_LOADING";

const Core::String Globals::B_FORCE_SAME_SEED = "B_FPRCE_SAME_SEED";


const float Globals::MAX_SIZE_F = 64.f;
const float Globals::Z_OFFSET = -64.f;

Globals::Globals()
{
	Asset::AssetManager& am = Engine::GetModule<Asset::AssetManager>();

	putVariableInto<PrimitiveSaveable<long>>(am.requestor, longGlobals, Enums::ObjectType::PrimitiveInt);
	putVariableInto<PrimitiveSaveable<double>>(am.requestor, doubleGlobals, Enums::ObjectType::PrimitiveDouble);
	putVariableInto<PrimitiveSaveable<Core::String>>(am.requestor, stringGlobals, Enums::ObjectType::PrimitiveString);
	putVariableInto<PrimitiveSaveable<std::vector<Core::String>>>(am.requestor, stringList, Enums::ObjectType::PrimitiveString);

	boolGlobals.insert(std::make_pair(GLOBAL_DRAW_HITBOX, true));
	boolGlobals.insert(std::make_pair(GLOBAL_DRAW_QT, false));
	boolGlobals.insert(std::make_pair(B_GLOBAL_LOADINGSCREENINFO, true));
	boolGlobals.insert(std::make_pair(B_GLOBAL_SLOW_LOADING, false));
	boolGlobals.insert(std::make_pair(B_FORCE_SAME_SEED, false));
	shape.setPointCount(4);
	shape.setPoint(0, { 0, 0 });
	shape.setPoint(1, { 0, 64 });
	shape.setPoint(2, { 64, 64 });
	shape.setPoint(3, { 64, 0 });
	shape.setOutlineColor(sf::Color::Red);
	shape.setOutlineThickness(1.f);
	font.loadFromFile("C:/Windows/Fonts/arial.ttf");
}