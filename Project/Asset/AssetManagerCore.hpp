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

		bool loadModHeader(Core::String modName, ModHeader& modHeader);

		bool loadModOrderFile();
		void saveModOrderFile();

		void saveGameDatabase(std::string filename, ModHeader& modhdr);

		void loadAllEditorVariables();

		TextureLoader textureloader;
		Core::String openedMod;

		ModLoader& getModLoader();

		const ResourceType& getType()
		{
			return type;
		}

	};
}

#endif