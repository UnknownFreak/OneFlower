#ifdef _UNITTESTS_
#include "CppUnitTest.h"

#include <Helpers/ListDir.hpp>
#include <File/Asset/Manager.hpp>
#include <Language/LanguageRequestor.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace Tests
{
	TEST_CLASS(LanguageRequestorTest)
	{
	public:
		static File::Archive::RequestorV2 req;
		static Core::uuid id1, id2;
		static Language::LanguageRequestor& r()
		{
			return *req.request<Language::LanguageRequestor>({ Core::Builtin, Core::uuid::nil() }, true);
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
			
			r().addString("Test1", id1, "TestString", lang1);
			r().addString("Test2", id1, "TestString2", lang2);
			r().addString("Test3", id1, "TestString3", lang3);
			
			r().addString("Test1", id2, "Empty", lang1);
			r().addString("Test1", id2, "Patched", lang2, true);
			r().addString("Test2", id2, "Empty2", lang2);
			r().addString("Test3", id2, "Empty3", lang3);

		}

		static void remove_old_files()
		{
			Helpers::os::clearDirectory(Core::langPath);
		}

		static void setup_file()
		{
			File::Mod::Header modhdr;
			modhdr.name = "test";
			std::ofstream file("test", std::ios::binary);
			std::ofstream index("test.index", std::ios::binary);
			{
				File::Archive::DatabaseIndex ind;
				ind.flags = Enums::ObjectFlag::NoFlag;
				ind.ID = Core::uuid::nil();
				ind.type = Enums::ObjectType::Header;
				ind.modFile = modhdr.name;
				ind.row = file.tellp();
				cereal::BinaryOutputArchive mainAr(file);
				cereal::BinaryOutputArchive indexAr(index);

				req.save(ind, file, indexAr, mainAr);

				ind.flags = Enums::ObjectFlag::EoF;
				ind.ID = Core::uuid::nil();
				ind.type = Enums::ObjectType::EoF;
				ind.modFile = modhdr.name;
				ind.row = file.tellp();

				indexAr(ind);

			}
			file.close();
			index.close();

			Engine::GetModule<File::Asset::Manager>().getModLoader().loadOrder.clear();
			Engine::GetModule<File::Asset::Manager>().getModLoader().loadOrder.insert(std::make_pair("test", 0));
			r().clear();
			req.clear();
		}

		TEST_CLASS_INITIALIZE(Initialize)
		{
			remove_old_files();
			add_objects(); 
			setup_file();
		}

		TEST_METHOD_CLEANUP(TestMethodCleanup)
		{
			req.clear();
		}

		TEST_METHOD(TestListDir)
		{
			std::vector<Core::String> expected = { "LangTest", "LangTest2", "LangTest3" };
			std::vector<Core::String> s = Helpers::os::listDirectory(Core::langPath, ".lang", true);
			for (size_t i = 0; i < s.size(); i++)
				Assert::IsTrue(s[i] == expected[i]);
		}

		TEST_METHOD(TestGetStringFirstLanguage)
		{
			r().setLanguage("Test1");
			Core::String& s = r().getString(id1);
			Assert::AreEqual("TestString", s.c_str());
		}
	
		TEST_METHOD(TestGetStringSecondLanguage)
		{
			r().setLanguage("Test2");
			Core::String& s = r().getString(id1);
			Assert::AreEqual("TestString2", s.c_str());
			s = r().getString(id2);
			Assert::AreEqual("Empty2", s.c_str());
		}
		TEST_METHOD(TestGetStringPatchedFirstLanguage)
		{
			r().setLanguage("Test1");
			Core::String& s = r().getString(id2);
			Assert::AreEqual("Patched", s.c_str());
		}
		TEST_METHOD(TestGetStringPatchedSecondLanguage)
		{
			r().setLanguage("Test2");
			Core::String& s = r().getString(id2);
			Assert::AreEqual("Empty2", s.c_str());
		}
	};
	File::Archive::RequestorV2 LanguageRequestorTest::req;
	Core::uuid LanguageRequestorTest::id1;
	Core::uuid LanguageRequestorTest::id2;
}

#endif