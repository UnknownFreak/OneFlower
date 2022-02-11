#ifdef _UNITTESTS_
#include "CppUnitTest.h"

#include <cereal/types/polymorphic.hpp>
#include "TestObjects.hpp"
#include <File/Resource/RegisterRTTI.hpp>

#include <Helpers/Enum/ObjectType.hpp>
#include <Interfaces/IRequestable.hpp>
#include <File/ModHeader.hpp>
#include <File/Resource/RequestorV2.hpp>
#include <File/AssetManagerCore.hpp>

#include <Helpers/uuid.hpp>
#include <Helpers/String.hpp>


//Enums::ObjectType Interfaces::Trait<Tests::MockedSaveable>::type = Enums::ObjectType::ColliderChunk;
//Enums::ObjectType Interfaces::Trait<Tests::MockedSaveable2>::type = Enums::ObjectType::DBZone;
//Enums::ObjectType Interfaces::Trait<Tests::MockedSaveable3>::type = Enums::ObjectType::DBZone;

#include <cereal/archives/binary.hpp>
#include <cereal\access.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace Tests
{		
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
		static RequestorV2 req_ptr;

		static void add_objects()
		{
			req_ptr.add<MockedSaveable>(new MockedSaveable(id1, "A_PTR"));
			req_ptr.add<MockedSaveable2>(new MockedSaveable2(id2, "B_PTR"));
			req_ptr.add<MockedSaveable>(new MockedSaveable(id3, "C_PTR"));
			req_ptr.add<MockedSaveable2>(new MockedSaveable2(id4, "DE_PTR"));
			req_ptr.add<MockedSaveable2>(new MockedSaveable3(id5, "FG_PTR", "HI_PTR"));
		}

		static void setup_file()
		{
			File::Mod::ModHeader modhdr;
			modhdr.name = "test";
			std::ofstream file("test", std::ios::binary);
			std::ofstream index("test.index", std::ios::binary);
			{
				DatabaseIndex ind;
				ind.flags = Enums::ObjectFlag::NoFlag;
				ind.ID = Core::uuid::nil();
				ind.type = Enums::ObjectType::Header;
				ind.modFile = modhdr.name;
				ind.row = file.tellp();
				cereal::BinaryOutputArchive mainAr(file);
				cereal::BinaryOutputArchive indexAr(index);

				req_ptr.save(ind, file, indexAr, mainAr);
				
				ind.flags = Enums::ObjectFlag::EoF;
				ind.ID = Core::uuid::nil();
				ind.type = Enums::ObjectType::EoF;
				ind.modFile = modhdr.name;
				ind.row = file.tellp();

				indexAr(ind);

			}
			file.close();
			index.close();

			Engine::GetModule<Asset::AssetManager>().getModLoader().loadOrder.clear();
			Engine::GetModule<Asset::AssetManager>().getModLoader().loadOrder.insert(std::make_pair("test", 0));
		}

		TEST_CLASS_INITIALIZE(Initialize)
		{
			add_objects();
			setup_file();
		}

		TEST_METHOD_CLEANUP(TestMethodCleanup)
		{
			req_ptr.clear();
		}

		TEST_METHOD(TestRequestorPointerSameType)
		{
			MockedSaveable* ref = req_ptr.request<MockedSaveable>(File::Mod::ModFileUUIDHelper("test", id1));
			Assert::IsNotNull(ref);
			Assert::AreEqual("A_PTR", ref->test_string.c_str());
			Assert::AreEqual(id1.to_wstring(), ref->ID.to_wstring());
		}
		TEST_METHOD(TestRequestorPointerSameType2)
		{
			MockedSaveable2* ref = req_ptr.request<MockedSaveable2>(File::Mod::ModFileUUIDHelper("test", id2));
			Assert::IsNotNull(ref);
			Assert::AreEqual("B_PTR", ref->test_string.c_str());
			Assert::AreEqual(id2.to_wstring(), ref->ID.to_wstring());
		}
		TEST_METHOD(TestRequestorPointerSameType3)
		{
			MockedSaveable3* ref = req_ptr.request<MockedSaveable3>(File::Mod::ModFileUUIDHelper("test", id5));
			Assert::IsNotNull(ref);
			Assert::AreEqual("FG_PTR", ref->test_string.c_str());
			Assert::AreEqual("HI_PTR", ref->another_test_string.c_str());
			Assert::AreEqual(id5.to_wstring(), ref->ID.to_wstring());
		}

		TEST_METHOD(TestRequestorPointerHigherBase)
		{
			MockedSaveable2* ref = req_ptr.request<MockedSaveable2>(File::Mod::ModFileUUIDHelper("test", id5));
			Assert::IsNotNull(ref);
			Assert::AreEqual("FG_PTR", ref->test_string.c_str());
			Assert::AreEqual("HI_PTR", ((MockedSaveable3*)ref)->another_test_string.c_str());
			Assert::AreEqual(id5.to_wstring(), ref->ID.to_wstring());
		}

		TEST_METHOD(TestRequestorEmpty)
		{
			MockedSaveable* ref = req_ptr.request<MockedSaveable>({ "test", Core::uuid() });
			Assert::IsNull(ref);
		}
		TEST_METHOD(TestRequestorPtr_AddToExistingDoesNotReplace)
		{
			Assert::IsTrue(req_ptr.add(new MockedSaveable(id1, "A_PTR")));
			Assert::IsFalse(req_ptr.add(new MockedSaveable(id1, "CC_PTR")));
		
			MockedSaveable* ref = req_ptr.request<MockedSaveable>({ "test", id1 });
		
			Assert::IsNotNull(ref);
			Assert::AreEqual(ref->test_string.c_str(), "A_PTR");
		}
		TEST_METHOD(TestRequestorPtr_AddNew)
		{
			Core::uuid id;
			Assert::IsTrue(req_ptr.add(new MockedSaveable2(id, "CC_PTR")));
		
			MockedSaveable2* ref = req_ptr.request<MockedSaveable2>({ "test", id });
		
			Assert::IsNotNull(ref);
			Assert::AreEqual(ref->test_string.c_str(), "CC_PTR");
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
	//Requestor<MockedSaveable> RequestorTest::req(Enums::ObjectType::Undefined, "");
	RequestorV2 RequestorTest::req_ptr("");

	//Requestor<Asset::Prefab> RequestorTest::prefab(Enums::ObjectType::Prefab, "");
}

#endif