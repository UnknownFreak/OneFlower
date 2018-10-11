#ifdef _UNITTESTS_
#include "CppUnitTest.h"

#include <Core\Rect.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define TestFramework Microsoft::VisualStudio::CppUnitTestFramework;

template<> inline std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<Core::IntRect>(const Core::IntRect& q) {
	return std::wstring(std::to_wstring(q.x) + L", " + std::to_wstring(q.y));
}
template<> inline std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<Core::IntRect>(const Core::IntRect* q) {
	return std::wstring(std::to_wstring(q->x) + L", " + std::to_wstring(q->y));
}
template<> inline std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<Core::IntRect>(Core::IntRect* q) {
	return std::wstring(std::to_wstring(q->x) + L", " + std::to_wstring(q->y));
}

namespace Tests
{
	TEST_CLASS(RectTest)
	{
	public:

		TEST_METHOD(NoIntersect)
		{
			Core::IntRect a(5, 5, 5, 5);
			Core::IntRect b(1, 1, 1, 1);
			Assert::IsFalse(a.intersects(b));
		}
		TEST_METHOD(Intersect)
		{
			Core::IntRect a(5, 5, 5, 5);
			Core::IntRect b(5, 5, 1, 1);
			Assert::IsTrue(a.intersects(b));
		}
		TEST_METHOD(TestBoundingBoxNoCollide)
		{
			Core::IntRect a(0, 0, 10, 10);
			Core::IntRect b(11, 11, 10, 10);
			Assert::IsFalse(a.intersects(b));
		}

		TEST_METHOD(TestBoundingBoxCollideSelf)
		{
			Core::IntRect a(0, 0, 10, 10);
			Assert::IsTrue(a.intersects(a));
		}
		TEST_METHOD(TestBoundingBoxCollideTopLeft)
		{
			Core::IntRect a(0, 0, 10, 10);
			Core::IntRect b(-10, -10, 10, 10);
			Assert::IsFalse(a.intersects(b));
		}
		TEST_METHOD(TestBoundingBoxCollideBottomLeft)
		{
			Core::IntRect a(0, 0, 10, 10);
			Core::IntRect b(-10, 10, 10, 10);
			Assert::IsFalse(a.intersects(b));
		}
		TEST_METHOD(TestBoundingBoxCollideTopRight)
		{
			Core::IntRect a(0, 0, 10, 10);
			Core::IntRect b(10, -10, 10, 10);
			Assert::IsFalse(a.intersects(b));
		}
		TEST_METHOD(TestBoundingBoxCollideBottomRight)
		{
			Core::IntRect a(0, 0, 10, 10);
			Core::IntRect b(10, 10, 10, 10);
			Assert::IsFalse(a.intersects(b));
		}
		TEST_METHOD(TestBoundingBoxNoCollideTopLeft)
		{
			Core::IntRect a(0, 0, 10, 10);
			Core::IntRect b(-10, -10, 9, 9);
			Assert::IsFalse(a.intersects(b));
		}
		TEST_METHOD(TestBoundingBoxNoCollideBottomLeft)
		{
			Core::IntRect a(0, 0, 10, 10);
			Core::IntRect b(-10, 10, 9, 9);
			Assert::IsFalse(a.intersects(b));

		}
		TEST_METHOD(TestBoundingBoxNoCollideTopRight)
		{
			Core::IntRect a(0, 0, 10, 10);
			Core::IntRect b(10, -10, 9, 9);
			Assert::IsFalse(a.intersects(b));
		}
		TEST_METHOD(TestBoundingBoxNoCollideBottomRight)
		{
			Core::IntRect a(0, 0, 10, 10);
			Core::IntRect b(11, 11, 9, 9);
			Assert::IsFalse(a.intersects(b));
		}
		TEST_METHOD(WithReference)
		{
			Core::Rect<const int&> r(0, 0, 10, 10);
			Assert::IsTrue(r.intersects(r));
		}
	};
}

#endif