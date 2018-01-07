#ifdef _UNITTESTS_
#include "CppUnitTest.h"

#include <AssetManager\AssetManagerCore.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace Tests
{		

	class MockedSaveable : public IRequestable
	{
	public:
		Core::String test_string;
		MockedSaveable(size_t id=1, Core::String test_string = "") : IRequestable("test", id), test_string(test_string)
		{
		}
		MockedSaveable(const MockedSaveable& c) : IRequestable(c), test_string(c.test_string)
		{
		}
		MockedSaveable& operator=(const MockedSaveable& r)
		{
			test_string = r.test_string;
			mode = r.mode;
			ID = r.ID;
			fromMod = r.fromMod;
			return *this;
		}
		template<class T>
		void save(T& archive) const
		{
			archive(cereal::base_class<IRequestable>(this));
			archive(test_string);
		}
		template<class T>
		void load(T& archive)
		{
			archive(cereal::base_class<IRequestable>(this));
			archive(test_string);
		}
	};

	TEST_CLASS(RequestorTest)
	{
	public:
		static Requestor<MockedSaveable> req;
		static Requestor<MockedSaveable*> req_ptr;

		static void add_objects()
		{
			req.add(MockedSaveable(1, "A"));
			req.add(MockedSaveable(2, "B"));
			req.add(MockedSaveable(3, "C"));
			req.add(MockedSaveable(4, "DE"));

			req_ptr.add(new MockedSaveable(5, "A_PTR"));
			req_ptr.add(new MockedSaveable(6, "B_PTR"));
			req_ptr.add(new MockedSaveable(7, "C_PTR"));
			req_ptr.add(new MockedSaveable(8, "DE_PTR"));

		}

		static void setup_file()
		{
			ModHeader modhdr;
			modhdr.name = "test";
			std::ofstream file("test", std::ios::binary);
			std::ofstream index("test.index", std::ios::binary);
			{
				DatabaseIndex ind;
				ind.flags = DatabaseIndex::ObjectFlag::NoFlag;
				ind.ID = 0;
				ind.type = DatabaseIndex::ObjectTypeEnum::Header;
				ind.modFile = modhdr.name;
				ind.row = file.tellp();
				cereal::BinaryOutputArchive mainAr(file);
				cereal::BinaryOutputArchive indexAr(index);


				req.save(ind, file, indexAr, mainAr);
				req_ptr.save(ind, file, indexAr, mainAr);
				
				ind.flags = DatabaseIndex::ObjectFlag::EoF;
				ind.ID = 0;
				ind.type = DatabaseIndex::ObjectTypeEnum::EoF;
				ind.modFile = modhdr.name;
				ind.row = file.tellp();

			}
			file.close();
			index.close();

			Engine::Get<AssetManager>().getModLoader().loadOrder.clear();
			Engine::Get<AssetManager>().getModLoader().loadOrder.insert(std::make_pair("test", 0));
			req.clear();
			req_ptr.clear();

		}

		TEST_CLASS_INITIALIZE(Initialize)
		{
			add_objects();
			setup_file();
		}

		TEST_METHOD_CLEANUP(TestMethodCleanup)
		{
			req.clear();
			req_ptr.clear();
		}

		TEST_METHOD(TestRequestor_OneRequest)
		{
			size_t expected = 1;
			Reference<MockedSaveable>*& ref = req.request("test", 1);
			Assert::AreEqual(ref->getUseCount(), expected);
		}
		TEST_METHOD(TestRequestor_ThreeRequest)
		{
			size_t expected = 3;
			Reference<MockedSaveable>*& ref = req.request("test", 1);
			req.request("test", 1);
			req.request("test", 1);
			
			Assert::AreEqual(ref->getUseCount(), expected);
		}
		TEST_METHOD(TestRequestor_Unrequest)
		{
			size_t expected = 2;
			size_t expectedAfterDelete = 1;
			Reference<MockedSaveable>*& ref = req.request("test", 1);
			req.request("test", 1);
			
			Assert::AreEqual(ref->getUseCount(), expected);
			Assert::IsFalse(req.requestRemoval("test", 1));
			Assert::AreEqual(ref->getUseCount(), expectedAfterDelete);
		}
		TEST_METHOD(TestRequestor_AddToExistingDoesNotReplace)
		{
			Assert::IsTrue(req.add(MockedSaveable(1, "A")));
			Assert::IsFalse(req.add(MockedSaveable(1, "CC")));

			Reference<MockedSaveable>*& ref = req.request("test", 1);
			MockedSaveable& m = ref->getReferenced();

			Assert::AreEqual(m.test_string.c_str(), "A");
		}
		TEST_METHOD(TestRequestor_AddNew)
		{
			Assert::IsTrue(req.add(MockedSaveable(21, "CC")));

			Reference<MockedSaveable>*& ref = req.request("test", 21);
			MockedSaveable m = ref->getReferenced();

			Assert::AreEqual(m.test_string.c_str(), "CC");
		}
		TEST_METHOD(TestRequestor_ExistingObjectHasSameData)
		{
			Reference<MockedSaveable>*& ref = req.request("test", 1);
			MockedSaveable m = ref->getReferenced();

			Assert::AreEqual(m.test_string.c_str(), "A");
			Assert::AreEqual(m.fromMod.c_str(), "test");
			Assert::AreEqual(m.ID, size_t(1));
		}


		TEST_METHOD(TestRequestorPtr_OneRequest)
		{
			size_t expected = 1;
			Reference<MockedSaveable*>*& ref = req_ptr.request("test", 5);
			Assert::AreEqual(ref->getUseCount(), expected);
		}
		TEST_METHOD(TestRequestorPtr_ThreeRequest)
		{
			size_t expected = 3;
			Reference<MockedSaveable*>*& ref = req_ptr.request("test", 5);
			req_ptr.request("test", 5);
			req_ptr.request("test", 5);

			Assert::AreEqual(ref->getUseCount(), expected);
		}
		TEST_METHOD(TestRequestorPtr_Unrequest)
		{
			size_t expected = 2;
			size_t expectedAfterDelete = 1;
			Reference<MockedSaveable*>*& ref = req_ptr.request("test", 5);
			req_ptr.request("test", 5);

			Assert::AreEqual(ref->getUseCount(), expected);
			Assert::IsFalse(req_ptr.requestRemoval("test", 5));
			Assert::AreEqual(ref->getUseCount(), expectedAfterDelete);
		}
		TEST_METHOD(TestRequestorPtr_AddToExistingDoesNotReplace)
		{
			Assert::IsTrue(req_ptr.add(new MockedSaveable(1, "A_PTR")));
			Assert::IsFalse(req_ptr.add(new MockedSaveable(1, "CC_PTR")));

			Reference<MockedSaveable*>*& ref = req_ptr.request("test", 5);
			MockedSaveable*& m = ref->getReferenced();

			Assert::AreEqual(m->test_string.c_str(), "A_PTR");
		}
		TEST_METHOD(TestRequestorPtr_AddNew)
		{
			Assert::IsTrue(req_ptr.add(new MockedSaveable(22, "CC_PTR")));

			Reference<MockedSaveable*>*& ref = req_ptr.request("test", 22);
			MockedSaveable* m = ref->getReferenced();

			Assert::AreEqual(m->test_string.c_str(), "CC_PTR");
		}
		TEST_METHOD(TestRequestorPtr_ExistingObjectHasSameData)
		{
			Reference<MockedSaveable*>*& ref = req_ptr.request("test", 5);
			MockedSaveable* m = ref->getReferenced();

			Assert::AreEqual(m->test_string.c_str(), "A_PTR");
			Assert::AreEqual(m->fromMod.c_str(), "test");
			Assert::AreEqual(m->ID, size_t(5));
		}

	};
	Requestor<MockedSaveable> RequestorTest::req(DatabaseIndex::ObjectTypeEnum::Undefined, "");
	Requestor<MockedSaveable*> RequestorTest::req_ptr(DatabaseIndex::ObjectTypeEnum::Undefined, "");
}

#endif