#include "CppUnitTest.h"

#include <AssetManager\Version\Version.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace Tests
{

	TEST_CLASS(VersionTest)
	{
	public:
		static Core::StringConverter con;

		TEST_CLASS_CLEANUP(VersionTestModuleCleanup)
		{
			con.deconstruct();
		}

		TEST_METHOD(TestVersion)
		{
			OneVersion o(0, 0, 0);
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
	};
	Core::StringConverter VersionTest::con;
}
template<> inline std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<OneVersion>(const OneVersion& q) {
	return Tests::VersionTest::con.toUtf16(((OneVersion&)q).str());
}
template<> inline std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<OneVersion>(const OneVersion* q) {
	return Tests::VersionTest::con.toUtf16(((OneVersion&)q).str());
}
template<> inline std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<OneVersion>(OneVersion* q) {
	return Tests::VersionTest::con.toUtf16(((OneVersion&)q).str());
}