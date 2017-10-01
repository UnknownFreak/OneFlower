#include "CppUnitTest.h"

#include <Core\String.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(StringConverterUnitTest)
	{
	public:

		static Core::StringConverter con;

		TEST_CLASS_INITIALIZE(Init)
		{
		
		}

		TEST_CLASS_CLEANUP(Cleanup)
		{
			con.deconstruct();
		}

		TEST_METHOD(Utf8ToUtf16)
		{
			//Core::String test = "ö";
			//std::wstring expect = L"ö";
			//
			//Assert::AreEqual(con.toUtf16(test), expect);
			Assert::Fail(L"Failed due to compiler failing to compile above characters");

		}

		TEST_METHOD(Utf16ToUtf8)
		{
			//Core::String expect = "ö";
			//std::wstring test= L"ö";
			//Core::String result = con.toUtf8(test);
			//Assert::AreEqual(result, expect);
			Assert::Fail(L"Failed due to compiler failing to compile above characters");
		}
	};
	Core::StringConverter StringConverterUnitTest::con;

}