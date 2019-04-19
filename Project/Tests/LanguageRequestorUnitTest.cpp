#ifdef _UNITTESTS_
#include "CppUnitTest.h"

#include <Asset\AssetManagerCore.hpp>
#include <Asset/LanguageRequestor.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace Tests
{
	TEST_CLASS(LanguageRequestorTest)
	{
	public:
		static Requestor<Language::LanguageRequestor> req;

		static Language::LanguageRequestor& r()
		{
			return req.request(Core::Builtin, 0);
		}

		static void add_objects()
		{
			Core::String lang1 = "LangTest.lang";
			Core::String lang2 = "LangTest2.lang";
			Core::String lang3 = "LangTest3.lang";
			r().clear();
			r().addLanguage(lang1, "Arial.ttf");
			r().addLanguage(lang2, "Arial.ttf");
			r().addLanguage(lang3, "Arial.ttf");
			
			r().addString("Test1", 1, "TestString", lang1);
			r().addString("Test2", 1, "TestString2", lang2);
			r().addString("Test3", 1, "TestString3", lang3);
			
			r().addString("Test1", 2, "Empty", lang1);
			r().addString("Test1", 2, "Patched", lang2, true);
			r().addString("Test2", 2, "Empty2", lang2);
			r().addString("Test3", 2, "Empty3", lang3);

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

				indexAr(ind);

			}
			file.close();
			index.close();

			Engine::GetModule<Asset::AssetManager>().getModLoader().loadOrder.clear();
			Engine::GetModule<Asset::AssetManager>().getModLoader().loadOrder.insert(std::make_pair("test", 0));
			r().clear();
			req.clear();
		}

		TEST_CLASS_INITIALIZE(Initialize)
		{
			add_objects(); 
			setup_file();
		}

		TEST_METHOD_CLEANUP(TestMethodCleanup)
		{
			req.clear();
		}

		TEST_METHOD(TestListDir)
		{
			std::vector<Core::String> expected = { "a", "b", "c" };
			std::vector<Core::String> s = listDirectory(Core::dataPath + "List//", ".txt", true);
			for (size_t i = 0; i < s.size(); i++)
				Assert::IsTrue(s[i] == expected[i]);
		}

		TEST_METHOD(TestGetStringfirstLanguage)
		{
			r().setLanguage("Test1");
			Core::String& s = r().getString(1);
			Assert::AreEqual("TestString", s.c_str());
		}
	
		TEST_METHOD(TestGetStringSecondLanguage)
		{
			r().setLanguage("Test2");
			Core::String& s = r().getString(1);
			Assert::AreEqual("TestString2", s.c_str());
		}
		TEST_METHOD(TestGetStringPatchedFirstLanguage)
		{
			r().setLanguage("Test1");
			Core::String& s = r().getString(2);
			Assert::AreEqual("Patched", s.c_str());
		}
		TEST_METHOD(TestGetStringPatchedSecondLanguage)
		{
			r().setLanguage("Test2");
			Core::String& s = r().getString(2);
			Assert::AreEqual("Empty2", s.c_str());
		}
	};
	Requestor<Language::LanguageRequestor> LanguageRequestorTest::req(DatabaseIndex::ObjectTypeEnum::Language, "");
}

#endif