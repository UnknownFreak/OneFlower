#ifdef _UNITTESTS_
#ifdef _WIN32
#include <direct.h>
#define chdir _chdir
#elif
#include <unistd.h>
#endif

#include "CppUnitTest.h"
#include <iostream>

#include <Asset\AssetManagerCore.hpp>
#include <Core/Component/TransformComponent.hpp>

#include <Graphic/World/WorldManager.hpp>
#include <Graphic/World/Zone.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace TestFramework = Microsoft::VisualStudio::CppUnitTestFramework;

template<> inline std::wstring TestFramework::ToString<WorldManager::Loadstate>(const WorldManager::Loadstate& q) {
	return std::wstring(std::to_wstring(q));
}
template<> inline std::wstring TestFramework::ToString<WorldManager::Loadstate>(const WorldManager::Loadstate* q) {
	return std::wstring(std::to_wstring(*q));
}
template<> inline std::wstring TestFramework::ToString<WorldManager::Loadstate>(WorldManager::Loadstate* q) {
	return std::wstring(std::to_wstring(*q));
}
template<> inline std::wstring TestFramework::ToString<Core::Vector2>(const Core::Vector2& q) {
	return std::wstring(std::to_wstring(q.x) + L", " + std::to_wstring(q.y));
}
template<> inline std::wstring TestFramework::ToString<Core::Vector2>(const Core::Vector2* q) {
	return std::wstring(std::to_wstring(q->x) + L", " + std::to_wstring(q->y));
}
template<> inline std::wstring TestFramework::ToString<Core::Vector2>(Core::Vector2* q) {
	return std::wstring(std::to_wstring(q->x) + L", " + std::to_wstring(q->y));
}
namespace Tests
{
	TEST_CLASS(WorldManagerTest)
	{

		const static Core::String fromMod;
		const static Core::String image;

		friend class Zone;

	public:

		static WorldManager wm;

		static void add_objects(Database::Chunk& c)
		{
			Database::Prefab prefab;

			prefab.fromMod = fromMod;
			prefab.ID = 1;
			prefab.oldPos = Core::Vector2(20, 20);
			prefab.pos = Core::Vector2(20, 20);

			c.prefabs.insert(std::make_pair(std::make_pair(fromMod, 1), prefab));
			prefab.oldPos = Core::Vector2(40, 40);
			prefab.pos = Core::Vector2(40, 40);
			c.prefabs.insert(std::make_pair(std::make_pair(fromMod, 1), prefab));
			prefab.oldPos = Core::Vector2(60, 60);
			prefab.pos = Core::Vector2(60, 60);
			c.prefabs.insert(std::make_pair(std::make_pair(fromMod, 1), prefab));
			prefab.oldPos = Core::Vector2(80, 20);
			prefab.pos = Core::Vector2(80, 20);
			c.prefabs.insert(std::make_pair(std::make_pair(fromMod, 1), prefab));
		}

		static void add_chunk(Database::Zone & zone, float x, float y)
		{

			Database::Chunk c;
			c.fromMod = fromMod;
			c.pos = Core::Vector2(x, y);
			
			add_objects(c);

			zone.chunks.push_back(c);
		}

		static void add_zone(Requestor<Database::Zone>& req)
		{
			Database::Zone zone;

			zone.background = image;
			zone.chunkCountX = zone.chunkCountY = 3;

			zone.fromMod = fromMod;
			zone.ID = 1;
			zone.loadingScreen = image;
			zone.loadingScreenMessage = "wm tests.";
			zone.mode = ObjectSaveMode::ADD;
			zone.name = "wmtestzone";

			zone.prefabs.push_back(std::make_pair(fromMod, 2));
			zone.prefabs.push_back(std::make_pair(fromMod, 1));
			zone.prefabs.push_back(std::make_pair(fromMod, 3));

			add_chunk(zone, 0, 0);
			add_chunk(zone, 0, 1);
			add_chunk(zone, 0, 2);
			add_chunk(zone, 1, 0);
			add_chunk(zone, 1, 1);
			add_chunk(zone, 1, 2);
			add_chunk(zone, 2, 0);
			add_chunk(zone, 2, 1);
			add_chunk(zone, 2, 2);

			req.add(zone);

		}

		static void add_prefab(Requestor<Asset::Prefab>& req, Core::String prefabName, size_t prefabId)
		{
			Asset::Prefab p;
			p.fromMod = fromMod;
			p.ID = prefabId;
			p.mode = ObjectSaveMode::ADD;
			//p.name = prefabName;
			p.base.push_back(new Component::Transform());
			req.add(p);
		}

		static void loadSomeRepeat(size_t repeat_count)
		{
			for (size_t i=0; i <= repeat_count; i++) wm.loadSome();
		}

		static void verify_chunk_positions()
		{
			Zone& z = wm.worldmap[{fromMod, 1}];
			
			verify_neighbours(z.chunkList[0], Core::Vector2(0, 0));
			verify_neighbours(z.chunkList[1], Core::Vector2(0, 1));
			verify_neighbours(z.chunkList[2], Core::Vector2(0, 2));
			verify_neighbours(z.chunkList[3], Core::Vector2(1, 0));
			verify_neighbours(z.chunkList[4], Core::Vector2(1, 1));
			verify_neighbours(z.chunkList[5], Core::Vector2(1, 2));
			verify_neighbours(z.chunkList[6], Core::Vector2(2, 0));
			verify_neighbours(z.chunkList[7], Core::Vector2(2, 1));
			verify_neighbours(z.chunkList[8], Core::Vector2(2, 2));

		}

		static void verify_neighbours(Chunk& chunk, Core::Vector2 expected_pos)
		{
			Assert::AreEqual(expected_pos, chunk.chunkPosition);

			for each (auto var in chunk.neighbours)
			{
				Core::Vector2 pos = chunk.chunkPosition;
				if (var.first == Chunk::Neighbour::LEFT)
				{
					pos.y--;
				}
				else if (var.first == Chunk::Neighbour::BOTTOM)
				{
					pos.x++;
				}
				if (var.first == Chunk::Neighbour::RIGHT)
				{
					pos.y++;
				}
				else if (var.first == Chunk::Neighbour::TOP)
				{
					pos.x--;
				}

				Assert::AreEqual(pos, var.second->chunkPosition);
			}

		}

		static void setup_file()
		{

			Requestor<Database::Zone>& zoneReq = Engine::GetModule<Asset::AssetManager>().getZoneRequester();
			Requestor<Asset::Prefab>& prefabReq = Engine::GetModule<Asset::AssetManager>().getPrefabRequester();

			add_prefab(prefabReq, "wmLoadTestPrefab1", 1);
			add_prefab(prefabReq, "wmLoadTestPrefab2", 2);
			add_prefab(prefabReq, "wmLoadTestPrefab3", 3);

			add_zone(zoneReq);

			ModHeader h;
			h.name = fromMod;

			Engine::GetModule<Asset::AssetManager>().saveGameDatabase(fromMod, h);
			Engine::GetModule<Asset::AssetManager>().getModLoader().loadOrder.clear();
			Engine::GetModule<Asset::AssetManager>().getModLoader().loadOrder.insert(std::make_pair("wmtest", 0));
			zoneReq.clear();
			prefabReq.clear();
		}

		TEST_CLASS_INITIALIZE(Initialize)
		{
			chdir(PROJECT_DIR);
			setup_file();
		}

		TEST_METHOD(TestLoadZone)
		{
			wm.loadZone(fromMod, 1);
			Assert::AreEqual(wm.CHECK_IF_LOADED, wm.getCurrentLoadingState(), L"Check loaded flag:");
			wm.loadSome();
			Assert::AreEqual(wm.LOAD_FROM_FILE, wm.getCurrentLoadingState(), L"Check load from file:");
			wm.loadSome();
			Assert::AreEqual(wm.INITIALIZE_CHUNKS, wm.getCurrentLoadingState(), L"Check initialize chunks:");
			loadSomeRepeat(8);
			Assert::AreEqual(wm.INITIALIZE_CHUNKS, wm.getCurrentLoadingState(), L"Check initialize chunk2:");
			wm.loadSome();
			Assert::AreEqual(wm.BUILD_CHUNKS, wm.getCurrentLoadingState(), L"Check build chunks:");
			loadSomeRepeat(8);
			Assert::AreEqual(wm.BUILD_CHUNKS, wm.getCurrentLoadingState(), L"Check build chunks2:");
			wm.loadSome();
			Assert::AreEqual(wm.PLACE_TILES, wm.getCurrentLoadingState(), L"Check place tiles:");
			loadSomeRepeat(8);
			Assert::AreEqual(wm.PLACE_TILES, wm.getCurrentLoadingState(), L"Check place tiles2:");
			wm.loadSome();
			Assert::AreEqual(wm.LOAD_OBJECTS, wm.getCurrentLoadingState(), L"Check load objects:");
			verify_chunk_positions();
			loadSomeRepeat(2);
			Assert::AreEqual(wm.LOAD_OBJECTS, wm.getCurrentLoadingState(), L"Check load objects2:");
			wm.loadSome();
			Assert::AreEqual(wm.POPULATE_CHUNKS, wm.getCurrentLoadingState(), L"Check populate chunks:");
			loadSomeRepeat(8);
			Assert::AreEqual(wm.POPULATE_CHUNKS, wm.getCurrentLoadingState(), L"Check populate chunks2:");
			wm.loadSome();
			Assert::AreEqual(wm.UNLOAD_OBJECTS, wm.getCurrentLoadingState(), L"Check unload objects:");
			wm.loadSome();
			Assert::AreEqual(wm.DONE, wm.getCurrentLoadingState(), L"Check done:");

		}

	};
	const Core::String WorldManagerTest::fromMod = "wmtest";
	const Core::String WorldManagerTest::image = "test.png";

	WorldManager WorldManagerTest::wm;
}

#endif