#ifdef _UNITTESTS_
#include "CppUnitTest.h"

#include <Helpers\Rect.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace TestFramework = Microsoft::VisualStudio::CppUnitTestFramework;

template<> inline std::wstring TestFramework::ToString<Core::IntRect>(const Core::IntRect& q) {
	return std::wstring(std::to_wstring(q.x) + L", " + std::to_wstring(q.y)) + L", "
		+ std::wstring(std::to_wstring(q.w) + L", " + std::to_wstring(q.h));
}
template<> inline std::wstring TestFramework::ToString<Core::IntRect>(const Core::IntRect* q) {
	return std::wstring(std::to_wstring(q->x) + L", " + std::to_wstring(q->y)) + L", "
		+ std::wstring(std::to_wstring(q->w) + L", " + std::to_wstring(q->h));
}
template<> inline std::wstring TestFramework::ToString<Core::IntRect>(Core::IntRect* q) {
	return std::wstring(std::to_wstring(q->x) + L", " + std::to_wstring(q->y)) + L", "
		+ std::wstring(std::to_wstring(q->w) + L", " + std::to_wstring(q->h));
}

namespace Tests
{
	TEST_CLASS(RectTests)
	{
	public:

		TEST_METHOD(Contains)
		{
			Core::IntRect a{ 5, 5, 5, 5 };
			Core::IntRect b{ 5, 5, 5, 5 };
			Assert::IsTrue(a.contains(b));
		}

		TEST_METHOD(NotContains)
		{
			Core::IntRect a{ 5, 5, 5, 5 };
			Core::IntRect b{ 5, 5, 6, 6 };
			Assert::IsFalse(a.contains(b));
		}
		TEST_METHOD(Intersects)
		{
			Core::IntRect a{ 5, 5, 5, 5 };
			Core::IntRect b{ 4, 4, 5, 5 };
			Assert::IsTrue(b.intersects(a));

		}
		TEST_METHOD(NotIntersects)
		{
			Core::IntRect a{ 5, 5, 5, 5 };
			Core::IntRect b{ -4, 4, 5, 5 };
			Assert::IsFalse(b.intersects(a));

		}
		TEST_METHOD(IsTrivial)
		{
			Assert::IsTrue(std::is_trivially_constructible_v<Core::IntRect>);
			Assert::IsTrue(std::is_trivially_copyable_v<Core::IntRect>);
			Assert::IsTrue(std::is_trivially_copy_assignable_v<Core::IntRect>);
			Assert::IsTrue(std::is_trivially_default_constructible_v<Core::IntRect>);
			Assert::IsTrue(std::is_trivially_move_assignable_v<Core::IntRect>);
			Assert::IsTrue(std::is_trivially_move_constructible_v<Core::IntRect>);
			Assert::IsTrue(std::is_trivial_v<Core::IntRect>);
			Assert::IsTrue(std::is_destructible_v<Core::IntRect>);
			Assert::IsTrue(std::is_trivially_destructible_v<Core::IntRect>);
			Assert::IsTrue(std::is_swappable_v<Core::IntRect>);

			Assert::IsTrue(std::is_nothrow_constructible_v<Core::IntRect>);
			Assert::IsTrue(std::is_nothrow_copy_assignable_v<Core::IntRect>);
			Assert::IsTrue(std::is_nothrow_copy_constructible_v<Core::IntRect>);
			Assert::IsTrue(std::is_nothrow_default_constructible_v<Core::IntRect>);
			Assert::IsTrue(std::is_nothrow_destructible_v<Core::IntRect>);
			Assert::IsTrue(std::is_nothrow_move_assignable_v<Core::IntRect>);
			Assert::IsTrue(std::is_nothrow_swappable_v<Core::IntRect>);

		}
	};
}

#endif