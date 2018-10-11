#ifdef _UNITTESTS_
#include "CppUnitTest.h"

#include <Asset\Version.hpp>
#include <Core\EngineModule\EngineModuleManager.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace Tests
{

	TEST_CLASS(VersionTest)
	{
	public:

		TEST_METHOD(TestVersion_EMPTY)
		{
			OneVersion o = OneVersion::EMPTY;
			Assert::AreEqual(o.str().c_str(), "0.0.0");
		}

		TEST_METHOD(TestVersion_IncrementRevision)
		{
			OneVersion o(0, 0, 0);
			o.incRev();
			Assert::AreEqual(o.str().c_str(), "0.0.1");
		}
		TEST_METHOD(TestVersion_Equality)
		{
			OneVersion o(1, 2, 3);
			OneVersion c(1, 2, 3);
			Assert::AreEqual(o, c);
		}
		TEST_METHOD(TestVersion_Inequality)
		{
			OneVersion o(1, 2, 3);
			OneVersion c(1, 2, 4);
			Assert::AreNotEqual(o, c);
		}
		TEST_METHOD(TestVersion_GreaterThan)
		{
			OneVersion o(1, 2, 3);
			OneVersion c(1, 2, 4);
			Assert::IsFalse(o > c);
		}
		TEST_METHOD(TestVersion_LessThan)
		{
			OneVersion o(1, 2, 3);
			OneVersion c(1, 2, 4);
			Assert::IsTrue(o < c);
		}
		TEST_METHOD(TestVersion_GreaterThanEq)
		{
			OneVersion o(1, 2, 3);
			OneVersion c(1, 2, 3);
			Assert::IsTrue(o >= c);
		}
		TEST_METHOD(TestVersion_LessThanEq)
		{
			OneVersion o(1, 2, 3);
			OneVersion c(1, 2, 3);
			Assert::IsTrue(o <= c);
		}
		TEST_METHOD(TestVersion_Assignment)
		{
			OneVersion o(1, 2, 34);
			OneVersion c = o;
			Assert::IsTrue(c == o);
		}
		TEST_METHOD(TestVersion_CopyCtor)
		{
			OneVersion o(1, 2, 3);
			OneVersion c(o);
			Assert::IsTrue(c == o);
		}
	};
}
template<> inline std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<OneVersion>(const OneVersion& q) {
	return Engine::GetModule<Core::StringConverter>().toUtf16(((OneVersion&)q).str());
}
template<> inline std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<OneVersion>(const OneVersion* q) {
	return Engine::GetModule<Core::StringConverter>().toUtf16(((OneVersion&)q).str());
}
template<> inline std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<OneVersion>(OneVersion* q) {
	return Engine::GetModule<Core::StringConverter>().toUtf16(((OneVersion&)q).str());
}

#endif