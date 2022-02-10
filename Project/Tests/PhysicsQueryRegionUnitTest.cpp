#ifdef _UNITTESTS_

#include "CppUnitTest.h"

#include <Physics/RegionQuery/Region.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	namespace TPhysics
	{
		TEST_CLASS(PhysicsQueryRegionTest)
		{
		public:

			TEST_METHOD(TestSplitHorizontal)
			{
				auto tup = Physics::RegionQuery::QueryRegion::split({ 0.f, 0.f, 50.f, 50.f }, true);
				Core::FloatRect first, second;
				first = std::get<0>(tup);
				second = std::get<1>(tup);

				Assert::AreEqual(first.x, 0.f);
				Assert::AreEqual(first.y, 0.f);
				Assert::AreEqual(first.h, 25.f);
				Assert::AreEqual(first.w, 50.f);

				Assert::AreEqual(second.x, 0.f);
				Assert::AreEqual(second.y, 25.f);
				Assert::AreEqual(second.h, 25.f);
				Assert::AreEqual(second.w, 50.f);

			}

			TEST_METHOD(TestSplitHorizontalNonZeroPos)
			{
				auto tup = Physics::RegionQuery::QueryRegion::split({ 50.f, 50.f, 50.f, 50.f }, true);
				Core::FloatRect first, second;
				first = std::get<0>(tup);
				second = std::get<1>(tup);

				Assert::AreEqual(first.x, 50.f);
				Assert::AreEqual(first.y, 50.f);
				Assert::AreEqual(first.h, 25.f);
				Assert::AreEqual(first.w, 50.f);

				Assert::AreEqual(second.x, 50.f);
				Assert::AreEqual(second.y, 75.f);
				Assert::AreEqual(second.h, 25.f);
				Assert::AreEqual(second.w, 50.f);

			}

			TEST_METHOD(TestSplitVertical)
			{
				auto tup = Physics::RegionQuery::QueryRegion::split({ 0.f, 0.f, 50.f, 50.f }, false);
				Core::FloatRect first, second;
				first = std::get<0>(tup);
				second = std::get<1>(tup);

				Assert::AreEqual(first.x, 0.f);
				Assert::AreEqual(first.y, 0.f);
				Assert::AreEqual(first.h, 50.f);
				Assert::AreEqual(first.w, 25.f);

				Assert::AreEqual(second.x, 25.f);
				Assert::AreEqual(second.y, 0.f);
				Assert::AreEqual(second.h, 50.f);
				Assert::AreEqual(second.w, 25.f);
			}

			TEST_METHOD(TestSplitVerticalNonZeroPos)
			{
				auto tup = Physics::RegionQuery::QueryRegion::split({ 50.f, 50.f, 50.f, 50.f }, false);
				Core::FloatRect first, second;
				first = std::get<0>(tup);
				second = std::get<1>(tup);

				Assert::AreEqual(first.x, 50.f);
				Assert::AreEqual(first.y, 50.f);
				Assert::AreEqual(first.h, 50.f);
				Assert::AreEqual(first.w, 25.f);

				Assert::AreEqual(second.x, 75.f);
				Assert::AreEqual(second.y, 50.f);
				Assert::AreEqual(second.h, 50.f);
				Assert::AreEqual(second.w, 25.f);

			}
		};

	}
}

#endif