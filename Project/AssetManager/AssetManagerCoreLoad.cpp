#include "AssetManagerCore.hpp"

#include <Core\Core.hpp>
#include "Prefab\Prefab.hpp"
#include "Database\DatabaseIndex.hpp"
#include <iostream>
#include <fstream>

#include <cereal\archives\binary.hpp>
#include <cereal\archives\xml.hpp>
#include <cereal\types\string.hpp>
#include <cereal\types\polymorphic.hpp>
#include <cereal\types\map.hpp>
#include <cereal\types\memory.hpp>
#include <cereal\access.hpp>

#include <Core\Component\TransformComponent.hpp>
#include <Graphic\Component\RenderComponent.h>
#include <Physics\Component\HitboxComponent.hpp>

#include <World\WorldCore.hpp>
#include <World\Zone.hpp>

#include <Animations\TextureMap.hpp>
#include <Animations\SpriterEntityInstance.hpp>
#include <Animations\SpriterModelContainer.hpp>
#include <Animations\SpriteSheetAnimation.hpp>
#include <Animations\SpriterTextureMapper.hpp>

#include <EditorManager\EditorCore.hpp>

bool AssetManagerCore::loadZoneFromSaveFile(Core::String saveFile, Zone& zoneToLoad, size_t zoneID)
{
	saveFile.append(".avfile");
	GameObject trash;
	std::ifstream file(saveFile.c_str(), std::ios::binary);
	{
		if (file.is_open())
		{
			cereal::BinaryInputArchive ar(file);
			ar(trash);
			size_t iter;
			ar(iter);
			for (size_t i = 0; i < iter; i++)
			{
				size_t _zoneToLoad;
				ar(_zoneToLoad);
				if (_zoneToLoad == zoneID)
				{
					ar(zoneToLoad);
					return true;
				}
				else
				{
					Zone trashZone;
					ar(trashZone);
				}
			}
		}
	}
	return false;
}

void AssetManagerCore::loadZoneFromDB(DBZone & zoneToLoad, size_t zoneID)
{
	for each (std::pair<Core::String, size_t> var in Engine::World.modLoadOrder.loadOrder)
	{
		bool eof = false;
		DatabaseIndex ind;
		std::ifstream index("Data\\" + var.first + ".index", std::ios::binary);
		std::ifstream database("Data\\" + var.first, std::ios::binary);
		if (index.is_open())
		{
			cereal::BinaryInputArchive ar(index);
			{
				while (!eof)
				{
					ar(ind);
					if (ind.type == "Zone")
					{
						database.seekg(ind.row);
						cereal::BinaryInputArchive zoneLoad(database);
						zoneLoad(zoneToLoad);
						if (zoneToLoad.ID == zoneID)
							eof = true;
					}
					else if (ind.flags == "EoF")
						eof = true;
				}
			}
		}
	}
}

void AssetManagerCore::loadAllEditorVariables()
{
	LoadAllTextureMaps(Engine::ModelContainer);
	LoadAllPrefabs(Editor::addons.myActualManager.editorPrefabContainer);
	LoadAllZones(Editor::addons.myActualManager.EditorAllZones);
}

bool AssetManagerCore::loadModHeader(Core::String modName, ModHeader & myheader)
{
	bool eof = false;
	DatabaseIndex ind;
	std::ifstream index(modName + ".index", std::ios::binary);
	std::ifstream database(modName, std::ios::binary);
	if (index.is_open())
	{
		cereal::BinaryInputArchive ar(index);
		{
			while (!eof)
			{
				ar(ind);
				if (ind.type == "Header")
				{
					database.seekg(ind.row);
					cereal::BinaryInputArchive headerLoad(database);
					headerLoad(myheader);
					index.close();
					database.close();
					return true;
				}
				else if (ind.flags == "EoF")
					eof = true;
			}
		}
	}
	return false;
}
bool AssetManagerCore::loadModOrderFile(ModLoader& mod)
{
	std::ifstream file("Data\\ModLoadOrder.xml");
	if (file.is_open())
	{
		cereal::XMLInputArchive ar(file);
		ar(mod);
		return true;
	}
	return false;
}

void AssetManagerCore::LoadAllZones(std::map<std::pair<std::string, size_t>, DBZone>& worldmap)
{
	for each (std::pair<std::string, size_t> var in Engine::World.modLoadOrder.loadOrder)
	{
		bool eof = false;
		DatabaseIndex ind;
		std::ifstream index(var.first + ".index", std::ios::binary);
		std::ifstream database(var.first, std::ios::binary);
		if (index.is_open())
		{
			cereal::BinaryInputArchive ar(index);
			{
				while (!eof)
				{
					ar(ind);
					if (ind.type == "Zone")
					{
						std::map<std::pair<std::string, size_t>, DBZone>::iterator it = worldmap.find(std::pair<std::string, size_t>(ind.modFile, ind.ID));
						if (it != worldmap.end())
						{
							// stuff exist add extra things to zone.
							database.seekg(ind.row);
							cereal::BinaryInputArchive zoneLoad(database);
							zoneLoad(it->second);
						}
						else
						{
							database.seekg(ind.row);
							DBZone tmp;
							cereal::BinaryInputArchive zoneLoad(database);
							zoneLoad(tmp);
							worldmap.insert(std::pair<std::pair<std::string, size_t>, DBZone>(std::pair<std::string, size_t>(ind.modFile, ind.ID), tmp));
						}
					}
					else if (ind.flags == "EoF")
						eof = true;
				}
			}
		}
	}
}
void AssetManagerCore::LoadAllPrefabs(PrefabContainer& pre)
{
	for each (std::pair<std::string, size_t> var in Engine::World.modLoadOrder.loadOrder)
	{
		bool eof = false;
		DatabaseIndex ind;
		std::ifstream index(var.first + ".index", std::ios::binary);
		std::ifstream database(var.first, std::ios::binary);
		if (index.is_open())
		{
			cereal::BinaryInputArchive ar(index);
			{
				while (!eof)
				{
					ar(ind);
					if (ind.type == "Prefab")
					{
						std::map<std::pair<std::string, size_t>, Prefab>::iterator it = pre.find(ind.modFile, ind.ID);
						if (it != pre.end())
						{
							// stuff exist add extra things to prefab.
						}
						else
						{
							database.seekg(ind.row);
							Prefab tmp;
							cereal::BinaryInputArchive prefabLoad(database);
							prefabLoad(tmp);
							pre.addPrefab(tmp);
						}
					}
					else if (ind.flags == "EoF")
						eof = true;
				}
			}
		}
	}
}
//void LoadAllItems(std::map<std::pair<std::string, size_t>, Items::Item*>& item)
//{
//	for each (std::pair<std::string, size_t> var in Engine::World.modLoadOrder.loadOrder)
//	{
//		bool eof = false;
//		DatabaseIndex ind;
//		std::ifstream index(var.first + ".index", std::ios::binary);
//		std::ifstream database(var.first, std::ios::binary);
//		if (index.is_open())
//		{
//			cereal::BinaryInputArchive ar(index);
//			{
//				while (!eof)
//				{
//					ar(ind);
//					if (ind.type == "Item")
//					{
//						std::map<std::pair<std::string, size_t>, Items::Item*>::iterator it = item.find(std::pair<std::string, size_t>(ind.modFile, ind.ID));
//						if (it != item.end())
//						{
//							// stuff exist add extra things to item
//							// or override
//							// or ignore
//						}
//						else
//						{
//							database.seekg(ind.row);
//							Items::Item* tmp = NULL;
//							cereal::BinaryInputArchive itemLoad(database);
//							loadItem(itemLoad, tmp);
//							item.insert(std::pair<std::pair<std::string, size_t>, Items::Item*>(std::pair<std::string, size_t>(ind.modFile, ind.ID), tmp));
//						}
//					}
//					else if (ind.flags == "EoF")
//						eof = true;
//				}
//			}
//		}
//	}
//}
//void LoadAllQuests(std::map<std::pair<std::string, unsigned int>, Quests::Quest>& quests)
//{
//	for each (std::pair<std::string, size_t> var in Engine::World.modLoadOrder.loadOrder)
//	{
//		bool eof = false;
//		DatabaseIndex ind;
//		std::ifstream index(var.first + ".index", std::ios::binary);
//		std::ifstream database(var.first, std::ios::binary);
//		if (index.is_open())
//		{
//			cereal::BinaryInputArchive ar(index);
//			{
//				while (!eof)
//				{
//					ar(ind);
//					if (ind.type == "Quest")
//					{
//						std::map<std::pair<std::string, unsigned int>, Quests::Quest>::iterator it = quests.find(std::pair<std::string, size_t>(ind.modFile, ind.ID));
//						if (it != quests.end())
//						{
//							// stuff exist add extra things to item
//							// or override
//							// or ignore
//						}
//						else
//						{
//							database.seekg(ind.row);
//							Quests::Quest tmp;
//							cereal::BinaryInputArchive questLoad(database);
//							questLoad(tmp);
//							quests.insert(std::pair<std::pair<std::string, unsigned int>, Quests::Quest>(std::pair<std::string, size_t>(ind.modFile, ind.ID), tmp));
//						}
//					}
//					else if (ind.flags == "EoF")
//						eof = true;
//				}
//			}
//		}
//	}
//}
void AssetManagerCore::LoadAllTextureMaps(SpriterModelContainer & container)
{
	for each (std::pair<std::string, size_t> var in Engine::World.modLoadOrder.loadOrder)
	{
		bool eof = false;
		DatabaseIndex ind;
		std::ifstream index(var.first + ".index", std::ios::binary);
		std::ifstream database(var.first, std::ios::binary);
		if (index.is_open())
		{
			cereal::BinaryInputArchive ar(index);
			{
				while (!eof)
				{
					ar(ind);
					if (ind.type == "ModelContainer")
					{
						database.seekg(ind.row);
						std::cout << "loading textureMaps" << std::endl;
						cereal::BinaryInputArchive ModelLoad(database);
						ModelLoad(container);
					}
					else if (ind.flags == "EoF")
						eof = true;
				}
			}
		}
	}
}