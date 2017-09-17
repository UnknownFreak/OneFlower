#include "CppUnitTest.h"
#define _EDITOR_

#include <cereal\archives\binary.hpp>
#include <cereal\archives\xml.hpp>
#include <cereal\types\string.hpp>
#include <cereal\types\polymorphic.hpp>
#include <cereal\types\map.hpp>
#include <cereal\types\memory.hpp>
#include <cereal\access.hpp>

#include <AssetManager\IRequestable.hpp>
#include <AssetManager\Requestor\Reference.hpp>
#include <AssetManager\Requestor\Requestor.hpp>
#include <AssetManager\Mod\ModHeader.hpp>
#include <AssetManager\ObjectSaveMode.hpp>
#include <Logger\Logger.hpp>

#include <AssetManager\AssetManagerCore.hpp>

ModLoader Engine::modLoadOrder;
Core::String AssetManagerCore::openedMod = "test";

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
		static Requester<MockedSaveable> req;

		static void add_objects()
		{
			req.add(MockedSaveable(1, "A"));
			req.add(MockedSaveable(2, "B"));
			req.add(MockedSaveable(3, "C"));
			req.add(MockedSaveable(4, "DE"));
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
				ind.flags = DatabaseIndex::ObjectFlag::EoF;
				ind.ID = 0;
				ind.type = DatabaseIndex::ObjectTypeEnum::EoF;
				ind.modFile = modhdr.name;
				ind.row = file.tellp();
			}
			file.close();
			index.close();

			Engine::modLoadOrder.loadOrder.clear();
			Engine::modLoadOrder.loadOrder.insert(std::make_pair("test", 0));
			req.clear();

		}

		TEST_CLASS_INITIALIZE(Initialize)
		{
			OneLogger::initialize();
			add_objects();
			setup_file();
		}

		TEST_METHOD_CLEANUP(TestMethodCleanup)
		{
			req.clear();
		}

		TEST_METHOD(TestRequestor_OneRequest)
		{
			size_t expected = 1;
			Reference<MockedSaveable>*& ref = req.request("test", 1);
			Assert::AreEqual(ref->getUseCount(), expected);
			
			expected = 3;

			req.request("test", 1);
			req.request("test", 1);
			Assert::AreEqual(ref->getUseCount(), expected);
		}
		TEST_METHOD(TestRequestor_ThreeRequest)
		{
			size_t expected = 3;
			Reference<MockedSaveable>*& ref = req.request("test", 1);
			req.request("test", 1);
			req.request("test", 1);
			
			Assert::AreEqual(ref->getUseCount(), expected);
			req.clear();
		}
		TEST_METHOD(TestRequestor_Unrequest)
		{
			size_t expected = 2;
			size_t expectedAfterDelete = 1;
			Reference<MockedSaveable>*& ref = req.request("test", 1);
			req.request("test", 1);
			
			Assert::AreEqual(ref->getUseCount(), expected);
			req.requestRemoval("test", 1);
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
	};
	Requester<MockedSaveable> RequestorTest::req(DatabaseIndex::ObjectTypeEnum::Undefined);
}