#ifndef AssetManagerCore_HPP
#define AssetManagerCore_HPP
#include "TextureLoader.hpp"
#include "Mod\ModHeader.hpp"
#include "Mod\ModLoader.hpp"
#include <Core/String.hpp>

#include "Prefab\PrefabContainer.hpp"
#include <Model\AnimationCore.hpp>
#include "ObjectSaveMode.hpp"
#include "Database\DatabaseIndex.hpp"
#include "Database\DBZone.hpp"

#include "SpriteSheetMap\SpriteSheetMapRef.hpp"

#include "Requestor\Requestor.hpp"

#include <cereal\archives\binary.hpp>
#include "Version\Version.hpp"

#include <Model\IModel.hpp>
#include <Model\StaticModel.hpp>


namespace Engine {
	extern TextureLoader Textureloader;
	extern Requester<SpriteSheetMap> SpriteSheetMapRequester;
	extern Requester<Prefab> PrefabRequester;
	extern Requester<IModel*> ModelRequester;
	//extern Requester<Quest> QuestRequester;
}
class Zone;
class DBZone;
class AssetManagerCore
{
	
public:
	
	static OneVersion assetManagerVersion;

	friend class Zone;
	enum class Mode
	{
		SAVING,
		LOADING,
		UNDEFINED
	};

	enum class AssetMode
	{
		FINE,
		INVALIDVERSION
	};

	static Core::String openedMod;

private:
	
	static AssetMode assetMode;
	static Mode state;
	//
	//ComponentLoader
	//ZoneLoader
	// in extended assetmanager? as they belong to game and the other two belong to engine
	//ItemLoader
	//QuestLoader
	//


public:

	static Mode getMode();

	static bool loadModHeader(Core::String modName, ModHeader& myheader);

	static bool loadModOrderFile(ModLoader & mod);
	static void saveModOrderFile(ModLoader & mod);

	static bool loadZoneFromSaveFile(Core::String saveFile, Zone& zoneToLoad, size_t zoneID);
	static void loadZoneFromDB(DBZone& zoneToLoad, size_t zoneID);

	static void saveGameDatabase(
		std::string filename,
		ModHeader& modhdr,
		PrefabContainer& prefabs,
		std::map<std::pair<std::string, size_t>, DBZone>& EditorAllZones);


	static void savePrefabs(DatabaseIndex & ind, 
		PrefabContainer& prefabs,
		std::ostream& file, 
		std::ostream& index, 
		cereal::BinaryOutputArchive& indexAr, 
		cereal::BinaryOutputArchive& mainAr);

	static void saveZones(DatabaseIndex & ind,
		std::map<std::pair<std::string, size_t>, DBZone>& allzones,
		std::ostream& file,
		std::ostream& index,
		cereal::BinaryOutputArchive& indexAr,
		cereal::BinaryOutputArchive& mainAr);

	static void saveSpriteSheetMaps(DatabaseIndex& ind,
		std::map < std::pair<std::string, size_t>, SpriteSheetMapRef>& allspriteSheetMaps,
		std::ostream& file,
		std::ostream& index,
		cereal::BinaryOutputArchive& indexAr,
		cereal::BinaryOutputArchive& mainAr);

	static void loadAllEditorVariables();

	static void LoadAllZones(std::map<std::pair<std::string, unsigned int>, DBZone>& nameOfAllZones);
	static void LoadAllPrefabs(PrefabContainer& editorPrefabContainer);
	static void LoadAllTextureMaps(SpriterModelContainer& container);
	static void LoadAllSpriteSheetMaps();

	//
	//const ComponentLoader& getComponentLoader()
	//const ItemLoader& getItemLoader()
	//const QuestLoader& getQuestLoader()
	//const ZoneLoader() getZoneLoader()
	//
	static void testRequestor();
	
};
#ifdef _DEBUG
void testSave();
void testLoad();
#endif

#endif

