#ifdef _UNITTESTS_
#include "CppUnitTest.h"

#include <AssetManager\AssetManagerCore.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace Tests
{
	TEST_CLASS(ReferenceTest)
	{
	public:

		TEST_METHOD(testGetUnique)
		{

			int value = 1;
			Reference<int> r("test", 0, NULL, value);

			Assert::AreEqual(1, r.getUnique());
		}
		TEST_METHOD(testGetUniquePtr)
		{
			int* value = new int(1);
			Reference<int*> r("test", 0, NULL, value);
			Assert::AreEqual(1, r.getUnique());
		}
	};
}

#endif