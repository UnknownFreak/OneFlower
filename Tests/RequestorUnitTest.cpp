#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{		
	TEST_CLASS(RequestorTest)
	{
	public:
		
		TEST_CLASS_INITIALIZE(Initialize)
		{

		}

		TEST_METHOD(TestRequestor)
		{
			// TODO: Your test code here
			Assert::AreEqual(1, 0);
		}

	};
}