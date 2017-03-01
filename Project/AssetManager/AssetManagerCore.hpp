#ifndef AssetManagerCore_HPP
#define AssetManagerCore_HPP
#include "TextureLoader.hpp"
#include "Mod\ModHeader.hpp"
#include "Mod\ModLoader.hpp"
#include <Core/String.hpp>
class Zone;
class DBZone;
class AssetManagerCore
{
	
public:
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


	//
	//const ComponentLoader& getComponentLoader()
	//const ItemLoader& getItemLoader()
	//const QuestLoader& getQuestLoader()
	//const ZoneLoader() getZoneLoader()
	//

};
#ifdef _DEBUG
void testSave();
void testLoad();
#endif
namespace Engine {
	extern TextureLoader Textureloader;
}

#endif