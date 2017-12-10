#ifdef _UNITTESTS_

#include "CppUnitTest.h"

#include <Graphic\Time\Time.hpp>
#include <Core\IEngineResource\EngineResourceManager.hpp>
#include <thread>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(TimeUnitTest)
	{
	public:


		TEST_METHOD(TestTime)
		{
			Assert::IsFalse(Engine::Get<Time>().time("test", 5));
			std::this_thread::sleep_for(std::chrono::seconds(1));
			Assert::IsTrue(Engine::Get<Time>().time("test", 1));
		}
	};

}

#endif