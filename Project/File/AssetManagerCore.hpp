#ifndef AssetManagerCore_HPP
#define AssetManagerCore_HPP

#include "Resource/RegisterRTTI.hpp"

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

#include <Graphics\Model\TextureMap.hpp>
#include <Graphics\Model\IModel.hpp>
//

#include <File/Resource/TileAtlas.hpp>

#include <Language/LanguageRequestor.hpp>
#include <Language/LanguageHeader.hpp>
#include <Language/TranslationString.hpp>
//
//#include "Database/DatabaseObjects.hpp"
//
#include <Combat/Element.hpp>
//
#include "ModHeader.hpp"
#include "ModLoader.hpp"

//#include "Prefab.hpp"

#include <File/Resource/Requestor.hpp>
#include <File/Resource/RequestorV2.hpp>

#include <File/Resource/DialogTree.hpp>
#include <File/Template/WorldInstance.hpp>
#include <File/Template/ColliderTemplate.hpp>
#include <File/Template/TileTemplate.hpp>

#include <Helpers/PrimitiveSaveable.hpp>
//
#include <Helpers/Version.hpp>

#ifdef _DEBUG
void testSave();
void testLoad();
#endif

namespace Asset
{
	class AssetManager : public Interfaces::IEngineResource<AssetManager>
	{

		Requestor<Language::LanguageRequestor> lang;

		ModLoader& modLoader;

	public:
		RequestorV2 requestor;
		
		AssetManager();

		Language::LanguageRequestor& getLanguage();

		//bool loadModHeader(Core::String modName, ModHeader& modHeader);

		bool loadModOrderFile();
		void saveModOrderFile();

		void saveGameDatabase(std::string filename, ModHeader& modhdr);

		void loadAllEditorVariables();


		std::map<Core::String, Language::TranslationString> loadLanguages(const std::vector<Core::String>& languageFiles);
		void saveLanguages(const Language::LanguageRequestor& languageRequestor);
		void saveLanguageFile(Core::String& filename, Language::TranslationString& langHeader);

		Core::String openedMod;

		ModLoader& getModLoader();

		Enums::EngineResourceType& getType() const
		{
			return type;
		}

		template< typename T>
		bool loadModHeader(Core::String modName, T & myheader)
		{
			bool eof = false;
			DatabaseIndex ind;
			std::ifstream index("Data//" + modName + ".index", std::ios::binary);
			std::ifstream database("Data//" + modName, std::ios::binary);

			if (!index.is_open())
				Engine::GetModule<EngineModule::Logger::OneLogger>().Critical("Unable to open mod index file [" + modName + ".index]", __FILE__, __LINE__);
			else if (!database.is_open())
				Engine::GetModule<EngineModule::Logger::OneLogger>().Critical("Unable to open database file [" + modName + "]", __FILE__, __LINE__);
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
			Engine::GetModule<EngineModule::Logger::OneLogger>().Critical("Unable to load mod header for mod [" + modName + "]", __FILE__, __LINE__);
			return false;
		}
	};
}

#endif