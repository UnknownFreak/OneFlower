#ifndef AssetManagerCore_HPP
#define AssetManagerCore_HPP

#include <cereal\archives\binary.hpp>
#include <cereal\archives\xml.hpp>
#include <cereal\types\string.hpp>
#include <cereal\types\polymorphic.hpp>
#include <cereal\types\map.hpp>
#include <cereal\types\memory.hpp>
#include <cereal\access.hpp>

#include <Core\String.hpp>
#include <Core\EngineModule\EngineModuleManager.hpp>
#include <Core\EngineModule\IEngineModule.hpp>

#include <Model\TextureMap.hpp>
#include <Model\IModel.hpp>

#include "LanguageRequestor.hpp"
#include "LanguageHeader.hpp"
#include "Language.hpp"

#include "Database/DatabaseObjects.hpp"

#include "Element.hpp"

#include "ModHeader.hpp"
#include "ModLoader.hpp"

#include "Prefab.hpp"

#include "Requestor.hpp"
#include "PrimitiveSaveable.hpp"

#include "TextureLoader.hpp"

#include "Version.hpp"

#ifdef _DEBUG
void testSave();
void testLoad();
#endif

namespace Asset
{
	class AssetManager : public IEngineResource<AssetManager>
	{

		Requestor<Asset::Prefab> prefabRequestor;
		Requestor<IModel*> modelRequestor;
		Requestor<Database::Zone> zoneRequestor;
		Requestor<TextureMap> textureMapRequestor;
		Requestor<PrimitiveSaveable<int>> intRequestor;
		Requestor<PrimitiveSaveable<double>> doubleRequestor;
		Requestor<PrimitiveSaveable<Core::String>> stringRequestor;
		Requestor<PrimitiveSaveable<std::vector<Core::String>>> stringVectorRequestor;
		Requestor<Element> elementRequestor;
		Requestor<Language::LanguageRequestor> lang;
		ModLoader modLoader;

	public:

		AssetManager();

		Requestor<Asset::Prefab>& getPrefabRequester();
		Requestor<IModel*>& getModelRequester();
		Requestor<Database::Zone>& getZoneRequester();
		Requestor<TextureMap>& getTextureMapRequester();
		Requestor<PrimitiveSaveable<int>>& getIntRequestor();
		Requestor<PrimitiveSaveable<double>>& getDoubleRequestor();
		Requestor<PrimitiveSaveable<Core::String>>& getStringRequestor();
		Requestor<PrimitiveSaveable<std::vector<Core::String>>>& getStringVectorRequestor();
		Requestor<Element>& getElementRequestor();

		Language::LanguageRequestor& getLanguage();

		//bool loadModHeader(Core::String modName, ModHeader& modHeader);

		bool loadModOrderFile();
		void saveModOrderFile();

		void saveGameDatabase(std::string filename, ModHeader& modhdr);

		void loadAllEditorVariables();


		std::map<Core::String, Language::TranslationString> loadLanguages(const std::vector<Core::String>& languageFiles);
		void saveLanguages(const Language::LanguageRequestor& languageRequestor);
		void saveLanguageFile(Core::String& filename, Language::TranslationString& langHeader);

		TextureLoader textureloader;
		Core::String openedMod;

		ModLoader& getModLoader();

		const ResourceType& getType()
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
				Engine::GetModule<OneLogger>().Critical("Unable to open mod index file [" + modName + ".index]", __FILE__, __LINE__);
			else if (!database.is_open())
				Engine::GetModule<OneLogger>().Critical("Unable to open database file [" + modName + "]", __FILE__, __LINE__);
			else
			{
				cereal::BinaryInputArchive ar(index);
				{
					while (!eof)
					{
						ar(ind);
						if (ind.type == DatabaseIndex::ObjectTypeEnum::Header)
						{
							database.seekg(ind.row);
							cereal::BinaryInputArchive headerLoad(database);
							headerLoad(myheader);
							index.close();
							database.close();
							return true;
						}
						else if (ind.flags == DatabaseIndex::ObjectFlag::EoF)
							eof = true;
					}
				}
			}
			Engine::GetModule<OneLogger>().Critical("Unable to load mod header for mod [" + modName + "]", __FILE__, __LINE__);
			return false;
		}
	};
}

#endif