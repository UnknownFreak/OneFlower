#ifdef _UNITTESTS_

#include "CppUnitTest.h"

#include <Object/ObjectInstanceHandler.hpp>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	namespace EngineModule
	{
		TEST_CLASS(ObjectInstanceHandlerTest)
		{
		public:

			static GameObject go;
			static ::EngineModule::ObjectInstanceHandler i;
			static Core::uuid existing;
			static Core::uuid notExisting;

			TEST_CLASS_INITIALIZE(Initialize)
			{
				
				i.player = &go;
				i.player->id = Core::uuid::nil();
				existing = i.addObject()->id;
			}

			TEST_METHOD(TestExists)
			{
				Assert::IsTrue(i.exists(existing));
			}

			TEST_METHOD(TestNotExists)
			{
				Assert::IsFalse(i.exists(notExisting));
			}

			TEST_METHOD(TestGetExists)
			{
				Assert::IsNotNull(i.getObject(existing));
			}

			TEST_METHOD(TestGetNotExists)
			{
				Assert::IsNull(i.getObject(notExisting));
			}

			TEST_METHOD(TestGetNilReturnsPlayer)
			{
				Assert::IsNotNull(i.getObject(Core::uuid::nil()));
			}
		};
		::EngineModule::ObjectInstanceHandler ObjectInstanceHandlerTest::i;
		GameObject ObjectInstanceHandlerTest::go;
		Core::uuid ObjectInstanceHandlerTest::existing = Core::uuid();
		Core::uuid ObjectInstanceHandlerTest::notExisting = Core::uuid();

	}
}

#endif