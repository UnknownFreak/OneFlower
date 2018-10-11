#ifdef _UNITTESTS_
#include "CppUnitTest.h"

#include <Asset\AssetManagerCore.hpp>
#include <Core/Component/TransformComponent.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace Tests
{		

	class MockedSaveable : public IRequestable
	{
	public:
		Core::String test_string;
		MockedSaveable(size_t id=1, Core::String test_string = "") : IRequestable("test", id, OneVersion(0,0,0)), test_string(test_string)
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

	static void create_prefab(Requestor<Asset::Prefab>& pref, size_t id)
	{
		Asset::Prefab p;
		p.fromMod = "test";
		p.ID = id;
		p.mode = ObjectSaveMode::ADD;
		//p.name = "asdasfs";
		p.base.push_back(new Component::Transform);
		pref.add(p);
	}

	TEST_CLASS(RequestorTest)
	{
	public:
		static Requestor<MockedSaveable> req;
		static Requestor<MockedSaveable*> req_ptr;
		static Requestor<Asset::Prefab> prefab;

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

			create_prefab(prefab, 1);
			create_prefab(prefab, 2);

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
				prefab.save(ind, file, indexAr, mainAr);
				
				ind.flags = DatabaseIndex::ObjectFlag::EoF;
				ind.ID = 0;
				ind.type = DatabaseIndex::ObjectTypeEnum::EoF;
				ind.modFile = modhdr.name;
				ind.row = file.tellp();

				indexAr(ind);

			}
			file.close();
			index.close();

			Engine::GetModule<Asset::AssetManager>().getModLoader().loadOrder.clear();
			Engine::GetModule<Asset::AssetManager>().getModLoader().loadOrder.insert(std::make_pair("test", 0));
			req.clear();
			req_ptr.clear();
			prefab.clear();

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

		TEST_METHOD(TestRequetorNonPointer)
		{
			MockedSaveable& ref = req.request("test", 1);
			Assert::AreEqual("A", ref.test_string.c_str());
			Assert::AreEqual((size_t)1, ref.ID);
		}
		TEST_METHOD(TestRequestorPointer)
		{
			MockedSaveable*& ref = req_ptr.request("test", 5);
			Assert::AreEqual("A_PTR", ref->test_string.c_str());
			Assert::AreEqual((size_t)5, ref->ID);
		}
		TEST_METHOD(TestRequestorEmpty)
		{
			MockedSaveable*& ref = req_ptr.request("test", 5555);
			Assert::IsNull(ref);
		}
		TEST_METHOD(TestRequestor_AddToExistingDoesNotReplace)
		{
			Assert::IsTrue(req.add(MockedSaveable(1, "A")));
			Assert::IsFalse(req.add(MockedSaveable(1, "CC")));
		
			MockedSaveable& ref = req.request("test", 1);
			Assert::AreEqual(ref.test_string.c_str(), "A");
		}
		TEST_METHOD(TestRequestor_AddNew)
		{
			Assert::IsTrue(req.add(MockedSaveable(21, "CC")));
		
			MockedSaveable& ref = req.request("test", 21);
			Assert::AreEqual(ref.test_string.c_str(), "CC");
		}
		TEST_METHOD(TestRequestorPtr_AddToExistingDoesNotReplace)
		{
			Assert::IsTrue(req_ptr.add(new MockedSaveable(1, "A_PTR")));
			Assert::IsFalse(req_ptr.add(new MockedSaveable(1, "CC_PTR")));
		
			MockedSaveable*& ref = req_ptr.request("test", 5);
		
			Assert::AreEqual(ref->test_string.c_str(), "A_PTR");
		}
		TEST_METHOD(TestRequestorPtr_AddNew)
		{
			Assert::IsTrue(req_ptr.add(new MockedSaveable(22, "CC_PTR")));
		
			MockedSaveable*& ref = req_ptr.request("test", 22);
		
			Assert::AreEqual(ref->test_string.c_str(), "CC_PTR");
		}

		TEST_METHOD(TestRequestPolymorphicDoesNotRaise)
		{
			// fails
			{
				prefab.request("test", 1);
				 prefab.request("test", 2);
			}
			// fails
			{
				//Asset::Prefab& p = prefab.request("test", 1);
				prefab.request("test", 2);
			}
			// works
			{
				prefab.request("test", 1);
				//Asset::Prefab& p2 = prefab.request("test", 2);
			}
		}

	};
	Requestor<MockedSaveable> RequestorTest::req(DatabaseIndex::ObjectTypeEnum::Undefined, "");
	Requestor<MockedSaveable*> RequestorTest::req_ptr(DatabaseIndex::ObjectTypeEnum::Undefined, "");
	Requestor<Asset::Prefab> RequestorTest::prefab(DatabaseIndex::ObjectTypeEnum::Prefab, "");
}

#endif