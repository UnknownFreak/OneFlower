#include "CppUnitTest.h"

#include <Core\Vector.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define TestFramework Microsoft::VisualStudio::CppUnitTestFramework;

//template<> inline std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<Core::Vector2i>(const Core::Vector2i& q) {
//	return std::wstring(std::to_wstring(q.x) + L", " + std::to_wstring(q.y));
//}
//template<> inline std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<Core::Vector2i>(const Core::Vector2i* q) {
//	return std::wstring(std::to_wstring(q->x) + L", " + std::to_wstring(q->y));
//}
//template<> inline std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<Core::Vector2i>(Core::Vector2i* q) { 
//	return std::wstring(std::to_wstring(q->x) + L", " + std::to_wstring(q->y));
//}

namespace Tests
{
	TEST_CLASS(Vector2Test)
	{
	public:
	
		TEST_METHOD(Addition)
		{
			Core::Vector2i a(5, 5);
			Core::Vector2i b(5, 5);
			Assert::AreEqual<Core::Vector2i>(a + b , Core::Vector2i(10, 10));
		}
		TEST_METHOD(Subtraction)
		{
			Core::Vector2i a(5, 5);
			Core::Vector2i b(5, 5);
			Assert::AreEqual<Core::Vector2i>(a - b, Core::Vector2i(0, 0));
		}
	};
}