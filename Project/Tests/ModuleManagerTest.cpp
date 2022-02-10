#ifdef _UNITTESTS_

#include "CppUnitTest.h"
#include <Module/EngineModuleManager.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace TestFramework = Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	namespace EngineModule
	{

		class ModuleMock : public Interfaces::IEngineResource<ModuleMock>
		{
			Enums::EngineResourceType& getType() const
			{
				return type;
			}
		};

		TEST_CLASS(EngineModuleUnitTest)
		{

		public:

			TEST_METHOD(GetModule)
			{
				ModuleMock& dummyModule = Engine::GetModule<ModuleMock>();
				ModuleMock& dummyModule2 = Engine::GetModule<ModuleMock>();
				Assert::AreSame(dummyModule, dummyModule2);
			}
		};
	}

}
Enums::EngineResourceType Interfaces::IEngineResource<Tests::EngineModule::ModuleMock>::type = Enums::EngineResourceType::NOT_SET;

template<> inline std::wstring TestFramework::ToString<Tests::EngineModule::ModuleMock>(const Tests::EngineModule::ModuleMock& ) {
	return std::wstring(L"Module Mock");
}
template<> inline std::wstring TestFramework::ToString<Tests::EngineModule::ModuleMock>(const Tests::EngineModule::ModuleMock* ) {
	return std::wstring(L"Module Mock");
}
template<> inline std::wstring TestFramework::ToString<Tests::EngineModule::ModuleMock>(Tests::EngineModule::ModuleMock* ) {
	return std::wstring(L"Module Mock");
}
#endif