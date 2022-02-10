#ifdef _UNITTESTS_
#include "CppUnitTest.h"

#include <Helpers\Vector.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace TestFramework = Microsoft::VisualStudio::CppUnitTestFramework;

template<> inline std::wstring TestFramework::ToString<Core::Vector2i>(const Core::Vector2i& q) {
	return std::wstring(std::to_wstring(q.x) + L", " + std::to_wstring(q.y));
}
template<> inline std::wstring TestFramework::ToString<Core::Vector2i>(const Core::Vector2i* q) {
	return std::wstring(std::to_wstring(q->x) + L", " + std::to_wstring(q->y));
}
template<> inline std::wstring TestFramework::ToString<Core::Vector2i>(Core::Vector2i* q) {
	return std::wstring(std::to_wstring(q->x) + L", " + std::to_wstring(q->y));
}

namespace Tests
{
	TEST_CLASS(Vector2Test)
	{
	public:
	
		TEST_METHOD(Addition)
		{
			Core::Vector2i a{ 5, 5 };
			Core::Vector2i b{ 5, 5 };
			Assert::AreEqual<Core::Vector2i>(a + b, { 10, 10 });
		}
		TEST_METHOD(Subtraction)
		{
			Core::Vector2i a{ 5, 5 };
			Core::Vector2i b{ 5, 5 };
			Assert::AreEqual<Core::Vector2i>(a - b, { 0,0 });
		}

		TEST_METHOD(LNormal)
		{
			Core::Vector2i a{ 2, 5 };
			Assert::AreEqual<Core::Vector2i>(a.lnormal(), { -5, 2 });
		}

		TEST_METHOD(RNormal)
		{
			Core::Vector2i a{ 2, 5 };
			Assert::AreEqual<Core::Vector2i>(a.rnormal(), { 5, -2 });
		}

		TEST_METHOD(Magnitude)
		{
			Core::Vector2i a{ 8, 6 };
			Assert::AreEqual(a.magnitude(), 10);
		}

		TEST_METHOD(Dot)
		{
			Core::Vector2i a{ 2, 3 };
			Core::Vector2i b{ 4, 5 };
			Assert::AreEqual(a.dot(b), 23);
		}

		TEST_METHOD(SfDot)
		{
			Core::Vector2i a{ 2, 3 };
			sf::Vector2i b{ 4, 5 };
			Assert::AreEqual(a.dot(b), 23);
		}
		TEST_METHOD(IsTrivial)
		{
			Assert::IsTrue(std::is_trivially_constructible_v<Core::Vector2i>);
			Assert::IsTrue(std::is_trivially_copyable_v<Core::Vector2i>);
			Assert::IsTrue(std::is_trivially_copy_assignable_v<Core::Vector2i>);
			Assert::IsTrue(std::is_trivially_default_constructible_v<Core::Vector2i>);
			Assert::IsTrue(std::is_trivially_move_assignable_v<Core::Vector2i>);
			Assert::IsTrue(std::is_trivially_move_constructible_v<Core::Vector2i>);
			Assert::IsTrue(std::is_trivial_v<Core::Vector2i>);
			Assert::IsTrue(std::is_destructible_v<Core::Vector2i>);
			Assert::IsTrue(std::is_trivially_destructible_v<Core::Vector2i>);
			Assert::IsTrue(std::is_swappable_v<Core::Vector2i>);

			Assert::IsTrue(std::is_nothrow_constructible_v<Core::Vector2i>);
			Assert::IsTrue(std::is_nothrow_copy_assignable_v<Core::Vector2i>);
			Assert::IsTrue(std::is_nothrow_copy_constructible_v<Core::Vector2i>);
			Assert::IsTrue(std::is_nothrow_default_constructible_v<Core::Vector2i>);
			Assert::IsTrue(std::is_nothrow_destructible_v<Core::Vector2i>);
			Assert::IsTrue(std::is_nothrow_move_assignable_v<Core::Vector2i>);
			Assert::IsTrue(std::is_nothrow_swappable_v<Core::Vector2i>);

		}
	};
}

#endif