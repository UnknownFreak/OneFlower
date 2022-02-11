#include "WorldManager.hpp"
#include <Input/InputHandler.hpp>

#include <Module/Globals.hpp>
#include <Module/OneTime.hpp>

#include <Physics/Physics.hpp>

#include <Object/BaseComponent.hpp>
#include <Object/IBaseComponent.hpp>

#include <Interfaces/ICollider.hpp>
#include <Physics/Colliders/TileCollider.hpp>
#include <Physics/Colliders/EntityCollider.hpp>
#include <File/Resource/TileAtlas.hpp>

#include <Helpers/Enum/TileTypes.hpp>

#include <File/Template/WorldInstance.hpp>
#include <File/Template/TileTemplate.hpp>
#include <File/Template/ColliderTemplate.hpp>
#include <File/Resource/Prefab.hpp>

#include <Graphics/Render.hpp>
#include <Graphics/Dialog.hpp>
#include <Graphics/PlayerInteractionPrompt.hpp>

#include <Graphics/UI/PlayerStats.hpp>

#include <Physics/Colliders/VisionCollider.hpp>
#include <Physics/Colliders/EntityCollider.hpp>
#include <Combat/Stats.hpp>
#include <Combat/Effect.hpp>
#include <Combat/Element.hpp>
#include <Combat/Damage.hpp>


#include <Object/ObjectInstanceHandler.hpp>
#include <Object/GameObject.hpp>

#include <Module/Globals.hpp>

File::Mod::ModFileUUIDHelper dialogTest;
Core::uuid testObjectId;

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
	sf::Uint8 time = (sf::Uint8)(std::abs(std::sin(gfx.timeOfDay / 8.f)) * 255);
	if (time < 64)
		time = 64;
	gfx.currentDayColor = sf::Color(time, time, time);
	//std::cout << "Brightness of day (0-255): " << int(time) << std::endl;
	//float whole, fractional;
	//fractional = std::modf(gfx.timeOfDay, &whole);
	//std::cout << "time of day: " << int(whole) << "h " << int(fractional*60) << "m " << int(fractional*3600) % 60 << "s" << std::endl;
	//std::cout << "shadowAngle: " << gfx.shadowAngle << std::endl;
	//std::cout << "shadow length x: " << gfx.shadowLengthX << std::endl;
	//std::cout << "shadow length y: " << gfx.shadowLengthY << std::endl;
}

WorldManager::WorldManager(Graphics::RenderWindow& gfx) : gfx(gfx), loadHandler(gfx, isLoading), objectHandler(Engine::GetModule<EngineModule::ObjectInstanceHandler>()), saveFile(Engine::GetModule<File::SaveFile>())
{
	newGame();
	auto& f = Engine::GetModule<Input::InputHandler>();

	auto* go = objectHandler.addObject();
	testObjectId = go->id;
	go->getComponent<Component::Transform>()->pos = { 150, 250.f, 0.f };
	go->addComponent<Render>();
	go->addComponent<Dialog>();
	
	go->getComponent<Collider>()->colliderType = Enums::ColliderType::StaticEntity;
	go->getComponent<Collider>()->hitboxOffset = { 8.f, 32.f };


	f.uiKeyboard.RegisterCallback(Input::Callback::KeyboardCallback("Console", [&](bool, sf::Keyboard::Key, const float&) {gfx.ui.ToggleConsole(); f.togglePlayerInput(); }, false), sf::Keyboard::Key::F1, Enums::Input::Action::Press);

	f.uiKeyboard.RegisterCallback(Input::Callback::KeyboardCallback("GlobalFlag", [&](bool, sf::Keyboard::Key, const float&) {
		Engine::GetModule<Globals>().boolGlobals[Globals::GLOBAL_DRAW_HITBOX] = !Engine::GetModule<Globals>().boolGlobals[Globals::GLOBAL_DRAW_HITBOX];
		}, false), sf::Keyboard::Key::F2, Enums::Input::Action::Press);

	f.playerKeyboard.RegisterCallback(Input::Callback::KeyboardCallback("NewGame", [&](bool, sf::Keyboard::Key, const float&) {
		newGame();
		}, false), sf::Keyboard::Key::Num1, Enums::Input::Action::Press);

	f.playerKeyboard.RegisterCallback(Input::Callback::KeyboardCallback("SaveGame", [&](bool, sf::Keyboard::Key, const float&) {
		save("Test.save");
		}, false), sf::Keyboard::Key::Num2, Enums::Input::Action::Press);
	f.playerKeyboard.RegisterCallback(Input::Callback::KeyboardCallback("LoadGame", [&](bool, sf::Keyboard::Key, const float&) {
		load("Test.save");
		}, false), sf::Keyboard::Key::Num3, Enums::Input::Action::Press);

	auto& console = Engine::GetModule<Console>();
	console.registerCommand("qtt", [&](const Core::String& arg)
		{
			Engine::GetModule<EngineModule::Logger::OneLogger>().Info("Quadtree test begin");
			try
			{
				const auto count = std::stoi(arg);
				isLoading = true;
				for (auto i = 0; i < count; i++)
				{
					auto* go = objectHandler.addObject();
					auto& randomGen = Engine::GetModule<EngineModule::RandomGen>();
					go->getComponent<Component::Transform>()->pos = {
						randomGen.random_float(-100000.f, 100000.f),
						randomGen.random_float(-100000.f, 100000.f), 0.f };
					go->addComponent<Render>();
					go->getComponent<Collider>()->colliderType = Enums::ColliderType::StaticEntity;
					go->getComponent<Collider>()->hitboxOffset = { 8.f, 32.f };
					go->getComponent<Collider>()->Update();
				}
				isLoading = false;
				Engine::GetModule<EngineModule::Logger::OneLogger>().Info("Quadtree finished spwning");
			}
			catch (...)
			{
				Engine::GetModule<EngineModule::Logger::OneLogger>().Error("Failed to execture command Quadtree test");

			}
		});

	console.registerCommand("wt", [&](const Core::String& )
		{
			Engine::GetModule<EngineModule::Logger::OneLogger>().Info("Wall test spawn");
			isLoading = true;

			gfx.addHitbox(std::make_unique<TileCollider>(Core::Vector3f{ 512.f, 720, 0.f }, Core::Vector2f{256.f, 64.f}, Enums::ColliderType::Wall, false), 1, "WallTest");

			gfx.addHitbox(std::make_unique<TileCollider>(Core::Vector3f{ 720.f, 720.f, 0.f }, Core::Vector2f{ 64.f, 256.f }, Enums::ColliderType::Wall, false), 1, "WallTest");

			isLoading = false;

				
		});

	console.registerCommand("e", [&](const Core::String&)
		{
			Engine::GetModule<EngineModule::Logger::OneLogger>().Info("Entity");
				isLoading = true;
				{
					auto* go = objectHandler.addObject();
					go->getComponent<Component::Transform>()->pos = {150.f, 250.f, 0.f };
					go->addComponent<Render>();
					go->getComponent<Collider>()->colliderType = Enums::ColliderType::StaticEntity;
					go->getComponent<Collider>()->hitboxOffset = { 8.f, 32.f };
					go->getComponent<Collider>()->Update();
				}
				isLoading = false;
		});

	//f.uiKeyboard.RegisterCallback(Input::Callback::KeyboardCallback("ReloadShader", [&](bool, sf::Keyboard::Key, const float&) {
	//	gfx.reloadShader();
	//	std::cout << "Reloading shader" << std::endl;
	//	}, false), sf::Keyboard::Key::Num3, Enums::Input::Action::Press);

}

WorldManager::WorldManager(const WorldManager& copy): gfx(copy.gfx), objectHandler(Engine::GetModule<EngineModule::ObjectInstanceHandler>()), loadHandler(copy.gfx, isLoading), saveFile(Engine::GetModule<File::SaveFile>())
{
}

void WorldManager::createSimpleWorld()
{
	const auto mod = "Default";
	gfx.clearDrawList();
	TileAtlas ta;
	ta.fromMod = mod;
	ta.name = "tilemap-superflat2-256.png";
	ta.name = "Exterior.png";
	ta.objectType = Enums::ObjectType::TileAtlas;
	ta.addAtlasPos("Wall", {64, 0});
	//ta.addAtlasPos("Wall", {256, 0});
	//ta.addAtlasPos("Ground", {0, 64});
	ta.addAtlasPos("Ground", {64, 64});
	//ta.addAtlasPos("GroundWall", {0, 0});
	ta.addAtlasPos("GroundWall", {128, 192});
	ta.addAtlasPos("WallGround", {0, 192});
	ta.addAtlasPos("Water", {192, 128});
	ta.addAtlasPos("WaterTopLeft", {128, 64});
	ta.addAtlasPos("WaterTop", {192, 64});

	std::unique_ptr<TileAtlas> t(new TileAtlas(ta));


	auto& theManager = Engine::GetModule<Asset::AssetManager>();
	//auto& atlasMgr = theManager.getTileAtlas();
	//atlasMgr.add(ta);
	theManager.requestor.add(t.release());
	File::Mod::ModFileUUIDHelper atlas = ta.getModfile();

	//theManager.test.add(t.get());

	//auto& worldInstance = theManager.getWorldInstance();
	//auto& colliderChunks = theManager.getColliderChunks();
	//auto& tileChunks = theManager.getTileChunks();

	WorldInstance wi;
	wi.objectType = Enums::ObjectType::WorldInstance;
	wi.fromMod = mod;
	wi.tileAtlases.push_back(atlas);

	ColliderChunk chunk;
	
	chunk.objectType = Enums::ObjectType::ColliderChunk;
	chunk.fromMod = mod;
	/// <summary>
	/// Core::Vector2f size;
	/// Enums::ColliderType type;
	/// size_t layer;
	/// Core::String group;
	/// </summary>
	chunk.layer = 0;
	chunk.group = "Default";
	chunk.colliderInfo.push_back(ColliderTemplate{ Core::Vector3f{64.f, 64.f, 0.f}, Core::Vector2f{256.f, 256.f}, Enums::ColliderType::Floor});
	chunk.colliderInfo.push_back(ColliderTemplate{ Core::Vector3f{64.f + 256.f, 64.f, 0.f}, Core::Vector2f{192.f, 256.f}, Enums::ColliderType::Floor});
	chunk.colliderInfo.push_back(ColliderTemplate{ Core::Vector3f{64.f, 64.f + 256.f, 0.f}, Core::Vector2f{256.f, 256.f}, Enums::ColliderType::Floor});
	chunk.colliderInfo.push_back(ColliderTemplate{ Core::Vector3f{64.f + 256.f, 64.f + 256.f, 0.f}, Core::Vector2f{192.f, 256.f}, Enums::ColliderType::Floor});
	chunk.colliderInfo.push_back(ColliderTemplate{ Core::Vector3f{8 * 64.f, 64.f, 0.f}, Core::Vector2f{64.f * 5, 192.f}, Enums::ColliderType::Floor});
	chunk.colliderInfo.push_back(ColliderTemplate{ Core::Vector3f{8 * 64.f, 4* 64.f, 0.f}, Core::Vector2f{64.f, 64.f}, Enums::ColliderType::Floor});

	chunk.colliderInfo.push_back(ColliderTemplate{ Core::Vector3f{0.f, 0.f, 0.f}, Core::Vector2f{256.f, 64.f}, Enums::ColliderType::Wall});
	chunk.colliderInfo.push_back(ColliderTemplate{ Core::Vector3f{256.f, 0.f, 0.f}, Core::Vector2f{256.f, 64.f}, Enums::ColliderType::Wall});
	chunk.colliderInfo.push_back(ColliderTemplate{ Core::Vector3f{2* 256.f, 0.f, 0.f}, Core::Vector2f{256.f, 64.f}, Enums::ColliderType::Wall});
	chunk.colliderInfo.push_back(ColliderTemplate{ Core::Vector3f{3* 256.f, 0.f, 0.f}, Core::Vector2f{256.f, 64.f}, Enums::ColliderType::Wall});
	chunk.colliderInfo.push_back(ColliderTemplate{ Core::Vector3f{4* 256.f, 0.f, 0.f}, Core::Vector2f{256.f, 64.f}, Enums::ColliderType::Wall});

	chunk.colliderInfo.push_back(ColliderTemplate{ Core::Vector3f{0.f, -64.f, 1.f}, Core::Vector2f{256.f, 128.f}, Enums::ColliderType::Floor });
	chunk.colliderInfo.push_back(ColliderTemplate{ Core::Vector3f{1*256.f, -64.f, 1.f}, Core::Vector2f{256.f, 128.f}, Enums::ColliderType::Floor });
	chunk.colliderInfo.push_back(ColliderTemplate{ Core::Vector3f{2*256.f, -64.f, 1.f}, Core::Vector2f{256.f, 128.f}, Enums::ColliderType::Floor });
	chunk.colliderInfo.push_back(ColliderTemplate{ Core::Vector3f{3*256.f, -64.f, 1.f}, Core::Vector2f{256.f, 128.f}, Enums::ColliderType::Floor });
	chunk.colliderInfo.push_back(ColliderTemplate{ Core::Vector3f{4*256.f, -64.f, 1.f}, Core::Vector2f{256.f, 128.f}, Enums::ColliderType::Floor });
	chunk.colliderInfo.push_back(ColliderTemplate{ Core::Vector3f{9*256.f, 6* 64.f, 1.f}, Core::Vector2f{256.f, 256.f}, Enums::ColliderType::Floor });

	chunk.colliderInfo.push_back(ColliderTemplate{ Core::Vector3f{128.f, 128.f, 1.f}, Core::Vector2f{128.f, 128.f}, Enums::ColliderType::Floor, true });
	chunk.colliderInfo.push_back(ColliderTemplate{ Core::Vector3f{512.f + 64.f, 256.f + 64.f, 1.f}, Core::Vector2f{256.f, 256.f}, Enums::ColliderType::Floor });
	chunk.colliderInfo.push_back(ColliderTemplate{ Core::Vector3f{512.f + 64.f, 256.f, 0.f}, Core::Vector2f{256.f, 64.f}, Enums::ColliderType::NToSRamp });
	chunk.colliderInfo.push_back(ColliderTemplate{ Core::Vector3f{512.f + 64.f, 576.f, 0.f}, Core::Vector2f{256.f, 64.f}, Enums::ColliderType::SToNRamp });
	
	chunk.colliderInfo.push_back(ColliderTemplate{ Core::Vector3f{512.f, 256.f + 64.f , 0.f}, Core::Vector2f{64.f, 256.f}, Enums::ColliderType::EToWRamp });
	chunk.colliderInfo.push_back(ColliderTemplate{ Core::Vector3f{512.f + 256.f + 64.f, 256.f + 64.f, 0.f}, Core::Vector2f{64.f, 256.f}, Enums::ColliderType::WToERamp });

	chunk.colliderInfo.push_back(ColliderTemplate{ Core::Vector3f{5 * 64.f, 9 * 64.f, 0.f}, Core::Vector2f{256.f, 256.f}, Enums::ColliderType::Floor });
	chunk.colliderInfo.push_back(ColliderTemplate{ Core::Vector3f{5 * 64.f, 13 * 64.f, 0.f}, Core::Vector2f{256.f, 256.f}, Enums::ColliderType::Floor });
	chunk.colliderInfo.push_back(ColliderTemplate{ Core::Vector3f{5 * 64.f, 17 * 64.f, 0.f}, Core::Vector2f{256.f, 192.f}, Enums::ColliderType::Floor });

	chunk.colliderInfo.push_back(ColliderTemplate{ Core::Vector3f{1 * 64.f, 9 * 64.f, 0.f}, Core::Vector2f{256.f, 256.f}, Enums::ColliderType::Floor });
	chunk.colliderInfo.push_back(ColliderTemplate{ Core::Vector3f{1 * 64.f, 13 * 64.f, 0.f}, Core::Vector2f{256.f, 256.f}, Enums::ColliderType::Floor });
	chunk.colliderInfo.push_back(ColliderTemplate{ Core::Vector3f{1 * 64.f, 17 * 64.f, 0.f}, Core::Vector2f{256.f, 192.f}, Enums::ColliderType::Floor });

	chunk.colliderInfo.push_back(ColliderTemplate{ Core::Vector3f{9 * 64.f, 9 * 64.f, 0.f}, Core::Vector2f{256.f, 256.f}, Enums::ColliderType::Floor });
	chunk.colliderInfo.push_back(ColliderTemplate{ Core::Vector3f{9 * 64.f, 13 * 64.f, 0.f}, Core::Vector2f{256.f, 256.f}, Enums::ColliderType::Floor });
	chunk.colliderInfo.push_back(ColliderTemplate{ Core::Vector3f{9 * 64.f, 17 * 64.f, 0.f}, Core::Vector2f{256.f, 128.f}, Enums::ColliderType::Floor });

	chunk.colliderInfo.push_back(ColliderTemplate{ Core::Vector3f{13 * 64.f, 1 * 64.f, 0.f}, Core::Vector2f{256.f + 128, 256.f}, Enums::ColliderType::Floor });
	chunk.colliderInfo.push_back(ColliderTemplate{ Core::Vector3f{14 * 64.f, 5 * 64.f, 0.f}, Core::Vector2f{ 256.f + 64, 256.f}, Enums::ColliderType::Floor });
	chunk.colliderInfo.push_back(ColliderTemplate{ Core::Vector3f{13 * 64.f, 9 * 64.f, 0.f}, Core::Vector2f{256.f + 128, 256.f}, Enums::ColliderType::Floor });
	chunk.colliderInfo.push_back(ColliderTemplate{ Core::Vector3f{13 * 64.f, 13 * 64.f, 0.f}, Core::Vector2f{256.f + 128, 256.f}, Enums::ColliderType::Floor });
	chunk.colliderInfo.push_back(ColliderTemplate{ Core::Vector3f{13 * 64.f, 17 * 64.f, 0.f}, Core::Vector2f{256.f + 128, 192.f}, Enums::ColliderType::Floor });
	chunk.colliderInfo.push_back(ColliderTemplate{ Core::Vector3f{13 * 64.f, 17 * 64.f, 0.f}, Core::Vector2f{256.f + 128 + 10240, 192.f + 10240 }, Enums::ColliderType::Floor });
	//colliderChunks.add(chunk);
	theManager.requestor.add(new ColliderChunk(chunk));
	wi.colliderInfo.push_back(chunk.getModfile());


	TileChunk tchunk;
	tchunk.fromMod = mod;
	tchunk.objectType = Enums::ObjectType::TileChunk;
	//tiles.clear();
	isLoading = true;
	tchunk.atlas = atlas;
		//for (float f = 1; f < 20; f++)
		for (float f2 = 1; f2 < 20; f2++)
		{

			tchunk.ID = Core::uuid();
			tchunk.tileInfo.clear();
			tchunk.layer = 0;
			tchunk.group = "Default";
			tchunk.tileInfo.push_back(TileTemplate{ Core::Vector3f{ -1 * 64.f, f2 * 64.f , 0.f }, atlas, "Ground",  Enums::TileTypes::Ground, false });
			tchunk.tileInfo.push_back(TileTemplate{ Core::Vector3f{ 0 * 64.f, f2 * 64.f  , 0.f }, atlas, "Ground",  Enums::TileTypes::Ground, false });
			tchunk.tileInfo.push_back(TileTemplate{ Core::Vector3f{ 1 * 64.f, f2 * 64.f  , 0.f }, atlas, "Ground",  Enums::TileTypes::Ground, false });
			tchunk.tileInfo.push_back(TileTemplate{ Core::Vector3f{ 2 * 64.f, f2 * 64.f  , 0.f }, atlas, "Ground",  Enums::TileTypes::Ground, false });
			tchunk.tileInfo.push_back(TileTemplate{ Core::Vector3f{ 3 * 64.f, f2 * 64.f  , 0.f }, atlas, "Ground",  Enums::TileTypes::Ground, false });
			tchunk.tileInfo.push_back(TileTemplate{ Core::Vector3f{ 4 * 64.f, f2 * 64.f  , 0.f }, atlas, "Ground",  Enums::TileTypes::Ground, false });
			tchunk.tileInfo.push_back(TileTemplate{ Core::Vector3f{ 5 * 64.f, f2 * 64.f  , 0.f }, atlas, "Ground",  Enums::TileTypes::Ground, false });
			tchunk.tileInfo.push_back(TileTemplate{ Core::Vector3f{ 6 * 64.f, f2 * 64.f  , 0.f }, atlas, "Ground",  Enums::TileTypes::Ground, false });
			tchunk.tileInfo.push_back(TileTemplate{ Core::Vector3f{ 7 * 64.f, f2 * 64.f  , 0.f }, atlas, "Ground",  Enums::TileTypes::Ground, false });
			tchunk.tileInfo.push_back(TileTemplate{ Core::Vector3f{ 8 * 64.f, f2 * 64.f  , 0.f }, atlas, "Ground",  Enums::TileTypes::Ground, false });
			tchunk.tileInfo.push_back(TileTemplate{ Core::Vector3f{ 13 * 64.f, f2 * 64.f , 0.f }, atlas, "Ground",  Enums::TileTypes::Ground, false });
			tchunk.tileInfo.push_back(TileTemplate{ Core::Vector3f{ 14 * 64.f, f2 * 64.f , 0.f }, atlas, "Ground",  Enums::TileTypes::Ground, false });
			tchunk.tileInfo.push_back(TileTemplate{ Core::Vector3f{ 15 * 64.f, f2 * 64.f , 0.f }, atlas, "Ground",  Enums::TileTypes::Ground, false });
			tchunk.tileInfo.push_back(TileTemplate{ Core::Vector3f{ 16 * 64.f, f2 * 64.f , 0.f }, atlas, "Ground",  Enums::TileTypes::Ground, false });
			tchunk.tileInfo.push_back(TileTemplate{ Core::Vector3f{ 17 * 64.f, f2 * 64.f , 0.f }, atlas, "Ground",  Enums::TileTypes::Ground, false });
			tchunk.tileInfo.push_back(TileTemplate{ Core::Vector3f{ 18 * 64.f, f2 * 64.f , 0.f }, atlas, "Ground",  Enums::TileTypes::Ground, false });
			
			theManager.requestor.add(new TileChunk(tchunk));
			wi.tileInfo.push_back(tchunk.getModfile());

		}
		for (float f2 = 1; f2 < 4; f2++)
		{
			tchunk.ID = Core::uuid();
			tchunk.tileInfo.clear();
			tchunk.tileInfo.push_back(TileTemplate{ Core::Vector3f{9 * 64.f, f2 * 64.f , 0.f }, atlas, "Ground",  Enums::TileTypes::Ground, false });
			tchunk.tileInfo.push_back(TileTemplate{ Core::Vector3f{10 * 64.f, f2 * 64.f  , 0.f }, atlas, "Ground",  Enums::TileTypes::Ground, false });				  
			tchunk.tileInfo.push_back(TileTemplate{ Core::Vector3f{11 * 64.f, f2 * 64.f  , 0.f }, atlas, "Ground",  Enums::TileTypes::Ground, false });				  
			tchunk.tileInfo.push_back(TileTemplate{ Core::Vector3f{12 * 64.f, f2 * 64.f  , 0.f }, atlas, "Ground",  Enums::TileTypes::Ground, false });				  

			theManager.requestor.add(new TileChunk(tchunk));
			wi.tileInfo.push_back(tchunk.getModfile());
			
		}
		tchunk.layer = 1;

		for (float f2 = 6; f2 < 9; f2++)
		{
			tchunk.ID = Core::uuid();
			tchunk.tileInfo.clear();
			tchunk.tileInfo.push_back(TileTemplate{ Core::Vector3f{9 * 64.f, f2 * 64.f , 1.f }, atlas, "Ground",  Enums::TileTypes::Ground, false });
			tchunk.tileInfo.push_back(TileTemplate{ Core::Vector3f{10 * 64.f, f2 * 64.f  , 1.f }, atlas, "Ground",  Enums::TileTypes::Ground, false });
			tchunk.tileInfo.push_back(TileTemplate{ Core::Vector3f{11 * 64.f, f2 * 64.f  , 1.f }, atlas, "Ground",  Enums::TileTypes::Ground, false });
			tchunk.tileInfo.push_back(TileTemplate{ Core::Vector3f{12 * 64.f, f2 * 64.f  , 1.f }, atlas, "Ground",  Enums::TileTypes::Ground, false });

			theManager.requestor.add(new TileChunk(tchunk));
			wi.tileInfo.push_back(tchunk.getModfile());
		
		}
		tchunk.layer = 0;

		for (float f2 = 9; f2 < 20; f2++)
		{
			tchunk.ID = Core::uuid();
			tchunk.tileInfo.clear();
			tchunk.tileInfo.push_back(TileTemplate{ Core::Vector3f{9 * 64.f, f2 * 64.f , 0.f }, atlas, "Ground",  Enums::TileTypes::Ground, false });
			tchunk.tileInfo.push_back(TileTemplate{ Core::Vector3f{10 * 64.f, f2 * 64.f  , 0.f }, atlas, "Ground",  Enums::TileTypes::Ground, false });
			tchunk.tileInfo.push_back(TileTemplate{ Core::Vector3f{11 * 64.f, f2 * 64.f  , 0.f }, atlas, "Ground",  Enums::TileTypes::Ground, false });
			tchunk.tileInfo.push_back(TileTemplate{ Core::Vector3f{12 * 64.f, f2 * 64.f  , 0.f }, atlas, "Ground",  Enums::TileTypes::Ground, false });

			theManager.requestor.add(new TileChunk(tchunk));
			wi.tileInfo.push_back(tchunk.getModfile());
		}
	
	tchunk.ID = Core::uuid();
	tchunk.tileInfo.clear();
	for (float f = 0; f < 20; f++)
	{

		tchunk.tileInfo.push_back(TileTemplate{ Core::Vector3f{f * 64.f, 0.f , 0.f }, atlas, "GroundWall",  Enums::TileTypes::Wall, false });
		tchunk.tileInfo.push_back(TileTemplate{ Core::Vector3f{f * 64.f, 1024.f, 0.f }, atlas, "GroundWall",  Enums::TileTypes::Wall, false });

	}
	
	for (float f = 1; f < 20; f++)
	{
		tchunk.tileInfo.push_back(TileTemplate{ Core::Vector3f{0.f, f * 64.f , 0.f }, atlas, "Wall",  Enums::TileTypes::Wall, true });
	}
	theManager.requestor.add(new TileChunk(tchunk));
	wi.tileInfo.push_back(tchunk.getModfile());

	tchunk.ID = Core::uuid();
	tchunk.tileInfo.clear();
	tchunk.layer = 1;
	for (float f = 0; f < 20; f++)
	{

		tchunk.tileInfo.push_back(TileTemplate{ Core::Vector3f{f * 64.f, -64.f, 1.f }, atlas, "Ground",  Enums::TileTypes::Ground, false });
		tchunk.tileInfo.push_back(TileTemplate{ Core::Vector3f{f * 64.f,  0.f, 1.f }, atlas, "GroundWall",  Enums::TileTypes::Ground, false });
	}
	theManager.requestor.add(new TileChunk(tchunk));
	wi.tileInfo.push_back(tchunk.getModfile());
	
	tchunk.ID = Core::uuid();
	tchunk.tileInfo.clear();
	tchunk.group = "Island";
	tchunk.tileInfo.push_back(TileTemplate{ Core::Vector3f{128.f, 128.f, 1.f }, atlas, "Ground",  Enums::TileTypes::Ground, true });
	tchunk.tileInfo.push_back(TileTemplate{ Core::Vector3f{128.f, 128.f + 64.f, 1.f }, atlas, "Ground",  Enums::TileTypes::Ground, true });
	tchunk.tileInfo.push_back(TileTemplate{ Core::Vector3f{128.f + 64.f, 128.f + 64.f, 1.f }, atlas, "Ground",  Enums::TileTypes::Ground, true });
	tchunk.tileInfo.push_back(TileTemplate{ Core::Vector3f{128.f + 64.f, 128.f, 1.f }, atlas, "Ground",  Enums::TileTypes::Ground, true });
	tchunk.chunkTransparency = TransparencyInfo{ true, Core::Vector3f{128.f, 128.f,  1.f},  Core::Vector2f{128.f , 128.f } };
	theManager.requestor.add(new TileChunk(tchunk));
	wi.tileInfo.push_back(tchunk.getModfile());

	auto greetings = DialogOption{ Core::uuid(), { {1,2}, {3,4}, {7,8}}, nullptr, nullptr, Enums::DialogStatus::Open, "Hello traveller!" };
	auto playerResponse = DialogOption{ Core::uuid(), { }, nullptr, nullptr, Enums::DialogStatus::Open, "Good day" };
	auto npcResponse = DialogOption{ Core::uuid(), { {5,5}}, nullptr, nullptr, Enums::DialogStatus::Open, "I hope you're having a good day!" };
	auto playerResponse2 = DialogOption{ Core::uuid(), { }, nullptr, nullptr, Enums::DialogStatus::Open, "Wassup? " };
	auto npcResponse2 = DialogOption{ Core::uuid(), { {5,6} }, nullptr, nullptr, Enums::DialogStatus::Open, "Not much... just added here as a testing dummy" };
	auto exitDialog = DialogOption{ Core::uuid(), { }, nullptr, nullptr, Enums::DialogStatus::Close, "Ok, Bye..." };
	auto exitDialog2 = DialogOption{ Core::uuid(), { }, nullptr, nullptr,Enums::DialogStatus::Close, "Bye..." };

	auto nested1 = DialogOption{ Core::uuid(), { {-1, 9} }, nullptr, nullptr, Enums::DialogStatus::Open, "Nested Test" };
	auto nested2 = DialogOption{ Core::uuid(), { {-1, 7}}, nullptr, nullptr,Enums::DialogStatus::Open, "Nested 2" };
	auto nested3 = DialogOption{ Core::uuid(), { {5, 6}}, nullptr, nullptr, Enums::DialogStatus::Open, "Nested 3" };


	std::unordered_map<size_t, DialogOption> opt{ 
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
	DialogTree dt(opt);
	dt.objectType = Enums::ObjectType::DialogTree;
	dt.fromMod = mod;
	dt.ID = Core::uuid();

	theManager.requestor.add(new DialogTree(dt));
	dialogTest = dt.getModfile();

	gfx.addRenderable(0, "Default", { 1024.f + 64, 128.f}, 0.f, atlas, "WaterTop", Enums::TileTypes::Ground, true);
	gfx.addRenderable(0, "Default", { 1024.f, 128.f }, 0.f, atlas, "WaterTopLeft", Enums::TileTypes::Ground, true);
	
	objectHandler.player->getComponent<Component::Transform>()->pos.x = 50.f; 
	objectHandler.player->getComponent<Component::Transform>()->pos.y = -15.f;

	auto dialog = objectHandler.objects[testObjectId].getComponent<Dialog>();
	dialog->dialogTreeuuid = dialogTest;
	dialog->dialogTree = Engine::GetModule<Asset::AssetManager>().requestor.requestUniqueInstance<DialogTree>(dialogTest);

	Combat::Element e;
	e.objectType = Enums::ObjectType::Element;
	e.name = "Testelement";
	e.fromMod = mod;
	e.elementAttributes[e.getModfile()] = 1.0;

	theManager.requestor.add(new Combat::Element(e));

	Combat::Effect ef;
	ef.objectType = Enums::ObjectType::Effect;
	ef.effectTime.maxTime = 10.f;
	ef.effectElememtId = e.getModfile();
	ef.effectType = Enums::EffectType::TickDamage;
	ef.theEffect = std::shared_ptr<Combat::DamageEffect>(new Combat::DamageEffect(1, Enums::Attribute::Power, 0.4));
	ef.tickDelay.maxTime = .1f;
	ef.fromMod = mod;
	theManager.requestor.add(new Combat::Effect(ef));

	ef.effectType = Enums::EffectType::Barrier;
	ef.theEffect = std::shared_ptr<Combat::BarrierEffect>(new Combat::BarrierEffect(2, 20));
	ef.effectTime.maxTime = 2.f;
	ef.tickDelay.maxTime = 1.f;

	auto ef2 = ef;
	ef2.ID = Core::uuid();
	theManager.requestor.add(new Combat::Effect(ef2));
	Prefab p;
	p.objectType = Enums::ObjectType::Prefab;
	p.components.emplace_back(std::make_unique<Collider, Core::Vector2f, Core::Vector2f>({ 64, 64 }, {-16, 16}));
	Component::Damage d = Component::Damage();
	d.canLockNextFrame = false;
	d.maxTargets = 1;
	d.speed = 0.f;
	//d.effectsIds.push_back(ef.getModfile());
	d.timeToLive.maxTime = 2.f;
	d.elementId = e.getModfile();
	d.damageCoef = 1.0;
	p.components.push_back(std::make_unique<Component::Damage>(d));
	p.fromMod = mod;

	theManager.requestor.add(new Prefab(p));

	Combat::Skill s;
	s.objectType = Enums::ObjectType::Skill;
	s.animation = "foo";
	s.coolDown.maxTime = 1.f;
	s.summonPoint = 100.f;
	s.fromMod = mod;
	s.elementId = e.getModfile();
	s.prefabId = p.getModfile();
	s.skillExecutionEffectIds.push_back(ef2.getModfile());
	s.iconTextureName = "SkillIconFrame.png";

	theManager.requestor.add(new Combat::Skill(s));


	isLoading = false;
	setCurrentTime(12.f);
	theManager.requestor.add(new WorldInstance(wi));

	File::Mod::ModHeader mh;
	mh.name = "Default";
	mh.modVersion = OneVersion(1, 0, 0);
	theManager.saveGameDatabase(mh.name, mh);
	theManager.getModLoader().loadOrder.insert({mh.name, 0});
	theManager.requestor.clear();
	loadWorldInstance(wi.getModfile(), {}, { 50.f, -15.f , 1.f});
	auto eff = theManager.requestor.requestUniqueInstance<Combat::Effect>(ef.getModfile());
	auto eff2 = theManager.requestor.requestUniqueInstance<Combat::Effect>(ef2.getModfile());
	auto elm = theManager.requestor.request<Combat::Element>(e.getModfile());
	objectHandler.player->getComponent<Component::Stats>()->attunedTo = *elm;
	objectHandler.player->getComponent<Component::Stats>()->doEffects({ eff, eff2 }, objectHandler.player->getSharedComponent<Component::Stats>());
	auto skill = theManager.requestor.requestUniqueInstance<Combat::Skill>(s.getModfile());
	objectHandler.player->getComponent<Component::CombatComponent>()->skills[Enums::CombatSkill::Primary] = skill;
	objectHandler.player->getComponent<Component::CombatComponent>()->skills[Enums::CombatSkill::Secondary] = skill;
	objectHandler.player->getComponent<Component::CombatComponent>()->skills[Enums::CombatSkill::Special] = skill;

}

void WorldManager::setCurrentTime(const float& currentTime)
{

	while (gfx.timeOfDay < currentTime || gfx.timeOfDay > currentTime + 0.5f)
		Simulate(12.f);
}

void WorldManager::newGame()
{
	Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("WorldManager").Info("New Game");
	saveFile.newGame(Enums::DifficultyLevel::Normal, Core::uuid::nil(), {});
	auto& glob = Engine::GetModule<Globals>();
	loadWorldInstance(glob.newGameWorldInstance, glob.newGameWorldInstanceLoadingScreen, glob.newGamePoint);
}

void WorldManager::save(const Core::String& fileName)
{
	Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("WorldManager").Info("Save Game");
	saveFile.currentZone = loadHandler.getCurrentWorld();
	saveFile.loadingScreen = loadHandler.getCurrentLoadingScreen();
	saveFile.save(fileName);
}

void WorldManager::load(const Core::String& fileName)
{
	Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("WorldManager").Info("Load Game");
	isLoading = true;
	saveFile.load(fileName);
	loadWorldInstance(saveFile.currentZone, saveFile.loadingScreen, saveFile.point);
	// TODO: start timers from questing module if needed
}

void WorldManager::loadWorldInstance(const File::Mod::ModFileUUIDHelper& world, const File::Mod::ModFileUUIDHelper& loadingScreen, const Core::Vector3f& playerPosition)
{
	isLoading = true;
	EngineModule::Time& time = Engine::GetModule<EngineModule::Time>();
	time.getTimer(Globals::LOADING_TIMER).restart();
	time.getTimer(Globals::TOTAL_TIME_LOADED).restart();

	loadHandler.beginLoad(world, loadingScreen, playerPosition);

}

void WorldManager::Update()
{
	if (isLoading)
	{
		auto timer = Engine::GetModule<EngineModule::Time>().getTimer(Globals::LOADING_TIMER);
		timer.restart();
		while (timer.getElapsedTime().asSeconds() < 0.05f && isLoading)
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
