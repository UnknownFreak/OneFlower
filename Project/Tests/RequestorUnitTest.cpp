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
		MockedSaveable() : MockedSaveable(Core::uuid::nil(), "") {}
		MockedSaveable(Core::uuid id, Core::String test_string = "") : IRequestable("test", id, OneVersion(0,0,0)), test_string(test_string)
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

	static void create_prefab(Requestor<Asset::Prefab>& pref, Core::uuid id)
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
		static Core::uuid id1;
		static Core::uuid id2;
		static Core::uuid id3;
		static Core::uuid id4;
		static Core::uuid id5;
		static Core::uuid id6;
		static Core::uuid id7;
		static Core::uuid id8;
		static Core::uuid id9;
		static Core::uuid id10;
		static Requestor<MockedSaveable> req;
		static Requestor<MockedSaveable*> req_ptr;
		static Requestor<Asset::Prefab> prefab;

		static void add_objects()
		{
			req.add(MockedSaveable(id1, "A"));
			req.add(MockedSaveable(id2, "B"));
			req.add(MockedSaveable(id3, "C"));
			req.add(MockedSaveable(id4, "DE"));

			req_ptr.add(new MockedSaveable(id5, "A_PTR"));
			req_ptr.add(new MockedSaveable(id6, "B_PTR"));
			req_ptr.add(new MockedSaveable(id7, "C_PTR"));
			req_ptr.add(new MockedSaveable(id8, "DE_PTR"));

			create_prefab(prefab, id9);
			create_prefab(prefab, id10);

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
				ind.ID = Core::uuid::nil();
				ind.type = DatabaseIndex::ObjectTypeEnum::Header;
				ind.modFile = modhdr.name;
				ind.row = file.tellp();
				cereal::BinaryOutputArchive mainAr(file);
				cereal::BinaryOutputArchive indexAr(index);


				req.save(ind, file, indexAr, mainAr);
				req_ptr.save(ind, file, indexAr, mainAr);
				prefab.save(ind, file, indexAr, mainAr);
				
				ind.flags = DatabaseIndex::ObjectFlag::EoF;
				ind.ID = Core::uuid::nil();
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
			MockedSaveable& ref = req.request("test", id1);
			Assert::AreEqual("A", ref.test_string.c_str());
			Assert::AreEqual(id1.to_wstring(), ref.ID.to_wstring());
		}
		TEST_METHOD(TestRequestorPointer)
		{
			MockedSaveable*& ref = req_ptr.request("test", id5);
			Assert::AreEqual("A_PTR", ref->test_string.c_str());
			Assert::AreEqual(id5.to_wstring(), ref->ID.to_wstring());
		}
		TEST_METHOD(TestRequestorEmpty)
		{
			MockedSaveable*& ref = req_ptr.request("test", Core::uuid());
			Assert::IsNull(ref);
		}
		TEST_METHOD(TestRequestor_AddToExistingDoesNotReplace)
		{
			Assert::IsTrue(req.add(MockedSaveable(id1, "A")));
			Assert::IsFalse(req.add(MockedSaveable(id1, "CC")));
		
			MockedSaveable& ref = req.request("test", id1);
			Assert::AreEqual(ref.test_string.c_str(), "A");
		}
		TEST_METHOD(TestRequestor_AddNew)
		{
			Core::uuid id21;
			Assert::IsTrue(req.add(MockedSaveable(id21, "CC")));
		
			MockedSaveable& ref = req.request("test", id21);
			Assert::AreEqual(ref.test_string.c_str(), "CC");
		}
		TEST_METHOD(TestRequestorPtr_AddToExistingDoesNotReplace)
		{
			Assert::IsTrue(req_ptr.add(new MockedSaveable(id5, "A_PTR")));
			Assert::IsFalse(req_ptr.add(new MockedSaveable(id5, "CC_PTR")));
		
			MockedSaveable*& ref = req_ptr.request("test", id5);
		
			Assert::AreEqual(ref->test_string.c_str(), "A_PTR");
		}
		TEST_METHOD(TestRequestorPtr_AddNew)
		{
			Core::uuid id;
			Assert::IsTrue(req_ptr.add(new MockedSaveable(id, "CC_PTR")));
		
			MockedSaveable*& ref = req_ptr.request("test", id);
		
			Assert::AreEqual(ref->test_string.c_str(), "CC_PTR");
		}

		TEST_METHOD(TestRequestPolymorphicDoesNotRaise)
		{
			// fails
			{
				prefab.request("test", id9);
				 prefab.request("test", id10);
			}
			// fails
			{
				//Asset::Prefab& p = prefab.request("test", 1);
				prefab.request("test", id10);
			}
			// works
			{
				prefab.request("test", id9);
				//Asset::Prefab& p2 = prefab.request("test", 2);
			}
		}

	};
	Core::uuid RequestorTest::id1 = Core::uuid();
	Core::uuid RequestorTest::id2 = Core::uuid();
	Core::uuid RequestorTest::id3 = Core::uuid();
	Core::uuid RequestorTest::id4 = Core::uuid();
	Core::uuid RequestorTest::id5 = Core::uuid();
	Core::uuid RequestorTest::id6 = Core::uuid();
	Core::uuid RequestorTest::id7 = Core::uuid();
	Core::uuid RequestorTest::id8 = Core::uuid();
	Core::uuid RequestorTest::id9 = Core::uuid();
	Core::uuid RequestorTest::id10 = Core::uuid();
	Requestor<MockedSaveable> RequestorTest::req(DatabaseIndex::ObjectTypeEnum::Undefined, "");
	Requestor<MockedSaveable*> RequestorTest::req_ptr(DatabaseIndex::ObjectTypeEnum::Undefined, "");
	Requestor<Asset::Prefab> RequestorTest::prefab(DatabaseIndex::ObjectTypeEnum::Prefab, "");
}

#endif