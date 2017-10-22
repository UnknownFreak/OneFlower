
#include "CppUnitTest.h"

#include <Graphic\Time\Time.hpp>
#include <chrono>
#include <thread>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(TimeUnitTest)
	{
	public:

		TEST_CLASS_INITIALIZE(Initialize)
		{
			Time::getTime();
		}

		TEST_CLASS_CLEANUP(Cleanup)
		{
			Time::deconstruct();
		}

		TEST_METHOD(TestTime)
		{
			Assert::IsFalse(Time::getTime().time("test", 5));
			std::this_thread::sleep_for(std::chrono::seconds(1));
			Assert::IsTrue(Time::getTime().time("test", 1));
		}
	};

}