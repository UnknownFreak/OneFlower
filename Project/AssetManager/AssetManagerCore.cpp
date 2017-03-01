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

CEREAL_REGISTER_TYPE(BaseComponent);

//CEREAL_REGISTER_TYPE(IBaseComponent<Component::DialogComponent>)
CEREAL_REGISTER_TYPE(Component::HitboxComponent)
//CEREAL_REGISTER_TYPE(IBaseComponent<Component::OverheadComponent>)
//CEREAL_REGISTER_TYPE(IBaseComponent<Component::PlayerComponent> )
CEREAL_REGISTER_TYPE(Component::RenderComponent )
//CEREAL_REGISTER_TYPE(IBaseComponent<Component::RigidComponent> )
//CEREAL_REGISTER_TYPE(IBaseComponent<Component::Timer>)
CEREAL_REGISTER_TYPE(Component::TransformComponent)

//CEREAL_REGISTER_TYPE_WITH_NAME(Component::DialogComponent, "Dialog")
//CEREAL_REGISTER_TYPE_WITH_NAME(Component::HitboxComponent, "Hitbox")
//CEREAL_REGISTER_TYPE_WITH_NAME(Component::OverheadComponent, "Overhead")
//CEREAL_REGISTER_TYPE_WITH_NAME(Component::PlayerComponent, "Player")
//CEREAL_REGISTER_TYPE_WITH_NAME(Component::RenderComponent, "Render")
//CEREAL_REGISTER_TYPE_WITH_NAME(Component::RigidComponent, "Rigid")
//CEREAL_REGISTER_TYPE_WITH_NAME(Component::Timer, "Timer")
//CEREAL_REGISTER_TYPE_WITH_NAME(Component::TransformComponent, "Transform")

//CEREAL_REGISTER_POLYMORPHIC_RELATION(BaseComponent, Component::DialogComponent)
CEREAL_REGISTER_POLYMORPHIC_RELATION(BaseComponent, Component::HitboxComponent)
//CEREAL_REGISTER_POLYMORPHIC_RELATION(BaseComponent, Component::OverheadComponent)
//CEREAL_REGISTER_POLYMORPHIC_RELATION(BaseComponent, Component::PlayerComponent)
CEREAL_REGISTER_POLYMORPHIC_RELATION(BaseComponent, Component::RenderComponent)
//CEREAL_REGISTER_POLYMORPHIC_RELATION(BaseComponent, Component::RigidComponent)
//CEREAL_REGISTER_POLYMORPHIC_RELATION(BaseComponent, Component::Timer)
CEREAL_REGISTER_POLYMORPHIC_RELATION(BaseComponent, Component::TransformComponent)

AssetManagerCore::AssetMode AssetManagerCore::assetMode = AssetManagerCore::AssetMode::FINE;
AssetManagerCore::Mode AssetManagerCore::state = AssetManagerCore::Mode::UNDEFINED;
Core::String AssetManagerCore::openedMod = "<Not Set>";

AssetManagerCore::Mode AssetManagerCore::getMode()
{
	return state;
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

void AssetManagerCore::saveModOrderFile(ModLoader & mod)
{
	std::ofstream file("Data\\ModLoadOrder.xml");
	{
		cereal::XMLOutputArchive ar(file);
		ar(mod);
	}
}

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



#ifdef _DEBUG

void testSave()
{
	GameObject *test = new GameObject();
	test->tag = "debug";
	test->name = "TestPlatform";
	test->GetComponent<Component::TransformComponent>()->position.x = 300;
	test->GetComponent<Component::TransformComponent>()->position.y = 316;
	test->AddComponent(new Component::HitboxComponent(0, 0, 40, 40));
	test->AddComponent(new Component::RenderComponent("testCutHalf.png"));
	Prefab pref(test);
	pref.ID = 1;
	//zone.addGameObject(test);

	GameObject *ground = new GameObject();
	ground->name = "da kewl ground";
	ground->tag = "debug";
	ground->GetComponent<Component::TransformComponent>()->position.x = 400;
	ground->GetComponent<Component::TransformComponent>()->position.y = 550;
	ground->AddComponent(new Component::HitboxComponent(0, 0, 40, 40));
	ground->AddComponent(new Component::RenderComponent("ground.marker_1.png"));
	ground->GetComponent<Component::RenderComponent>()->sprite.setScale(2, 1);
	ground->GetComponent<Component::HitboxComponent>()->bounding.size.x = ground->GetComponent<Component::HitboxComponent>()->bounding.size.x * 2;
	Prefab pref2(ground);
	pref2.ID = 2;

	//zone.addGameObject(ground);

	GameObject *target = new GameObject();
	target->name = "testTarget";
	target->tag = "debug";
	target->GetComponent<Component::TransformComponent>()->position.x = 580;
	target->GetComponent<Component::TransformComponent>()->position.y = 480;
	target->AddComponent(new Component::HitboxComponent(0, 0, 40, 40));
	target->AddComponent(new Component::RenderComponent("testTarget.png"));

	//target->AddComponent(new Component::DialogComponent(2));
	////target->GetComponent<DialogComponent>()->msg->iconName = "TestDialogChat.png";
	//target->GetComponent<Component::DialogComponent>()->dialogMessage = "Senpai!\nNotice me!";
	//target->GetComponent<Component::DialogComponent>()->position.x = 64;
	//target->GetComponent<Component::DialogComponent>()->position.y = 80;
	//target->GetComponent<DialogComponent>()->msg->setOffset(10, 5);

	Prefab pref3(target);
	pref3.ID = 3;


	std::ofstream index("TestSave.xml.index", std::ios::binary);
	std::ofstream file("TestSave.xml", std::ios::binary);
	{
		DatabaseIndex ind;
		cereal::BinaryOutputArchive mainAr(file);
		cereal::BinaryOutputArchive indexAr(index);
		//ind.flags = "-";
		//ind.ID = zone.ID;
		//ind.type = "Zone";
		//ind.row = file.tellp();
		//indexAr(ind);
		//mainAr(zone);

		ind.ID = pref.ID;
		ind.type = "Prefab";
		ind.row = file.tellp();
		indexAr(ind);
		mainAr(pref);

		ind.ID = pref2.ID;
		ind.type = "Prefab";
		ind.row = file.tellp();
		indexAr(ind);
		mainAr(pref2);

		ind.ID = pref3.ID;
		ind.type = "Prefab";
		ind.row = file.tellp();
		indexAr(ind);
		mainAr(pref3);

		ind.ID = 0xffffffff;
		ind.type = "";
		ind.row = file.tellp();
		ind.flags = "EoF";
		indexAr(ind);
	}
	delete test;
	test = 0;
	delete target;
	target = 0;
	delete ground;
	ground = 0;
}

void testLoad()
{
	Prefab a;
	Prefab b;
	Prefab c;
	std::ifstream index("TestSave.xml.index", std::ios::binary);
	std::ifstream file("TestSave.xml", std::ios::binary);
	{
		DatabaseIndex ind;
		cereal::BinaryInputArchive mainAr(file);
		cereal::BinaryInputArchive indexAr(index);
		mainAr(a);
		mainAr(b);
		mainAr(c);
	}
}
#endif