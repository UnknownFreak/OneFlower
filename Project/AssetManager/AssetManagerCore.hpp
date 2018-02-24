#ifndef AssetManagerCore_HPP
#define AssetManagerCore_HPP

#include <cereal\archives\binary.hpp>

#include <Core\String.hpp>
#include <Core\IEngineResource\EngineResourceManager.hpp>
#include <Core\IEngineResource\IEngineResource.hpp>

#include <Model\AnimationCore.hpp>
#include <Model\IModel.hpp>

#include "Database\DBZone.hpp"

#include "Mod\ModHeader.hpp"
#include "Mod\ModLoader.hpp"

#include "Prefab\Prefab.hpp"

#include "Requestor\Requestor.hpp"
#include "PrimitiveSaveable.hpp"

#include "TextureLoader.hpp"

#include "Version\Version.hpp"

class Zone;
class DBZone;

#ifdef _DEBUG
void testSave();
void testLoad();
#endif

class AssetManager : public IEngineResource<AssetManager>
{

	Requestor<Prefab> prefabRequestor;
	Requestor<IModel*> modelRequestor;
	Requestor<DBZone> dbZoneRequestor;
	Requestor<TextureMap> textureMapRequestor;
	Requestor<PrimitiveSaveable<int>> intRequestor;
	Requestor<PrimitiveSaveable<double>> doubleRequestor;
	Requestor<PrimitiveSaveable<Core::String>> stringRequestor;
	Requestor < PrimitiveSaveable<std::vector<Core::String>>> stringVectorRequestor;
	ModLoader modLoader;

public:

	AssetManager();

	Requestor<Prefab>& getPrefabRequester();
	Requestor<IModel*>& getModelRequester();
	Requestor<DBZone>& getDBZoneRequester();
	Requestor<TextureMap>& getTextureMapRequester();
	Requestor<PrimitiveSaveable<int>>& getIntRequestor();
	Requestor<PrimitiveSaveable<double>>& getDoubleRequestor();
	Requestor<PrimitiveSaveable<Core::String>>& getStringRequestor();
	Requestor<PrimitiveSaveable<std::vector<Core::String>>>& getStringVectorRequestor();

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

#endif