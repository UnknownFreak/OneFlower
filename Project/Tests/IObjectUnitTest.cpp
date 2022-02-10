#ifdef _UNITTESTS_

#include "CppUnitTest.h"

#include <Interfaces/IObject.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(IObjectUnitTest)
	{
	public:

		TEST_METHOD(Construct)
		{
			Interfaces::IObject foo;
			Interfaces::IObject foo2;
			Assert::AreNotEqual(foo2.identifier.to_string(), foo.identifier.to_string());
		}

		TEST_METHOD(CopyConstruct)
		{
			Interfaces::IObject foo;
			Interfaces::IObject fooCopy(foo);
			Assert::AreEqual(foo.identifier.to_string(), fooCopy.identifier.to_string());
		}

		TEST_METHOD(AssignmentOperator)
		{
			Interfaces::IObject foo;
			Interfaces::IObject fooAssign = foo;
			Assert::AreEqual(foo.identifier.to_string(), fooAssign.identifier.to_string());
		}
	};
}

#endif