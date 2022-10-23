#include "Manager.hpp"

#include <File/Archive/DatabaseIndex.hpp>
#include <fstream>

#include <cereal\archives\binary.hpp>
#include <cereal\types\string.hpp>
#include <cereal\types\polymorphic.hpp>
#include <cereal\types\map.hpp>
#include <cereal\types\unordered_map.hpp>
#include <cereal\types\unordered_set.hpp>
#include <cereal\types\memory.hpp>
#include <cereal\access.hpp>

#ifdef _EDITOR_
#include <Editor/EditorEvents.hpp>
#endif

Enums::EngineResourceType Interfaces::IEngineResource<File::Asset::Manager>::type = Enums::EngineResourceType::AssetManager;

namespace File::Asset
{

	void Manager::saveModOrderFile()
	{
		std::ofstream file("Data\\ModLoadOrder.xml");
		{
			cereal::XMLOutputArchive ar(file);
			ar(modLoader);
		}
	}

	void Manager::buildModOrderFile(const Core::String& modFile, std::set<Core::String>& dependencies)
	{
		modLoader.loadOrder.clear();
		for (auto& name : dependencies)
		{
			modLoader.loadOrder.insert(std::make_pair(name, modLoader.loadOrder.size()));
		}
		modLoader.loadOrder.insert(std::make_pair(modFile, modLoader.loadOrder.size()));
		auto& logger = Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("File::Asset::Manager");
		logger.Info("New load order built: Order is as follows,");
		for (auto& order : modLoader.loadOrder)
		{
			logger.Info(order.first);
		}
		logger.Info("End of load order.");
	}

	Manager::Manager() : 
		openedMod(),
		modLoader(Engine::GetModule<File::Mod::Loader>())
	{
		openedMod.name = "<Not Set>";
	}

	void Manager::saveGameDatabase(
		std::string filename,
		File::Mod::Header& modhdr)
	{
		std::ofstream file(Core::dataPath + filename, std::ios::binary | std::ios::out);
		filename.append(".index");
		std::ofstream index(Core::dataPath + filename, std::ios::binary | std::ios::out);
		{

			File::Archive::DatabaseIndex ind;
			cereal::BinaryOutputArchive mainAr(file);
			cereal::BinaryOutputArchive indexAr(index);
			ind.flags = Enums::ObjectFlag::NoFlag;
			ind.ID = Core::uuid::nil();
			ind.type = Enums::ObjectType::Header;
			ind.modFile = modhdr.name;
			ind.row = file.tellp();
			indexAr(ind);
			mainAr(modhdr);

			//lang.save(ind, file, indexAr, mainAr);
			requestor.save(ind, file, indexAr, mainAr);

			ind.ID = Core::uuid::nil();
			ind.type = Enums::ObjectType::EoF;
			ind.row = file.tellp();
			ind.flags = Enums::ObjectFlag::EoF;
			indexAr(ind);
		}
		file.close();
		index.close();
	}

	Language::LanguageRequestor & Manager::getLanguage()
	{
		return *requestor.request<Language::LanguageRequestor>({ Core::Builtin, Core::uuid::nil() }, true);
	}

	File::Mod::Loader & Manager::getModLoader()
	{
		return modLoader;
	}

	void Manager::loadAllEditorVariables()
	{
		requestor.editorLoadAll();
	}

	std::map<Core::String, Language::TranslationString> Manager::loadLanguages(const std::vector<Core::String>& languageFiles)
	{
		std::map<Core::String, Language::TranslationString> tmp;

		Language::TranslationString translationStr;
		for(Core::String var : languageFiles)
		{
			loadModHeader("Lang//" + var, translationStr);
			tmp.emplace(var, translationStr);
		}
		return tmp;
	}

	void Manager::saveLanguages(const Language::LanguageRequestor& languageRequestor)
	{
		for(auto& x : languageRequestor.languages)
			saveLanguageFile(x.first, (Language::TranslationString&)x.second);
	}

	void Manager::saveLanguageFile(const Core::String & filename, Language::TranslationString & langHeader)
	{
		Core::String idx = filename;
		std::ofstream file(Core::langPath + filename, std::ios::binary);
		idx.append(".index");
		auto& logger = Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("Manager");
		logger.Debug("Saving file: " + filename);
		std::ofstream index(Core::langPath + idx, std::ios::binary);
		{
			File::Archive::DatabaseIndex ind;
			cereal::BinaryOutputArchive mainAr(file);
			cereal::BinaryOutputArchive indexAr(index);
			ind.flags = Enums::ObjectFlag::NoFlag;
			ind.ID = Core::uuid::nil();
			ind.type = Enums::ObjectType::Header;
			ind.modFile = "notUsed";
			ind.row = file.tellp();
			indexAr(ind);
			mainAr(langHeader);
			langHeader.stringList.save(ind, file, indexAr, mainAr);

			ind.ID = Core::uuid::nil();
			ind.type = Enums::ObjectType::EoF;
			ind.row = file.tellp();
			ind.flags = Enums::ObjectFlag::EoF;
			indexAr(ind);
		}
	}

#pragma warning(disable: 6262)
	bool Manager::loadModOrderFile()
	{
		auto& logger = Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("File::Asset::Manager");
		std::ifstream file("Data\\ModLoadOrder.xml");
		if (file.is_open())
		{
			cereal::XMLInputArchive ar(file);
			ar(modLoader);
			return true;
		}
		logger.Critical("Unable to load mod load order file [ModLoadOrder.xml]", logger.fileInfo(__FILE__, __LINE__));
		return false;
	}
#pragma warning(default: 6262)

}