#include "WorldManager.hpp"
#include <Input/InputHandler.hpp>

#include <Module/Globals.hpp>
#include <Module/OneTime.hpp>

#include <object/component/BaseComponent.hpp>
#include <object/component/IBaseComponent.hpp>

#include <Helpers/Enum/TileTypes.hpp>

#include <File/Handler.hpp>

#include <File/Asset/Resource/Template/WorldInstance.hpp>
#include <File/Asset/Resource/Template/TileTemplate.hpp>
#include <File/Asset/Resource/Template/ColliderTemplate.hpp>
#include <File/Asset/Resource/Prefab.hpp>

#include <Graphics/Render.hpp>
#include <Graphics/Dialog.hpp>
#include <Graphics/PlayerInteractionPrompt.hpp>

#include <Graphics/UI/PlayerStats.hpp>

#include <Combat/Stats.hpp>
#include <Combat/Effect.hpp>
#include <Combat/Element.hpp>
#include <Combat/Damage.hpp>

#include <Object/GameObject.hpp>

#include <Module/Globals.hpp>

of::file::FileId dialogTest;
of::common::uuid testObjectId;

void WorldManager::doDayCycle(const float& fElapsedTime)
{
	float dt = 0.004f * fElapsedTime;
	gfx.timeOfDay += dt;
	float f = 3.14f / 20.f;
	float f2 = 6.f / 20.f;
	//float f3 = 1.4f / 18.f;
	if (gfx.timeOfDay > 24.f)
	{
		gfx.timeOfDay = 0.f;
		gfx.shadowAngle = 0.f;
	}
	if (gfx.timeOfDay > 0.f && gfx.timeOfDay < 5.f)
	{
		gfx.shadowLengthX = 6.f;
		gfx.shadowLengthY = 1.4f;
	}
	//		gfx.shadowAngle += f * dt;
	if (gfx.timeOfDay > 5.f && gfx.timeOfDay < 5.f + 20.f)
	{
		gfx.shadowAngle += f * dt;
		if (gfx.timeOfDay < 4.f + 8)
		{
			gfx.shadowLengthX -= f2 * dt;
		}
		else
		{
			gfx.shadowLengthX += f2 * dt;
		}
	}

	//gfx.shadowLengthX = gfx.timeOfDay / 12.f;
	//gfx.shadowLengthY = gfx.timeOfDay / 18.f;
	//uint_fast8_t time = (uint_fast8_t)(std::abs(std::sin(gfx.timeOfDay / 8.f)) * 255);
	//if (time < 64)
	//	time = 64;
	//gfx.currentDayColor = sf::Color(time, time, time);
	//std::cout << "Brightness of day (0-255): " << int(time) << std::endl;
	//float whole, fractional;
	//fractional = std::modf(gfx.timeOfDay, &whole);
	//std::cout << "time of day: " << int(whole) << "h " << int(fractional*60) << "m " << int(fractional*3600) % 60 << "s" << std::endl;
	//std::cout << "shadowAngle: " << gfx.shadowAngle << std::endl;
	//std::cout << "shadow length x: " << gfx.shadowLengthX << std::endl;
	//std::cout << "shadow length y: " << gfx.shadowLengthY << std::endl;
}

WorldManager::WorldManager(Graphics::RenderWindow& gfx) : gfx(gfx), loadHandler(gfx, isLoading), objectHandler(of::engine::GetModule<of::module::ObjectInstanceHandler>()), saveFile(of::engine::GetModule<of::module::SaveFile>())
{
}

void WorldManager::initialize()
{
	newGame();
	auto& f = of::engine::GetModule<Input::InputHandler>();

	auto* go = objectHandler.addObject();
	testObjectId = go->id;
	go->getComponent<of::object::component::Transform>()->pos = { 150, 250.f, 0.f };
	go->addComponent<Render>();
	go->addComponent<Dialog>();
	
	f.uiKeyboard.RegisterCallback(Input::Callback::KeyboardCallbackTemp("Console", [&](bool, swizzle::input::Keys, const float&) {gfx.ui.ToggleConsole(); f.togglePlayerInput(); }, false),
		swizzle::input::Keys::KeyF1
	, Enums::Input::Action::Press);

	f.uiKeyboard.RegisterCallback(Input::Callback::KeyboardCallbackTemp("GlobalFlag", [&](bool, swizzle::input::Keys, const float&) {
		of::engine::GetModule<Globals>().boolGlobals[Globals::GLOBAL_DRAW_HITBOX] = !of::engine::GetModule<Globals>().boolGlobals[Globals::GLOBAL_DRAW_HITBOX];
		}, false), 
		 swizzle::input::Keys::KeyF2
		, Enums::Input::Action::Press);

	auto& console = of::engine::GetModule<Console>();
	console;

}

WorldManager::WorldManager(const WorldManager& copy): gfx(copy.gfx), objectHandler(of::engine::GetModule<of::module::ObjectInstanceHandler>()), loadHandler(copy.gfx, isLoading), saveFile(of::engine::GetModule<of::module::SaveFile>())
{
}

void WorldManager::createSimpleWorld()
{
	const auto mod = "Default";
	gfx.clearDrawList();

	auto& theManager = of::engine::GetModule<of::file::Handler>();
	//auto& atlasMgr = theManager.getTileAtlas();
	//atlasMgr.add(ta);
	//theManager.test.add(t.get());

	//auto& worldInstance = theManager.getWorldInstance();
	//auto& colliderChunks = theManager.getColliderChunks();
	//auto& tileChunks = theManager.getTileChunks();

	File::Asset::Resource::Template::WorldInstance wi;
	wi.objectType = of::file::ObjectType::WorldInstance;
	wi.fromMod = mod;

	File::Asset::Resource::Template::ColliderChunk chunk;
	
	chunk.objectType = of::file::ObjectType::ColliderChunk;
	chunk.fromMod = mod;
	/// <summary>
	/// glm::vec2 size;
	/// Enums::ColliderType type;
	/// size_t layer;
	/// Core::String group;
	/// </summary>
	chunk.layer = 0;
	chunk.group = "Default";
	chunk.colliderInfo.push_back(File::Asset::Resource::Template::ColliderTemplate{ glm::vec3{64.f, 64.f, 0.f}, glm::vec2{256.f, 256.f}, Enums::ColliderType::Floor});
	chunk.colliderInfo.push_back(File::Asset::Resource::Template::ColliderTemplate{ glm::vec3{64.f + 256.f, 64.f, 0.f}, glm::vec2{192.f, 256.f}, Enums::ColliderType::Floor});
	chunk.colliderInfo.push_back(File::Asset::Resource::Template::ColliderTemplate{ glm::vec3{64.f, 64.f + 256.f, 0.f}, glm::vec2{256.f, 256.f}, Enums::ColliderType::Floor});
	chunk.colliderInfo.push_back(File::Asset::Resource::Template::ColliderTemplate{ glm::vec3{64.f + 256.f, 64.f + 256.f, 0.f}, glm::vec2{192.f, 256.f}, Enums::ColliderType::Floor});
	chunk.colliderInfo.push_back(File::Asset::Resource::Template::ColliderTemplate{ glm::vec3{8 * 64.f, 64.f, 0.f}, glm::vec2{64.f * 5, 192.f}, Enums::ColliderType::Floor});
	chunk.colliderInfo.push_back(File::Asset::Resource::Template::ColliderTemplate{ glm::vec3{8 * 64.f, 4* 64.f, 0.f}, glm::vec2{64.f, 64.f}, Enums::ColliderType::Floor});

	chunk.colliderInfo.push_back(File::Asset::Resource::Template::ColliderTemplate{ glm::vec3{0.f, 0.f, 0.f}, glm::vec2{256.f, 64.f}, Enums::ColliderType::Wall});
	chunk.colliderInfo.push_back(File::Asset::Resource::Template::ColliderTemplate{ glm::vec3{256.f, 0.f, 0.f}, glm::vec2{256.f, 64.f}, Enums::ColliderType::Wall});
	chunk.colliderInfo.push_back(File::Asset::Resource::Template::ColliderTemplate{ glm::vec3{2* 256.f, 0.f, 0.f}, glm::vec2{256.f, 64.f}, Enums::ColliderType::Wall});
	chunk.colliderInfo.push_back(File::Asset::Resource::Template::ColliderTemplate{ glm::vec3{3* 256.f, 0.f, 0.f}, glm::vec2{256.f, 64.f}, Enums::ColliderType::Wall});
	chunk.colliderInfo.push_back(File::Asset::Resource::Template::ColliderTemplate{ glm::vec3{4* 256.f, 0.f, 0.f}, glm::vec2{256.f, 64.f}, Enums::ColliderType::Wall});

	chunk.colliderInfo.push_back(File::Asset::Resource::Template::ColliderTemplate{ glm::vec3{0.f, -64.f, 1.f}, glm::vec2{256.f, 128.f}, Enums::ColliderType::Floor });
	chunk.colliderInfo.push_back(File::Asset::Resource::Template::ColliderTemplate{ glm::vec3{1*256.f, -64.f, 1.f}, glm::vec2{256.f, 128.f}, Enums::ColliderType::Floor });
	chunk.colliderInfo.push_back(File::Asset::Resource::Template::ColliderTemplate{ glm::vec3{2*256.f, -64.f, 1.f}, glm::vec2{256.f, 128.f}, Enums::ColliderType::Floor });
	chunk.colliderInfo.push_back(File::Asset::Resource::Template::ColliderTemplate{ glm::vec3{3*256.f, -64.f, 1.f}, glm::vec2{256.f, 128.f}, Enums::ColliderType::Floor });
	chunk.colliderInfo.push_back(File::Asset::Resource::Template::ColliderTemplate{ glm::vec3{4*256.f, -64.f, 1.f}, glm::vec2{256.f, 128.f}, Enums::ColliderType::Floor });
	chunk.colliderInfo.push_back(File::Asset::Resource::Template::ColliderTemplate{ glm::vec3{9*256.f, 6* 64.f, 1.f}, glm::vec2{256.f, 256.f}, Enums::ColliderType::Floor });

	chunk.colliderInfo.push_back(File::Asset::Resource::Template::ColliderTemplate{ glm::vec3{128.f, 128.f, 1.f}, glm::vec2{128.f, 128.f}, Enums::ColliderType::Floor, true });
	chunk.colliderInfo.push_back(File::Asset::Resource::Template::ColliderTemplate{ glm::vec3{512.f + 64.f, 256.f + 64.f, 1.f}, glm::vec2{256.f, 256.f}, Enums::ColliderType::Floor });
	chunk.colliderInfo.push_back(File::Asset::Resource::Template::ColliderTemplate{ glm::vec3{512.f + 64.f, 256.f, 0.f}, glm::vec2{256.f, 64.f}, Enums::ColliderType::NToSRamp });
	chunk.colliderInfo.push_back(File::Asset::Resource::Template::ColliderTemplate{ glm::vec3{512.f + 64.f, 576.f, 0.f}, glm::vec2{256.f, 64.f}, Enums::ColliderType::SToNRamp });
	
	chunk.colliderInfo.push_back(File::Asset::Resource::Template::ColliderTemplate{ glm::vec3{512.f, 256.f + 64.f , 0.f}, glm::vec2{64.f, 256.f}, Enums::ColliderType::EToWRamp });
	chunk.colliderInfo.push_back(File::Asset::Resource::Template::ColliderTemplate{ glm::vec3{512.f + 256.f + 64.f, 256.f + 64.f, 0.f}, glm::vec2{64.f, 256.f}, Enums::ColliderType::WToERamp });

	chunk.colliderInfo.push_back(File::Asset::Resource::Template::ColliderTemplate{ glm::vec3{5 * 64.f, 9 * 64.f, 0.f}, glm::vec2{256.f, 256.f}, Enums::ColliderType::Floor });
	chunk.colliderInfo.push_back(File::Asset::Resource::Template::ColliderTemplate{ glm::vec3{5 * 64.f, 13 * 64.f, 0.f}, glm::vec2{256.f, 256.f}, Enums::ColliderType::Floor });
	chunk.colliderInfo.push_back(File::Asset::Resource::Template::ColliderTemplate{ glm::vec3{5 * 64.f, 17 * 64.f, 0.f}, glm::vec2{256.f, 192.f}, Enums::ColliderType::Floor });

	chunk.colliderInfo.push_back(File::Asset::Resource::Template::ColliderTemplate{ glm::vec3{1 * 64.f, 9 * 64.f, 0.f}, glm::vec2{256.f, 256.f}, Enums::ColliderType::Floor });
	chunk.colliderInfo.push_back(File::Asset::Resource::Template::ColliderTemplate{ glm::vec3{1 * 64.f, 13 * 64.f, 0.f}, glm::vec2{256.f, 256.f}, Enums::ColliderType::Floor });
	chunk.colliderInfo.push_back(File::Asset::Resource::Template::ColliderTemplate{ glm::vec3{1 * 64.f, 17 * 64.f, 0.f}, glm::vec2{256.f, 192.f}, Enums::ColliderType::Floor });

	chunk.colliderInfo.push_back(File::Asset::Resource::Template::ColliderTemplate{ glm::vec3{9 * 64.f, 9 * 64.f, 0.f}, glm::vec2{256.f, 256.f}, Enums::ColliderType::Floor });
	chunk.colliderInfo.push_back(File::Asset::Resource::Template::ColliderTemplate{ glm::vec3{9 * 64.f, 13 * 64.f, 0.f}, glm::vec2{256.f, 256.f}, Enums::ColliderType::Floor });
	chunk.colliderInfo.push_back(File::Asset::Resource::Template::ColliderTemplate{ glm::vec3{9 * 64.f, 17 * 64.f, 0.f}, glm::vec2{256.f, 128.f}, Enums::ColliderType::Floor });

	chunk.colliderInfo.push_back(File::Asset::Resource::Template::ColliderTemplate{ glm::vec3{13 * 64.f, 1 * 64.f, 0.f}, glm::vec2{256.f + 128, 256.f}, Enums::ColliderType::Floor });
	chunk.colliderInfo.push_back(File::Asset::Resource::Template::ColliderTemplate{ glm::vec3{14 * 64.f, 5 * 64.f, 0.f}, glm::vec2{ 256.f + 64, 256.f}, Enums::ColliderType::Floor });
	chunk.colliderInfo.push_back(File::Asset::Resource::Template::ColliderTemplate{ glm::vec3{13 * 64.f, 9 * 64.f, 0.f}, glm::vec2{256.f + 128, 256.f}, Enums::ColliderType::Floor });
	chunk.colliderInfo.push_back(File::Asset::Resource::Template::ColliderTemplate{ glm::vec3{13 * 64.f, 13 * 64.f, 0.f}, glm::vec2{256.f + 128, 256.f}, Enums::ColliderType::Floor });
	chunk.colliderInfo.push_back(File::Asset::Resource::Template::ColliderTemplate{ glm::vec3{13 * 64.f, 17 * 64.f, 0.f}, glm::vec2{256.f + 128, 192.f}, Enums::ColliderType::Floor });
	chunk.colliderInfo.push_back(File::Asset::Resource::Template::ColliderTemplate{ glm::vec3{13 * 64.f, 17 * 64.f, 0.f}, glm::vec2{256.f + 128 + 10240, 192.f + 10240 }, Enums::ColliderType::Floor });
	//colliderChunks.add(chunk);
	theManager.archive.add(new File::Asset::Resource::Template::ColliderChunk(chunk));
	wi.colliderInfo.push_back(chunk.getModfile());


	File::Asset::Resource::Template::TileChunk tchunk;
	tchunk.fromMod = mod;
	tchunk.objectType = of::file::ObjectType::TileChunk;
	//tiles.clear();
	isLoading = true;
		//for (float f = 1; f < 20; f++)
		for (float f2 = 1; f2 < 20; f2++)
		{

			tchunk.ID = of::common::uuid();
			tchunk.tileInfo.clear();
			tchunk.layer = 0;
			tchunk.group = "Default";
			tchunk.tileInfo.push_back(File::Asset::Resource::Template::TileTemplate{ glm::vec3{ -1 * 64.f, f2 * 64.f , 0.f }, "Ground",  Enums::TileTypes::Ground, false });
			tchunk.tileInfo.push_back(File::Asset::Resource::Template::TileTemplate{ glm::vec3{ 0 * 64.f, f2 * 64.f  , 0.f }, "Ground",  Enums::TileTypes::Ground, false });
			tchunk.tileInfo.push_back(File::Asset::Resource::Template::TileTemplate{ glm::vec3{ 1 * 64.f, f2 * 64.f  , 0.f }, "Ground",  Enums::TileTypes::Ground, false });
			tchunk.tileInfo.push_back(File::Asset::Resource::Template::TileTemplate{ glm::vec3{ 2 * 64.f, f2 * 64.f  , 0.f }, "Ground",  Enums::TileTypes::Ground, false });
			tchunk.tileInfo.push_back(File::Asset::Resource::Template::TileTemplate{ glm::vec3{ 3 * 64.f, f2 * 64.f  , 0.f }, "Ground",  Enums::TileTypes::Ground, false });
			tchunk.tileInfo.push_back(File::Asset::Resource::Template::TileTemplate{ glm::vec3{ 4 * 64.f, f2 * 64.f  , 0.f }, "Ground",  Enums::TileTypes::Ground, false });
			tchunk.tileInfo.push_back(File::Asset::Resource::Template::TileTemplate{ glm::vec3{ 5 * 64.f, f2 * 64.f  , 0.f }, "Ground",  Enums::TileTypes::Ground, false });
			tchunk.tileInfo.push_back(File::Asset::Resource::Template::TileTemplate{ glm::vec3{ 6 * 64.f, f2 * 64.f  , 0.f }, "Ground",  Enums::TileTypes::Ground, false });
			tchunk.tileInfo.push_back(File::Asset::Resource::Template::TileTemplate{ glm::vec3{ 7 * 64.f, f2 * 64.f  , 0.f }, "Ground",  Enums::TileTypes::Ground, false });
			tchunk.tileInfo.push_back(File::Asset::Resource::Template::TileTemplate{ glm::vec3{ 8 * 64.f, f2 * 64.f  , 0.f }, "Ground",  Enums::TileTypes::Ground, false });
			tchunk.tileInfo.push_back(File::Asset::Resource::Template::TileTemplate{ glm::vec3{ 13 * 64.f, f2 * 64.f , 0.f }, "Ground",  Enums::TileTypes::Ground, false });
			tchunk.tileInfo.push_back(File::Asset::Resource::Template::TileTemplate{ glm::vec3{ 14 * 64.f, f2 * 64.f , 0.f }, "Ground",  Enums::TileTypes::Ground, false });
			tchunk.tileInfo.push_back(File::Asset::Resource::Template::TileTemplate{ glm::vec3{ 15 * 64.f, f2 * 64.f , 0.f }, "Ground",  Enums::TileTypes::Ground, false });
			tchunk.tileInfo.push_back(File::Asset::Resource::Template::TileTemplate{ glm::vec3{ 16 * 64.f, f2 * 64.f , 0.f }, "Ground",  Enums::TileTypes::Ground, false });
			tchunk.tileInfo.push_back(File::Asset::Resource::Template::TileTemplate{ glm::vec3{ 17 * 64.f, f2 * 64.f , 0.f }, "Ground",  Enums::TileTypes::Ground, false });
			tchunk.tileInfo.push_back(File::Asset::Resource::Template::TileTemplate{ glm::vec3{ 18 * 64.f, f2 * 64.f , 0.f }, "Ground",  Enums::TileTypes::Ground, false });
			
			theManager.archive.add(new File::Asset::Resource::Template::TileChunk(tchunk));
			wi.tileInfo.push_back(tchunk.getModfile());

		}
		for (float f2 = 1; f2 < 4; f2++)
		{
			tchunk.ID = of::common::uuid();
			tchunk.tileInfo.clear();
			tchunk.tileInfo.push_back(File::Asset::Resource::Template::TileTemplate{ glm::vec3{9 * 64.f, f2 * 64.f , 0.f }, "Ground",  Enums::TileTypes::Ground, false });
			tchunk.tileInfo.push_back(File::Asset::Resource::Template::TileTemplate{ glm::vec3{10 * 64.f, f2 * 64.f  , 0.f }, "Ground",  Enums::TileTypes::Ground, false });				  
			tchunk.tileInfo.push_back(File::Asset::Resource::Template::TileTemplate{ glm::vec3{11 * 64.f, f2 * 64.f  , 0.f }, "Ground",  Enums::TileTypes::Ground, false });				  
			tchunk.tileInfo.push_back(File::Asset::Resource::Template::TileTemplate{ glm::vec3{12 * 64.f, f2 * 64.f  , 0.f }, "Ground",  Enums::TileTypes::Ground, false });				  

			theManager.archive.add(new File::Asset::Resource::Template::TileChunk(tchunk));
			wi.tileInfo.push_back(tchunk.getModfile());
			
		}
		tchunk.layer = 1;

		for (float f2 = 6; f2 < 9; f2++)
		{
			tchunk.ID = of::common::uuid();
			tchunk.tileInfo.clear();
			tchunk.tileInfo.push_back(File::Asset::Resource::Template::TileTemplate{ glm::vec3{9 * 64.f, f2 * 64.f , 1.f }, "Ground",  Enums::TileTypes::Ground, false });
			tchunk.tileInfo.push_back(File::Asset::Resource::Template::TileTemplate{ glm::vec3{10 * 64.f, f2 * 64.f  , 1.f }, "Ground",  Enums::TileTypes::Ground, false });
			tchunk.tileInfo.push_back(File::Asset::Resource::Template::TileTemplate{ glm::vec3{11 * 64.f, f2 * 64.f  , 1.f }, "Ground",  Enums::TileTypes::Ground, false });
			tchunk.tileInfo.push_back(File::Asset::Resource::Template::TileTemplate{ glm::vec3{12 * 64.f, f2 * 64.f  , 1.f }, "Ground",  Enums::TileTypes::Ground, false });

			theManager.archive.add(new File::Asset::Resource::Template::TileChunk(tchunk));
			wi.tileInfo.push_back(tchunk.getModfile());
		
		}
		tchunk.layer = 0;

		for (float f2 = 9; f2 < 20; f2++)
		{
			tchunk.ID = of::common::uuid();
			tchunk.tileInfo.clear();
			tchunk.tileInfo.push_back(File::Asset::Resource::Template::TileTemplate{ glm::vec3{9 * 64.f, f2 * 64.f , 0.f },  "Ground",  Enums::TileTypes::Ground, false });
			tchunk.tileInfo.push_back(File::Asset::Resource::Template::TileTemplate{ glm::vec3{10 * 64.f, f2 * 64.f  , 0.f }, "Ground",  Enums::TileTypes::Ground, false });
			tchunk.tileInfo.push_back(File::Asset::Resource::Template::TileTemplate{ glm::vec3{11 * 64.f, f2 * 64.f  , 0.f }, "Ground",  Enums::TileTypes::Ground, false });
			tchunk.tileInfo.push_back(File::Asset::Resource::Template::TileTemplate{ glm::vec3{12 * 64.f, f2 * 64.f  , 0.f }, "Ground",  Enums::TileTypes::Ground, false });

			theManager.archive.add(new File::Asset::Resource::Template::TileChunk(tchunk));
			wi.tileInfo.push_back(tchunk.getModfile());
		}
	
	tchunk.ID = of::common::uuid();
	tchunk.tileInfo.clear();
	for (float f = 0; f < 20; f++)
	{

		tchunk.tileInfo.push_back(File::Asset::Resource::Template::TileTemplate{ glm::vec3{f * 64.f, 0.f , 0.f },  "GroundWall",  Enums::TileTypes::Wall, false });
		tchunk.tileInfo.push_back(File::Asset::Resource::Template::TileTemplate{ glm::vec3{f * 64.f, 1024.f, 0.f },  "GroundWall",  Enums::TileTypes::Wall, false });

	}
	
	for (float f = 1; f < 20; f++)
	{
		tchunk.tileInfo.push_back(File::Asset::Resource::Template::TileTemplate{ glm::vec3{0.f, f * 64.f , 0.f }, "Wall",  Enums::TileTypes::Wall, true });
	}
	theManager.archive.add(new File::Asset::Resource::Template::TileChunk(tchunk));
	wi.tileInfo.push_back(tchunk.getModfile());

	tchunk.ID = of::common::uuid();
	tchunk.tileInfo.clear();
	tchunk.layer = 1;
	for (float f = 0; f < 20; f++)
	{

		tchunk.tileInfo.push_back(File::Asset::Resource::Template::TileTemplate{ glm::vec3{f * 64.f, -64.f, 1.f },  "Ground",  Enums::TileTypes::Ground, false });
		tchunk.tileInfo.push_back(File::Asset::Resource::Template::TileTemplate{ glm::vec3{f * 64.f,  0.f, 1.f }, "GroundWall",  Enums::TileTypes::Ground, false });
	}
	theManager.archive.add(new File::Asset::Resource::Template::TileChunk(tchunk));
	wi.tileInfo.push_back(tchunk.getModfile());
	
	tchunk.ID = of::common::uuid();
	tchunk.tileInfo.clear();
	tchunk.group = "Island";
	tchunk.tileInfo.push_back(File::Asset::Resource::Template::TileTemplate{ glm::vec3{128.f, 128.f, 1.f }, "Ground",  Enums::TileTypes::Ground, true });
	tchunk.tileInfo.push_back(File::Asset::Resource::Template::TileTemplate{ glm::vec3{128.f, 128.f + 64.f, 1.f }, "Ground",  Enums::TileTypes::Ground, true });
	tchunk.tileInfo.push_back(File::Asset::Resource::Template::TileTemplate{ glm::vec3{128.f + 64.f, 128.f + 64.f, 1.f }, "Ground",  Enums::TileTypes::Ground, true });
	tchunk.tileInfo.push_back(File::Asset::Resource::Template::TileTemplate{ glm::vec3{128.f + 64.f, 128.f, 1.f }, "Ground",  Enums::TileTypes::Ground, true });
	tchunk.chunkTransparency = File::Asset::Resource::Template::TransparencyInfo{ true, glm::vec3{128.f, 128.f,  1.f},  glm::vec2{128.f , 128.f } };
	theManager.archive.add(new File::Asset::Resource::Template::TileChunk(tchunk));
	wi.tileInfo.push_back(tchunk.getModfile());

	auto greetings = Asset::Resource::DialogOption{ of::common::uuid(), { {1,2}, {3,4}, {7,8}}, nullptr, nullptr, Enums::DialogStatus::Open, "Hello traveller!" };
	auto playerResponse = Asset::Resource::DialogOption{ of::common::uuid(), { }, nullptr, nullptr, Enums::DialogStatus::Open, "Good day" };
	auto npcResponse = Asset::Resource::DialogOption{ of::common::uuid(), { {5,5}}, nullptr, nullptr, Enums::DialogStatus::Open, "I hope you're having a good day!" };
	auto playerResponse2 = Asset::Resource::DialogOption{ of::common::uuid(), { }, nullptr, nullptr, Enums::DialogStatus::Open, "Wassup? " };
	auto npcResponse2 = Asset::Resource::DialogOption{ of::common::uuid(), { {5,6} }, nullptr, nullptr, Enums::DialogStatus::Open, "Not much... just added here as a testing dummy" };
	auto exitDialog = Asset::Resource::DialogOption{ of::common::uuid(), { }, nullptr, nullptr, Enums::DialogStatus::Close, "Ok, Bye..." };
	auto exitDialog2 = Asset::Resource::DialogOption{ of::common::uuid(), { }, nullptr, nullptr,Enums::DialogStatus::Close, "Bye..." };

	auto nested1 = Asset::Resource::DialogOption{ of::common::uuid(), { {-1, 9} }, nullptr, nullptr, Enums::DialogStatus::Open, "Nested Test" };
	auto nested2 = Asset::Resource::DialogOption{ of::common::uuid(), { {-1, 7}}, nullptr, nullptr,Enums::DialogStatus::Open, "Nested 2" };
	auto nested3 = Asset::Resource::DialogOption{ of::common::uuid(), { {5, 6}}, nullptr, nullptr, Enums::DialogStatus::Open, "Nested 3" };


	std::unordered_map<size_t, Asset::Resource::DialogOption> opt{
		{0, greetings},
		{1, playerResponse},
		{2, npcResponse},
		{3, playerResponse2},
		{4, npcResponse2},
		{5, exitDialog},
		{6, exitDialog},
		{7, nested1},
		{8, nested2},
		{9, nested3}
	};
	Asset::Resource::DialogTree dt(opt);
	dt.objectType = of::file::ObjectType::DialogTree;
	dt.fromMod = mod;
	dt.ID = of::common::uuid();

	theManager.archive.add(new Asset::Resource::DialogTree(dt));
	dialogTest = dt.getModfile();

	gfx.addRenderable(0, "Default", { 1024.f + 64, 128.f}, 0.f, "WaterTop", Enums::TileTypes::Ground, true);
	gfx.addRenderable(0, "Default", { 1024.f, 128.f }, 0.f, "WaterTopLeft", Enums::TileTypes::Ground, true);
	
	objectHandler.player->getComponent<of::object::component::Transform>()->pos.x = 50.f;
	objectHandler.player->getComponent<of::object::component::Transform>()->pos.y = -15.f;

	auto dialog = objectHandler.objects[testObjectId].getComponent<Dialog>();
	dialog->dialogTreeuuid = dialogTest;
	dialog->dialogTree = of::engine::GetModule<of::file::Handler>().archive.requestUniqueInstance<Asset::Resource::DialogTree>(dialogTest);

	Combat::Element e;
	e.objectType = of::file::ObjectType::Element;
	e.name = "Testelement";
	e.fromMod = mod;
	e.elementAttributes[e.getModfile()] = 1.0;

	theManager.archive.add(new Combat::Element(e));

	Combat::Effect ef;
	ef.objectType = of::file::ObjectType::Effect;
	ef.effectTime.maxTime = 10.f;
	ef.effectElememtId = e.getModfile();
	ef.effectType = Enums::EffectType::TickDamage;
	ef.theEffect = std::shared_ptr<Combat::DamageEffect>(new Combat::DamageEffect(1, Enums::Attribute::Power, 0.4));
	ef.tickDelay.maxTime = .1f;
	ef.fromMod = mod;
	theManager.archive.add(new Combat::Effect(ef));

	ef.effectType = Enums::EffectType::Barrier;
	ef.theEffect = std::shared_ptr<Combat::BarrierEffect>(new Combat::BarrierEffect(2, 20));
	ef.effectTime.maxTime = 2.f;
	ef.tickDelay.maxTime = 1.f;

	auto ef2 = ef;
	ef2.ID = of::common::uuid();
	theManager.archive.add(new Combat::Effect(ef2));
	Asset::Resource::Prefab p;
	p.objectType = of::file::ObjectType::Prefab;
	of::object::component::Damage d = of::object::component::Damage();
	d.canLockNextFrame = false;
	d.maxTargets = 1;
	d.speed = 0.f;
	//d.effectsIds.push_back(ef.getModfile());
	d.timeToLive.maxTime = 2.f;
	d.elementId = e.getModfile();
	d.damageCoef = 1.0;
	p.components.push_back(std::make_unique<of::object::component::Damage>(d));
	p.fromMod = mod;

	theManager.archive.add(new Asset::Resource::Prefab(p));

	Combat::Skill s;
	s.objectType = of::file::ObjectType::Skill;
	s.animation = "foo";
	s.coolDown.maxTime = 1.f;
	s.summonPoint = 100.f;
	s.fromMod = mod;
	s.elementId = e.getModfile();
	s.prefabId = p.getModfile();
	s.skillExecutionEffectIds.push_back(ef2.getModfile());
	s.iconTextureName = "SkillIconFrame.png";

	theManager.archive.add(new Combat::Skill(s));


	isLoading = false;
	setCurrentTime(12.f);
	theManager.archive.add(new File::Asset::Resource::Template::WorldInstance(wi));

	of::file::Header mh;
	mh.name = "Default";
	mh.modVersion = OneVersion(1, 0, 0);
	theManager.saveGameDatabase(mh.name, mh);
	of::engine::GetModule<of::file::Loader>().loadOrder.insert({ mh.name, 0 });
	theManager.archive.clear();
	loadWorldInstance(wi.getModfile(), {}, { 50.f, -15.f , 1.f});
	auto eff = theManager.archive.requestUniqueInstance<Combat::Effect>(ef.getModfile());
	auto eff2 = theManager.archive.requestUniqueInstance<Combat::Effect>(ef2.getModfile());
	auto elm = theManager.archive.request<Combat::Element>(e.getModfile());
	objectHandler.player->getComponent<of::object::component::Stats>()->attunedTo = *elm;
	objectHandler.player->getComponent<of::object::component::Stats>()->doEffects({ eff, eff2 }, objectHandler.player->getSharedComponent<of::object::component::Stats>());
	auto skill = theManager.archive.requestUniqueInstance<Combat::Skill>(s.getModfile());
	objectHandler.player->getComponent<of::object::component::CombatComponent>()->skills[Enums::CombatSkill::Primary] = skill;
	objectHandler.player->getComponent<of::object::component::CombatComponent>()->skills[Enums::CombatSkill::Secondary] = skill;
	objectHandler.player->getComponent<of::object::component::CombatComponent>()->skills[Enums::CombatSkill::Special] = skill;

}

void WorldManager::setCurrentTime(const float& currentTime)
{

	while (gfx.timeOfDay < currentTime || gfx.timeOfDay > currentTime + 0.5f)
		Simulate(12.f);
}

void WorldManager::newGame()
{
	of::engine::GetModule<of::module::logger::OneLogger>().getLogger("WorldManager").Info("New Game");
	saveFile.newGame(of::resource::DifficultyLevel::Normal, of::common::uuid::nil(), {});
	auto& glob = of::engine::GetModule<Globals>();
	loadWorldInstance(glob.newGameWorldInstance, glob.newGameWorldInstanceLoadingScreen, glob.newGamePoint);
}

void WorldManager::save(const of::common::String& fileName)
{
	of::engine::GetModule<of::module::logger::OneLogger>().getLogger("WorldManager").Info("Save Game");
	saveFile.currentZone = loadHandler.getCurrentWorld();
	saveFile.loadingScreen = loadHandler.getCurrentLoadingScreen();
	saveFile.save(fileName);
}

void WorldManager::load(const of::common::String& fileName)
{
	of::engine::GetModule<of::module::logger::OneLogger>().getLogger("WorldManager").Info("Load Game");
	isLoading = true;
	saveFile.load(fileName);
	loadWorldInstance(saveFile.currentZone, saveFile.loadingScreen, saveFile.point);
	// TODO: start timers from questing module if needed
}

void WorldManager::loadWorldInstance(const of::file::FileId& world, const of::file::FileId& loadingScreen, const glm::vec3& playerPosition)
{
	isLoading = true;
	EngineModule::Time& time = of::engine::GetModule<EngineModule::Time>();
	time.getTimer(Globals::LOADING_TIMER).reset();
	time.getTimer(Globals::TOTAL_TIME_LOADED).reset();

	loadHandler.beginLoad(world, loadingScreen, playerPosition);

}

void WorldManager::Update()
{
	if (isLoading)
	{
		auto timer = of::engine::GetModule<EngineModule::Time>().getTimer(Globals::LOADING_TIMER);
		timer.reset();
		while (timer.secondsAsFloat() < 0.05f && isLoading)
		{
			loadHandler.load();
		}
	}
}

void WorldManager::Simulate(const float& fElapsedTime)
{
	doDayCycle(fElapsedTime);
	objectHandler.processDeletedObjects(fElapsedTime);
}
