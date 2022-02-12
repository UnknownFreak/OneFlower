#ifdef _UNITTESTS_

#include "CppUnitTest.h"

#include <File/CfgParser.hpp>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	namespace File
	{
		TEST_CLASS(ConfigFileTest)
		{
		public:

			static ::File::Resource::Config::ConfigParser i;

			TEST_METHOD_INITIALIZE(Initialize)
			{
				i.clear();
				i.put("test", "test", "Foo");
				i.put("test", "test2", 1L);
				i.put("test", "test3", 1.f);
				i.put("test", "test4", true);
				i.put("test", "test5", 1234L, "Comment tests");
				i.put("test2", "test", "test", "Comment tests");
			}

			TEST_METHOD(GetMissingSection)
			{
				auto x = i.get("asdada", "asdsadas", false);
				Assert::IsFalse(x);
			}
			TEST_METHOD(GetMissingKey)
			{
				i.put("test", "test", "Foo");
				auto x = i.get("test", "asdsadas", false);
				Assert::IsFalse(x);
			}
			TEST_METHOD(GetString)
			{
				Core::String x = i.get("test", "test", "F");
				Assert::AreEqual(x.c_str(), "Foo");
			}
			TEST_METHOD(GetLong)
			{
				auto x = i.get("test", "test2", 0L);
				Assert::AreEqual(x, 1L);
			}

			TEST_METHOD(GetInt)
			{
				auto x = i.get("test", "test2", 0);
				Assert::AreEqual(x, 1);
			}

			TEST_METHOD(GetFloat)
			{
				auto x = i.get("test", "test3", 0.f);
				Assert::AreEqual(x, 1.f);
			}
			TEST_METHOD(GetBool)
			{
				auto x = i.get("test", "test4", false);
				Assert::AreEqual(x, true);
			}
			TEST_METHOD(GetWithComment)
			{
				auto x = i.get("test", "test5", 0L);
				Assert::AreEqual(x, 1234L);
			}
			TEST_METHOD(LoadFile)
			{
				// see test.cfg in 64x/UnitTests
				i.load("test.cfg");
				auto s = i.get("section", "test1", "F");
				Assert::AreEqual(s.c_str(), "foo");
				auto s2 = i.get("section2", "test1", "F");
				Assert::AreEqual(s2.c_str(), "foo3");
				auto s3 = i.get("section2", "test2", 0L);
				Assert::AreEqual(s3, 123L);
			}

			TEST_METHOD(SaveFile)
			{
				i.save("test2.cfg");
				i.load();
				auto s = i.get("test", "test", "F");
				Assert::AreEqual(s.c_str(), "Foo");
				auto s2 = i.get("test", "test2", 0L);
				Assert::AreEqual(s2, 1L);
				auto s3 = i.get("test", "test3", 0.f);
				Assert::AreEqual(s3, 1.f);
				auto s4 = i.get("test", "test4", false);
				Assert::IsTrue(s4);
				auto s5 = i.get("test", "test5", 0L);
				Assert::AreEqual(s5, 1234L);
				auto s6 = i.get("test2", "test", "F");
				Assert::AreEqual(s6.c_str(), "test");
			}
		};
		::File::Resource::Config::ConfigParser ConfigFileTest::i;

	}
}

#endif