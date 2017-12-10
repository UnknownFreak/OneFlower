#ifndef AssetManagerCore_HPP
#define AssetManagerCore_HPP
#include "TextureLoader.hpp"
#include "Mod\ModHeader.hpp"
#include "Mod\ModLoader.hpp"
#include <Core/String.hpp>

//#include "Prefab\PrefabContainer.hpp"
#include "Prefab\Prefab.hpp"

#include <Model\AnimationCore.hpp>
#include "Database\DBZone.hpp"

#include "Requestor\Requestor.hpp"

#include <cereal\archives\binary.hpp>
#include "Version\Version.hpp"

#include <Model\IModel.hpp>

#include <Core\IEngineResource\IEngineResource.hpp>

class Zone;
class DBZone;
//class AssetManagerCore
//{
//	
//public:
//	
//	static OneVersion assetManagerVersion;
//
//	friend class Zone;
//	enum class Mode
//	{
//		SAVING,
//		LOADING,
//		UNDEFINED
//	};
//
//	enum class AssetMode
//	{
//		FINE,
//		INVALIDVERSION
//	};
//
//	static Core::String openedMod;
//
//private:
//	
//	static AssetMode assetMode;
//	static Mode state;
//	//
//	//ComponentLoader
//	//ZoneLoader
//	// in extended assetmanager? as they belong to game and the other two belong to engine
//	//ItemLoader
//	//QuestLoader
//	//
//
//
//public:
//
//	static Mode getMode();
//
//	static bool loadModHeader(Core::String modName, ModHeader& myheader);
//
//	static bool loadModOrderFile(ModLoader & mod);
//	static void saveModOrderFile(ModLoader & mod);
//
//	static bool loadZoneFromSaveFile(Core::String saveFile, Zone& zoneToLoad, size_t zoneID);
//	static void loadZoneFromDB(DBZone& zoneToLoad, size_t zoneID);
//
//	static void saveGameDatabase(
//		std::string filename,
//		ModHeader& modhdr,
//		PrefabContainer& prefabs,
//		std::map<std::pair<std::string, size_t>, DBZone>& EditorAllZones);
//
//
//	static void savePrefabs(DatabaseIndex & ind, 
//		PrefabContainer& prefabs,
//		std::ostream& file, 
//		std::ostream& index, 
//		cereal::BinaryOutputArchive& indexAr, 
//		cereal::BinaryOutputArchive& mainAr);
//
//	static void saveZones(DatabaseIndex & ind,
//		std::map<std::pair<std::string, size_t>, DBZone>& allzones,
//		std::ostream& file,
//		std::ostream& index,
//		cereal::BinaryOutputArchive& indexAr,
//		cereal::BinaryOutputArchive& mainAr);
//
//	static void saveSpriteSheetMaps(DatabaseIndex& ind,
//		std::map < std::pair<std::string, size_t>, SpriteSheetMapRef>& allspriteSheetMaps,
//		std::ostream& file,
//		std::ostream& index,
//		cereal::BinaryOutputArchive& indexAr,
//		cereal::BinaryOutputArchive& mainAr);
//
//	static void loadAllEditorVariables();
//
//	static void LoadAllZones(std::map<std::pair<std::string, unsigned int>, DBZone>& nameOfAllZones);
//	static void LoadAllPrefabs(PrefabContainer& editorPrefabContainer);
//	static void LoadAllTextureMaps(SpriterModelContainer& container);
//	static void LoadAllSpriteSheetMaps();
//
//};
#ifdef _DEBUG
void testSave();
void testLoad();
#endif



class AssetManager : public IEngineResource<AssetManager>
{

public:
	AssetManager();


	Requester<Prefab>& getPrefabRequester();
	Requester<IModel*>& getModelRequester();
	Requester<DBZone>& getDBZoneRequester();


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

private:

	Requester<Prefab> prefabRequestor;
	Requester<IModel*> modelRequestor;
	Requester<DBZone> dbZoneRequestor;
	ModLoader modLoader;

};

#endif