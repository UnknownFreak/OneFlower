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
	ModLoader modLoader;

public:

	AssetManager();

	Requestor<Prefab>& getPrefabRequester();
	Requestor<IModel*>& getModelRequester();
	Requestor<DBZone>& getDBZoneRequester();

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