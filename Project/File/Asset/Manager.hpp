#ifndef AssetManager_HPP
#define AssetManager_HPP

#include <File/Archive/RegisterRTTI.hpp>

#pragma warning(push)
#pragma warning(disable: 4003)
#include <cereal\archives\binary.hpp>
#include <cereal\archives\xml.hpp>
#include <cereal\types\string.hpp>
#include <cereal\types\polymorphic.hpp>
#include <cereal\types\map.hpp>
#include <cereal\types\memory.hpp>
#include <cereal\access.hpp>
#pragma warning(pop)


#include <Helpers\String.hpp>

#include <Module/EngineModuleManager.hpp>
#include <Interfaces/IEngineModule.hpp>

#include <Language/LanguageRequestor.hpp>
#include <Language/TranslationString.hpp>

#include <Combat/Element.hpp>

#include <File/Mod/ModHeader.hpp>
#include <File/Mod/ModLoader.hpp>

#include <File/Archive/RequestorV2.hpp>

#include <File/Asset/Resource/DialogTree.hpp>
#include <File/Asset/Resource/Template/WorldInstance.hpp>
#include <File/Asset/Resource/Template/ColliderTemplate.hpp>
#include <File/Asset/Resource/Template/TileTemplate.hpp>

#include <Helpers/PrimitiveSaveable.hpp>
#include <Helpers/Version.hpp>

namespace File::Asset
{
	class Manager : public Interfaces::IEngineResource<Manager>
	{

		File::Archive::RequestorV2 lang;

		File::Mod::Loader& modLoader;

	public:
		File::Archive::RequestorV2 requestor;
		
		Manager();

		Language::LanguageRequestor& getLanguage();

		//bool loadModHeader(Core::String modName, Header& modHeader);

		bool loadModOrderFile();
		void saveModOrderFile();

		void saveGameDatabase(std::string filename, File::Mod::Header& modhdr);

		void loadAllEditorVariables();


		std::map<Core::String, Language::TranslationString> loadLanguages(const std::vector<Core::String>& languageFiles);
		void saveLanguages(const Language::LanguageRequestor& languageRequestor);
		void saveLanguageFile(const Core::String& filename, Language::TranslationString& langHeader);

		Core::String openedMod;

		File::Mod::Loader& getModLoader();

		Enums::EngineResourceType& getType() const
		{
			return type;
		}

		template< typename T>
		bool loadModHeader(Core::String modName, T & myheader)
		{
			bool eof = false;
			File::Archive::DatabaseIndex ind;
			std::ifstream index("Data//" + modName + ".index", std::ios::binary);
			std::ifstream database("Data//" + modName, std::ios::binary);
			auto& logger = Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("File::Asset::Manager");
			if (!index.is_open())
				logger.Critical("Unable to open mod index file [" + modName + ".index]", logger.fileInfo(__FILE__, __LINE__));
			else if (!database.is_open())
				logger.Critical("Unable to open database file [" + modName + "]", logger.fileInfo(__FILE__, __LINE__));
			else
			{
				cereal::BinaryInputArchive ar(index);
				{
					while (!eof)
					{
						ar(ind);
						if (ind.type == Enums::ObjectType::Header)
						{
							database.seekg(ind.row);
							cereal::BinaryInputArchive headerLoad(database);
							headerLoad(myheader);
							index.close();
							database.close();
							return true;
						}
						else if (ind.flags == Enums::ObjectFlag::EoF)
							eof = true;
					}
				}
			}
			logger.Critical("Unable to load mod header for mod [" + modName + "]", logger.fileInfo(__FILE__, __LINE__));
			return false;
		}
	};
}

#endif