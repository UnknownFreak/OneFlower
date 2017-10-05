#define _EDITOR_

#include "CppUnitTest.h"

#include <Physics\BoundingBox.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;




namespace Tests
{

	TEST_CLASS(BoundingBoxUnitTest)
	{
	public:

		TEST_METHOD(TestBoundingBoxNoCollide)
		{
			Physics::BoundingBox a(0, 0, 10, 10);
			Physics::BoundingBox b(11, 11, 10, 10);
			Assert::IsFalse(a.intersect(b));
		}

		TEST_METHOD(TestBoundingBoxCollideSelf)
		{
			Physics::BoundingBox a(0, 0, 10, 10);
			Assert::IsTrue(a.intersect(a));
		}
		TEST_METHOD(TestBoundingBoxCollideTopLeft)
		{
			Physics::BoundingBox a(0, 0, 10, 10);
			Physics::BoundingBox b(-10, -10, 10, 10);
			Assert::IsTrue(a.intersect(b));
		}
		TEST_METHOD(TestBoundingBoxCollideBottomLeft)
		{
			Physics::BoundingBox a(0, 0, 10, 10);
			Physics::BoundingBox b(-10, 10, 10, 10);
			Assert::IsTrue(a.intersect(b));

		}
		TEST_METHOD(TestBoundingBoxCollideTopRight)
		{
			Physics::BoundingBox a(0, 0, 10, 10);
			Physics::BoundingBox b(10, -10, 10, 10);
			Assert::IsTrue(a.intersect(b));
		}
		TEST_METHOD(TestBoundingBoxCollideBottomRight)
		{
			Physics::BoundingBox a(0, 0, 10, 10);
			Physics::BoundingBox b(10, 10, 10, 10);
			Assert::IsTrue(a.intersect(b));
		}
		TEST_METHOD(TestBoundingBoxNoCollideTopLeft)
		{
			Physics::BoundingBox a(0, 0, 10, 10);
			Physics::BoundingBox b(-10, -10, 9, 9);
			Assert::IsFalse(a.intersect(b));
		}
		TEST_METHOD(TestBoundingBoxNoCollideBottomLeft)
		{
			Physics::BoundingBox a(0, 0, 10, 10);
			Physics::BoundingBox b(-10, 10, 9, 9);
			Assert::IsFalse(a.intersect(b));

		}
		TEST_METHOD(TestBoundingBoxNoCollideTopRight)
		{
			Physics::BoundingBox a(0, 0, 10, 10);
			Physics::BoundingBox b(10, -10, 9, 9);
			Assert::IsFalse(a.intersect(b));
		}
		TEST_METHOD(TestBoundingBoxNoCollideBottomRight)
		{
			Physics::BoundingBox a(0, 0, 10, 10);
			Physics::BoundingBox b(11, 11, 9, 9);
			Assert::IsFalse(a.intersect(b));
		}
	};

}

