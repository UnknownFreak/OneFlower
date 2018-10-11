#ifdef _UNITTESTS_

#include "CppUnitTest.h"

#include <Core\String.hpp>
#include <Core\EngineModule\EngineModuleManager.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(StringConverterUnitTest)
	{
	public:

		TEST_METHOD(Utf8ToUtf16)
		{
			Core::String test = { char(0xc2), char(0xa5) }; // ¥
			std::wstring expect = L"¥";
			
			Assert::AreEqual(Engine::GetModule<Core::StringConverter>().toUtf16(test), expect);

		}

		TEST_METHOD(Utf16ToUtf8)
		{
			Core::String expect = { char(0xc2), char(0xa5) }; // ¥
			std::wstring test = L"¥";
			Core::String result = Engine::GetModule<Core::StringConverter>().toUtf8(test); 
			Assert::AreEqual(result, expect);
		}
	};
}

#endif