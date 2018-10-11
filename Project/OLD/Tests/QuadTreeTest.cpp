#ifdef _UNITTESTS_

#include "CppUnitTest.h"

#include <Core\QuadTree.hpp>
#include <Core\ICollider.hpp>
#include <Graphic\Tile\GridTile.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{

	TEST_CLASS(QuadTreeUnitTest)
	{
	public:
		static QuadTree<World::Grid::Tile> qt;
		static std::vector<World::Grid::Tile> tiles;
		TEST_CLASS_INITIALIZE(QuadTreeUnitTestInitialize)
		{
			for (float x =0; x < 10; x++)
				for (float y = 0; y < 10; y++)
				{
					tiles.push_back(World::Grid::Tile(16 * x, 16 * y));
				}

			for (auto it = tiles.begin(); it != tiles.end(); it++)
			{
				World::Grid::Tile* t = &it.operator*();
				qt.insert(t);
			}
		}

		TEST_CLASS_CLEANUP(QuadTreeUnitTestCleanup)
		{
			for (auto it = tiles.begin(); it != tiles.end(); it++)
			{
				qt.remove(&*it);
			}
		}

		TEST_METHOD(TestCheckCollision)
		{
			World::Grid::Tile test(0, 0);
			test.size = 32;
			
			qt.insert(&test);

			auto result = qt.collidesWith(&test);
			qt.remove(&test);
			Assert::AreEqual(result.size(), (size_t)4);
		}

		TEST_METHOD(TestCheckCollisionAfterMove)
		{
			World::Grid::Tile test(0, 0);
			test.size = 32;

			qt.insert(&test);

			test.pos.x = -32;
			test.pos.y = -32;

			test.update = true;
			qt.update();

			auto result = qt.collidesWith(&test);

			qt.remove(&test);
			Assert::AreEqual(result.size(), (size_t)0);
		}

		TEST_METHOD(TestRemoveAllObjectsRemovesAllChildren)
		{
			QuadTree<World::Grid::Tile> qt_internal(1024, 1024);
			for (auto it = tiles.begin(); it != tiles.end(); it++)
			{
				World::Grid::Tile* t = &it.operator*();
				qt_internal.insert(t);
			}
			for (auto it = tiles.begin(); it != tiles.end(); it++)
			{
				World::Grid::Tile* t = &it.operator*();
				qt_internal.remove(t);
			}
			Assert::IsFalse(qt_internal.getRootNode().hasChildren());
		}


	};
	QuadTree<World::Grid::Tile> QuadTreeUnitTest::qt(-1024, -1024, 2048, 2048);
	std::vector<World::Grid::Tile> QuadTreeUnitTest::tiles(0);
}


#endif