#include <fstream>

#include <cereal\archives\xml.hpp>
#include <cereal\types\string.hpp>
#include <cereal\types\polymorphic.hpp>
#include <cereal\types\map.hpp>
#include <cereal\types\memory.hpp>
#include <cereal\archives\binary.hpp>
#include <cereal\access.hpp>

#include <map>

#include "..\Component\BaseComponent.hpp"
#include "..\Component\DialogComponent.hpp"
#include "..\Component\HitboxComponent.hpp"
#include "..\Component\OverheadComponent.hpp"
#include "..\Component\TransformComponent.hpp"
#include "..\Component\RenderComponent.h"
#include "..\Component\GameObject.h"
#include "..\Component\RigidComponent.hpp"
#include "..\Component\ReputationComponent.hpp"
#include "..\Component\HealthComponent.hpp"
#include "..\Component\StatsComponent.hpp"

//need save
#include "..\Component\EquipmentComponent.hpp"
#include "..\Component\InventoryComponent.hpp"
#include "..\Component\PickupComponent.hpp"
#include "..\Component\ProjectilePatternComponent.hpp"

#include "..\Item\Armor.hpp"
#include "..\Item\Bag.hpp"
#include "..\Item\Item.hpp"
//

#include "LoadAndSave.hpp"

#include "../GUI/Text/Message.hpp"
#include "../GUI/Text\FloatingText.hpp"

#include "../World/ZoneMaker.hpp"
#include "../World/Zone.hpp"
#include "../World/ModLoader.hpp"

#include "../LoadAndSave/Prefab.hpp"
#include "../LoadAndSave/PrefabContainer.hpp"
#include "../LoadAndSave/DatabaseIndex.hpp"

#include "../../Engine.hpp"

std::string versionName = "Alpha Test: 1.3v";
CEREAL_REGISTER_ARCHIVE(RenderComponent)
void prefabSave(const GameObject* go)
{
	GameObject testPrefab("test");
	testPrefab.AddComponent(new IBaseComponent<RenderComponent>);
	testPrefab.GetComponent<RenderComponent>()->textureName = "prefabTest.png";
	std::ofstream file("test.prefab",std::ios::binary);
	{
		cereal::BinaryOutputArchive ar(file);
		ar(testPrefab);
	}
}
bool loadZoneFromSaveFile(std::string saveFile, Zone& zoneToLoad, size_t zoneID)
{
	saveFile.append(".avfile");
	GameObject trash;
	std::ifstream file(saveFile, std::ios::binary);
	{
		cereal::BinaryInputArchive ar(file);
		ar(trash);
		size_t iter;
		ar(iter);
		for (int i = 0; i < iter; i++)
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
	return false;
}
void saveGame(GameObject& player,std::string saveFile)
{
	saveFile.append(".avfile");
	std::ofstream file(saveFile, std::ios::binary);
	{
		cereal::BinaryOutputArchive ar(file);
		ar(player);
		ar(Engine::World.getCurrentZone()->ID);
		size_t size = Engine::World.worldmap.size();
		ar(size);
		for (std::map<size_t, Zone*>::iterator i = Engine::World.worldmap.begin(); i != Engine::World.worldmap.end(); i++)
		{
			ar(i->first);
			ar(*i->second);
		}
	}
}
void loadGame(GameObject& player,std::string loadFile)
{
	loadFile.append(".avfile");
	std::ifstream file(loadFile, std::ios::binary);
	{
		cereal::BinaryInputArchive ar(file);
		ar(player);
		size_t zoneID;
		ar(zoneID);
		Engine::World.loadZone(zoneID);

		size_t size = Engine::World.worldmap.size();
		ar(size);
		for (size_t i = 0; i < size; i++)
		{
			size_t id;
			Zone* zone = new Zone();
			ar(id);
			ar(*zone);
			Engine::World.worldmap.insert(std::pair<size_t, Zone*>(id, zone));
		}
	}
}

void saveGameDatabase(std::string filename, PrefabContainer& prefabs, std::map<unsigned int, DBZone>& EditorAllZones)
{
	std::ofstream file(filename, std::ios::binary);
	filename.append(".index");
	std::ofstream index(filename, std::ios::binary);
	{
		DatabaseIndex ind;
		cereal::BinaryOutputArchive mainAr(file);
		cereal::BinaryOutputArchive indexAr(index);
		for (std::map<size_t, DBZone>::iterator it = EditorAllZones.begin(); it != EditorAllZones.end(); it++)
		{
			ind.flags = "-";
			ind.ID = it->first;
			ind.type = "Zone";
			ind.row = file.tellp();
			indexAr(ind);
			mainAr(it->second);
			Engine::Window.debug.print("SavingZone - FilePos " + std::to_string(ind.row), __LINE__, __FILE__);
		}
		for (std::map<size_t,Prefab>::iterator it = prefabs.begin(); it != prefabs.end(); it++)
		{
			ind.flags = "-";
			ind.ID = it->first;
			ind.type = "Prefab";
			ind.row = file.tellp();
			indexAr(ind);
			mainAr(it->second);
			Engine::Window.debug.print("SavingPrefab - FilePos " + std::to_string(ind.row), __LINE__, __FILE__);
		}
		/*for (loop)
		{
			ind.flags = "-";
			ind.ID = it->first;
			ind.type = "Item";
			ind.row = file.tellp();
			indexAr(ind);
			mainAr(it->second);
			Engine::Window.debug.print("SavingItem - FilePos " + std::to_string(ind.row), __LINE__, __FILE__);
		}*/
		ind.ID = 0xffffffff;
		ind.type = "EoF";
		ind.row = file.tellp();
		ind.flags = "EoF";
		indexAr(ind);
		Engine::Window.debug.print("Saving EoF - FilePos " + std::to_string(ind.row), __LINE__, __FILE__);
	}
}

#ifdef _DEBUG
void testSave()
{
	/*
	Item item;
	item.ID = 1;
	item.iconName = "test.png";
	item.name = "testSaveItem";
	item.description = "<ItemTestSave>";
	item.price = 2;
	item.stackable = true;
	item.tag = Item::undefined;
	item.weight = 0.4;

	std::ofstream file("test.item");
	{
		cereal::XMLOutputArchive ar(file);
		ar(item.tag);
		ar(item);
	}
	//*/

	DBZone zone;
	zone.ID = 1;
	zone.name = "test";
	GameObject *test = new GameObject();
	test->tag = "debug";
	test->name = "TestPlatform";
	test->GetComponent<TransformComponent>()->position.x = 300;
	test->GetComponent<TransformComponent>()->position.y = 316;
	test->AddComponent(new HitboxComponent(0, 0, 40, 40));
	test->AddComponent(new RenderComponent("testCutHalf.png"));
	zone.prefabList.push_back(std::pair<size_t, Vector2>(1, Vector2(300, 316)));
	Prefab pref(test);
	pref.ID = 1;
	//zone.addGameObject(test);

	GameObject *ground = new GameObject();
	ground->name = "da kewl ground";
	ground->tag = "debug";
	ground->GetComponent<TransformComponent>()->position.x = 400;
	ground->GetComponent<TransformComponent>()->position.y = 550;
	ground->AddComponent(new HitboxComponent(0,0,40,40));
	ground->AddComponent(new RenderComponent("ground.marker_1.png"));
	ground->GetComponent<RenderComponent>()->sprite.setScale(2, 1);
	ground->GetComponent<HitboxComponent>()->bounding.size.x = ground->GetComponent<HitboxComponent>()->bounding.size.x * 2;
	Prefab pref2(ground);
	pref2.ID = 2;
	zone.prefabList.push_back(std::pair<size_t, Vector2>(2, Vector2(400, 550)));
	
	//zone.addGameObject(ground);

	GameObject *target = new GameObject();
	target->name = "testTarget";
	target->tag = "debug";
	target->GetComponent<TransformComponent>()->position.x = 580;
	target->GetComponent<TransformComponent>()->position.y = 480;
	target->AddComponent(new HitboxComponent(0, 0, 40, 40));
	target->AddComponent(new RenderComponent("testTarget.png"));

	target->AddComponent(new DialogComponent(2));
	target->GetComponent<DialogComponent>()->msg->iconName = "TestDialogChat.png";
	target->GetComponent<DialogComponent>()->dialogMessage = "Senpai!\nNotice me!";
	target->GetComponent<DialogComponent>()->position.x = 64;
	target->GetComponent<DialogComponent>()->position.y = 80;
	target->GetComponent<DialogComponent>()->msg->setOffset(10, 5);

	Prefab pref3(target);
	pref3.ID = 3;
	zone.prefabList.push_back(std::pair<size_t, Vector2>(3, Vector2(580, 480)));

	//zone.addGameObject(target);

	zone.background = Tile("testBackground_1.png", 400, 300);
	zone.background.size.x = 4000;
	zone.background.size.y = 800;
	zone.loadingScreen = Tile("black.png", Vector2(0, 0));
	zone.loadingScreenMessage = "This is a test";
	/*zone.foregrounds.push_back(Tile("blacktree_1.png", 250, 50));
	zone.foregrounds.push_back(Tile("blacktree_1.png", 450, 250));
	zone.foregrounds.push_back(Tile("blacktree_1.png", 400, 250));
	zone.foregrounds.push_back(Tile("blacktree_1.png", 350, 250));
	zone.foregrounds.push_back(Tile("blacktree_1.png", 550, 250));
	zone.foregrounds.push_back(Tile("blacktree_1.png", 500, 250));*/
	std::ofstream index("OneFlower.main.index", std::ios::binary);
	std::ofstream file("OneFlower.main", std::ios::binary);//
	{
		DatabaseIndex ind;
		cereal::BinaryOutputArchive mainAr(file);
		cereal::BinaryOutputArchive indexAr(index);
		ind.flags = "-";
		ind.ID = zone.ID;
		ind.type = "Zone";
		ind.row = file.tellp();
		indexAr(ind);
		mainAr(zone);
		Engine::Window.debug.print("SavingZone - FilePos " + std::to_string(ind.row), __LINE__, __FILE__);

		ind.ID = pref.ID;
		ind.type = "Prefab";
		ind.row = file.tellp();
		indexAr(ind);
		mainAr(pref);
		Engine::Window.debug.print("Saving Prefab - FilePos " + std::to_string(ind.row), __LINE__, __FILE__);


		ind.ID = pref2.ID;
		ind.type = "Prefab";
		ind.row = file.tellp();
		indexAr(ind);
		mainAr(pref2);
		Engine::Window.debug.print("Saving Prefab - FilePos " + std::to_string(ind.row), __LINE__, __FILE__);


		ind.ID = pref3.ID;
		ind.type = "Prefab";
		ind.row = file.tellp();
		indexAr(ind);
		mainAr(pref3);
		Engine::Window.debug.print("Saving Prefab - FilePos " + std::to_string(ind.row), __LINE__, __FILE__);


		ind.ID = 0xffffffff;
		ind.type = "";
		ind.row = file.tellp();
		ind.flags = "EoF";
		indexAr(ind);
		Engine::Window.debug.print("Saving EoF - FilePos " + std::to_string(ind.row), __LINE__, __FILE__);
	}
}

void testLoad()
{
	/*GameObject test;
	test.name = "SaveTestObjectNotLoaded";

	std::ifstream file("test.binary", std::ios::binary);
	{
	cereal::BinaryInputArchive ar(file);
	ar(test);
	}*/

	/*
	PrefabContainer con;
	std::ifstream file("prefabtest.prefabs",std::ios::binary);
	{
		cereal::BinaryInputArchive ar(file);
		ar(con);
	}
	//*/
}
#endif
//*
#pragma region GameObject
template<class Archive>
void save(Archive& archive,const GameObject& go)
{
	//if (go != NULL)
	{
		archive(versionName);
		archive(go.name);
		archive(go.componentMap.size());
		for(std::map<int,BaseComponent*>::const_iterator it = go.componentMap.begin(); it != go.componentMap.end(); ++it)
		{
			archive(it->first);
			//Make directives id instead and use switches
			if(it->first == IBaseComponent<RenderComponent>::typeID)
			{
				RenderComponent* rcp = (RenderComponent*)it->second;
				archive(*rcp);
			}
			else if(it->first == IBaseComponent<TransformComponent>::typeID)
			{
				TransformComponent* tcp = (TransformComponent*)it->second;
				archive(*tcp);
			}
			else if(it->first == IBaseComponent<HitboxComponent>::typeID)
			{
				HitboxComponent* hcp = (HitboxComponent*)it->second;
				archive(*hcp);
			}
			else if(it->first == IBaseComponent<DialogComponent>::typeID)
			{
				DialogComponent* dcp = (DialogComponent*)it->second;
				archive(*dcp);
			}
			else if(it->first == IBaseComponent<OverheadComponent>::typeID)
			{
				OverheadComponent* ohd = (OverheadComponent*)it->second;
				archive(*ohd);
			}
			else if(it->first == IBaseComponent<RigidComponent>::typeID)
			{
				RigidComponent* rig = (RigidComponent*)it->second;
				archive(*rig);
			}
			else if(it->first == IBaseComponent<ReputationComponent>::typeID)
			{
				ReputationComponent* rep = (ReputationComponent*)it->second;
				archive(*rep);
			}
			else if(it->first == IBaseComponent<HealthComponent>::typeID)
			{
				HealthComponent* rep = (HealthComponent*)it->second;
				archive(*rep);
			}
			else if(it->first == IBaseComponent<StatsComponent>::typeID)
			{
				StatsComponent* rep = (StatsComponent*)it->second;
				archive(*rep);
			}
		}
	}
}
template<class Archive>
void load(Archive& archive,GameObject& go)
{
	RenderComponent rcp;
	TransformComponent tcp;
	HitboxComponent hcp;
	DialogComponent dcp;
	OverheadComponent ohd;
	RigidComponent rig;
	ReputationComponent rep;
	HealthComponent healthcp;
	StatsComponent stats;
	int ID;
	int componentCount = 0;
	std::string versionName = "";
	{
		archive(versionName);
		//archive(a);
		archive(go.name);
		archive(componentCount);
		for(int i = 0; i < componentCount; i++)
		{
			archive(ID);
			if(ID == IBaseComponent<RenderComponent>::typeID)
			{
				archive(rcp);

				go.AddComponent(new RenderComponent(rcp));

				sf::Sprite* sprite = &go.GetComponent<RenderComponent>()->sprite;

				//int x = sprite->getTextureRect().width;
				//int y = sprite->getTextureRect().height;
				//sprite->setOrigin(x / 2,y / 2);
			}
			else if(ID == IBaseComponent<TransformComponent>::typeID)
			{
				archive(tcp);
				// change to go.AddComponent(tcp);
				go.GetComponent<TransformComponent>()->position.x = tcp.position.x;
				go.GetComponent<TransformComponent>()->position.y = tcp.position.y;
				go.GetComponent<TransformComponent>()->size.x = tcp.size.x;
				go.GetComponent<TransformComponent>()->size.y = tcp.size.y;
				go.GetComponent<TransformComponent>()->rotation.x = tcp.rotation.x;
				go.GetComponent<TransformComponent>()->rotation.y = tcp.rotation.y;
			}
			else if(ID == IBaseComponent<HitboxComponent>::typeID)
			{
				archive(hcp);
				go.AddComponent(new HitboxComponent(hcp));
			}
			else if(ID == IBaseComponent<DialogComponent>::typeID)
			{
				archive(dcp);
				go.AddComponent(new DialogComponent(dcp));
			}
			else if(ID == IBaseComponent<OverheadComponent>::typeID)
			{
				archive(ohd);
				go.AddComponent(new OverheadComponent(ohd));
			}
			else if(ID == IBaseComponent<RigidComponent>::typeID)
			{
				archive(rig);
				go.AddComponent(new RigidComponent(rig));
			}
			else if(ID == IBaseComponent<ReputationComponent>::typeID)
			{
				archive(rep);
				go.AddComponent(new ReputationComponent(rep));
			}
			else if(ID == IBaseComponent<HealthComponent>::typeID)
			{
				archive(healthcp);
				go.AddComponent(new HealthComponent(healthcp));
			}
			else if(ID == IBaseComponent<StatsComponent>::typeID)
			{
				archive(stats);
				if(go.GetComponent<StatsComponent>())
				{
					StatsComponent* tmp = go.GetComponent<StatsComponent>();
					tmp->agility = stats.agility;
					tmp->maxHealth = stats.maxHealth;
					tmp->health = stats.health;
					tmp->maxMana = stats.maxMana;
					tmp->mana = stats.mana;
					tmp->maxStamina = stats.maxStamina;
					tmp->stamina = stats.stamina;
				}
				else
					go.AddComponent(new StatsComponent(stats));
			}
		}
	}
}

#pragma endregion

#pragma region Components
#pragma region RenderComponent
template<class Archive>
void save(Archive& archive,const RenderComponent& rc)
{
	float x = rc.sprite.getScale().x;
	float y = rc.sprite.getScale().y;
	//	archive(rc.getTypeName());
	archive(rc.componentName);
	archive(rc.renderlayer);
	archive(rc.textureName);
	archive(x);
	archive(y);
	archive(rc.size.x);
	archive(rc.size.y);
	archive(rc.animation);
	archive(rc.frameSpeed);
	archive(rc.outline);
}
template<class Archive>
void load(Archive& archive,RenderComponent& rc)
{
	float x,y;
	//	archive(rc.getTypeName());
	archive(rc.componentName);
	archive(rc.renderlayer);
	archive(rc.textureName);
	archive(x);
	archive(y);
	rc.sprite.setScale(x,y);
	archive(rc.size.x);
	archive(rc.size.y);
	archive(rc.animation);
	archive(rc.frameSpeed);
	archive(rc.outline);
}
#pragma endregion

#pragma region BaseComponent
template<class Archive>
void save(Archive& archive,const BaseComponent& bc)
{
	archive(versionName);
	//archive(bc.componentName);
}
#pragma endregion

#pragma region TransformComponent
template<class Archive>
void save(Archive &ar,const TransformComponent &tc)
{
	//ar(tc.componentName);
	ar(tc.position.x);
	ar(tc.position.y);
	ar(tc.rotation.x);
	ar(tc.rotation.y);
	ar(tc.size.x);
	ar(tc.size.y);
}
template<class Archive>
void load(Archive &ar,TransformComponent &tc)
{
	//ar(tc.componentName);
	ar(tc.position.x);
	ar(tc.position.y);
	ar(tc.rotation.x);
	ar(tc.rotation.y);
	ar(tc.size.x);
	ar(tc.size.y);
}
#pragma endregion

#pragma region HitboxComponent
template <class Archive>
void save(Archive &ar,const HitboxComponent &hc)
{
	ar(hc.bounding.position.x);
	ar(hc.bounding.position.y);
	ar(hc.bounding.size.x);
	ar(hc.bounding.size.y);
}
template <class Archive>
void load(Archive &ar,HitboxComponent &hc)
{
	ar(hc.bounding.position.x);
	ar(hc.bounding.position.y);
	ar(hc.bounding.size.x);
	ar(hc.bounding.size.y);
}
#pragma endregion

#pragma region DialogComponent
template <class Archive>
void save(Archive& ar,const DialogComponent& dc)
{
	ar(dc.fontName);
	ar(*dc.msg);
	ar(dc.position.x);
	ar(dc.position.y);
	ar(dc.dialogMessage);
}
template <class Archive>
void load(Archive& ar,DialogComponent& dc)
{
	ar(dc.fontName);
	ar(*dc.msg);
	ar(dc.position.x);
	ar(dc.position.y);
	ar(dc.dialogMessage);
}
#pragma endregion

#pragma region OverheadComponent
template <class Archive>
void save(Archive& ar,const OverheadComponent& ohd)
{
	ar(ohd.msg);
	ar(ohd.pos->x);
	ar(ohd.pos->y);
	ar(ohd.offset.x);
	ar(ohd.offset.y);
}

template <class Archive>
void load(Archive& ar,OverheadComponent& ohd)
{
	ar(ohd.msg);
	ar(ohd.pos->x);
	ar(ohd.pos->y);
	ar(ohd.offset.x);
	ar(ohd.offset.y);
}
#pragma endregion

#pragma region RigidComponent
template <class Archive>
void save(Archive& ar,const RigidComponent& rig)
{
	ar(rig.bounding.size.x);
	ar(rig.bounding.size.y);
	//ar(rig.gravity);
	ar(rig.mass);
}
template <class Archive>
void load(Archive& ar,RigidComponent& rig)
{
	ar(rig.bounding.size.x);
	ar(rig.bounding.size.y);
	//ar(rig.gravity);
	ar(rig.mass);
}
#pragma endregion

#pragma region ReputationComponent
template <class Archive>
void save(Archive& ar,const ReputationComponent& rep)
{
	ar(rep.rep.size());
	for(std::map<std::string,int>::const_iterator it = rep.rep.begin(); it != rep.rep.end(); it++)
	{
		ar(it->first);
		ar(it->second);
	}
	ar(rep.levels.size());
	for(std::map<std::string,int>::const_iterator it = rep.levels.begin(); it != rep.levels.end(); it++)
	{
		ar(it->first);
		ar(it->second);
	}
}
template <class Archive>
void load(Archive& ar,ReputationComponent& rep)
{
	int size = 0;
	std::string first = "";
	int second = 0;
	ar(size);
	for(int it = 0; it < size; it++)
	{
		ar(first);
		ar(second);
		rep.rep.insert(std::pair<std::string,int>(first,second));
	}
	ar(size);
	for(int it = 0; it < size; it++)
	{
		ar(first);
		ar(second);
		rep.levels.insert(std::pair<std::string,int>(first,second));
	}
}
#pragma endregion

#pragma region HealthComponent
template <class Archive>
void save(Archive& ar,const HealthComponent& hcp)
{
	ar(hcp.dead);
	ar(hcp.invulnerable);
}
template <class Archive>
void load(Archive& ar,HealthComponent& hcp)
{
	ar(hcp.dead);
	ar(hcp.invulnerable);
}
#pragma endregion

#pragma region StatsComponent
template<class Archive>
void save(Archive& ar,const StatsComponent &stats)
{
	ar(stats.agility);
	ar(stats.maxHealth);
	ar(stats.health);
	ar(stats.maxMana);
	ar(stats.mana);
	ar(stats.maxStamina);
	ar(stats.mana);
}
template<class Archive>
void load(Archive& ar,StatsComponent &stats)
{
	ar(stats.agility);
	ar(stats.maxHealth);
	ar(stats.health);
	ar(stats.maxMana);
	ar(stats.mana);
	ar(stats.maxStamina);
	ar(stats.mana);
}
#pragma endregion

#pragma endregion

#pragma region ItemTypes
#pragma region Item
template <class Archive>
void save(Archive& ar,const Item& item)
{
	ar(item.ID);
	ar(item.description);
	ar(item.iconName);
	ar(item.name);
	ar(item.price);
	ar(item.stackable);
	ar(item.tag);
	ar(item.weight);
}
template <class Archive>
void load(Archive& ar,Item& item)
{
	ar(item.ID);
	ar(item.description);
	ar(item.iconName);
	ar(item.name);
	ar(item.price);
	ar(item.stackable);
	ar(item.tag);
	ar(item.weight);
}
#pragma endregion

#pragma region Armor
template <class Archive>
void save(Archive& ar,const Armor& item)
{
	ar(item.ID);
	ar(item.description);
	ar(item.iconName);
	ar(item.name);
	ar(item.price);
	ar(item.stackable);
	ar(item.tag);
	ar(item.weight);
	ar(item.armorIcon);
	ar(item.armorType);
	ar(item..defense);
}
template <class Archive>
void load(Archive& ar,Armor& item)
{
	ar(item.ID);
	ar(item.description);
	ar(item.iconName);
	ar(item.name);
	ar(item.price);
	ar(item.stackable);
	ar(item.tag);
	ar(item.weight);
	ar(item.armorIcon);
	ar(item.armorType);
	ar(item..defense);
}
#pragma endregion

#pragma region Bag
template<class Archive>
void save(Archive& ar,const Bag& item)
{
	ar(item.ID);
	ar(item.description);
	ar(item.iconName);
	ar(item.name);
	ar(item.price);
	ar(item.stackable);
	ar(item.tag);
	ar(item.weight);
	ar(item.size);
}
template<class Archive>
void load(Archive& ar,Bag& item)
{
	ar(item.ID);
	ar(item.description);
	ar(item.iconName);
	ar(item.name);
	ar(item.price);
	ar(item.stackable);
	ar(item.tag);
	ar(item.weight);
	ar(item.size);
}
#pragma endregion

#pragma endregion
#pragma region Zone
template<class Archive>
void save(Archive &ar, const DBZone&zone)
{
	ar(zone.name);
	ar(zone.ID);
	ar(zone.background);
	ar(zone.loadingScreen);
	ar(zone.loadingScreenMessage);
	ar(zone.prefabList.size());
	for (size_t i = 0; i < zone.prefabList.size(); i++)
	{
		ar(zone.prefabList[i].first);
		ar(zone.prefabList[i].second.x);
		ar(zone.prefabList[i].second.y);
	}
}
template<class Archive>
void load(Archive &ar,DBZone &zone)
{
	size_t size = 0;
	Tile t;
	ar(zone.name);
	ar(zone.ID);
	ar(t);
	zone.background = t;
	ar(t);
	zone.loadingScreen = t;
	ar(zone.loadingScreenMessage);
	ar(size);
	for (size_t i = 0; i < size; i++)
	{
		size_t ID;
		Vector2 pos;
		ar(ID);
		ar(pos.x);
		ar(pos.y);
		zone.prefabList.push_back(std::pair<size_t, Vector2>(ID, pos));
	}
}
template<class Archive>
void save(Archive &ar, const Zone&zone)
{
	ar(zone.name);
	ar(zone.ID);
	ar(zone.background);
	ar(zone.loadScreen);
	ar(zone.loadingScreenMessage);
	ar(zone.objects.size());
	for (size_t i = 0; i < zone.objects.size(); i++)
	{
		ar(zone.objects[i].first);
		ar(*zone.objects[i].second);
	}
}
template<class Archive>
void load(Archive &ar, Zone &zone)
{
	size_t size = 0;
	Tile t;
	ar(zone.name);
	ar(zone.ID);
	ar(t);
	zone.background = t;
	ar(t);
	zone.loadScreen = t;
	ar(zone.loadingScreenMessage);
	ar(size);
	for (size_t i = 0; i < size; i++)
	{
		size_t ID;
		GameObject* obj = new GameObject();
		ar(ID);
		ar(*obj);
		zone.objects.push_back(std::pair<size_t, GameObject*>(ID, obj));
	}
}
#pragma endregion

#pragma region Tile
template<class Archive>
void save(Archive &ar,const Tile & t)
{
	ar(t.name);
	ar(t.position.x);
	ar(t.position.y);
	ar(t.size.x);
	ar(t.size.y);
}
template<class Archive>
void load(Archive &ar,Tile & t)
{
	ar(t.name);
	ar(t.position.x);
	ar(t.position.y);
	ar(t.size.x);
	ar(t.size.y);
}
#pragma endregion

namespace GUI
{
	namespace Text
	{
#pragma region Message
		template <class Archive>
		void save(Archive& ar, const GUI::Text::Message& msg)
		{
			std::string txt = msg.entireString.getString();
			ar(msg.marginWidth);
			ar(msg.maxLength);
			ar(msg.size);
			ar(txt);
			ar(msg.color.r);
			ar(msg.color.g);
			ar(msg.color.b);
			ar(msg.color.a);
			ar(msg.text[0].first.getPosition().x);
			ar(msg.text[0].first.getPosition().y);
			ar(msg.duration);
		}
		template <class Archive>
		void load(Archive& ar, GUI::Text::Message& msg)
		{
			std::string text;
			int x = 0;
			int y = 0;
			ar(msg.marginWidth);
			ar(msg.maxLength);
			ar(msg.size);
			ar(text);
			msg = text;
			ar(msg.color.r);
			ar(msg.color.g);
			ar(msg.color.b);
			ar(msg.color.a);
			ar(x);
			ar(y);
			msg.setPosition(x, y);
			ar(msg.duration);
		}
#pragma endregion

#pragma region FloatingText
		template <class Archive>
		void save(Archive& ar, const GUI::Text::FloatingText& msg)
		{
			Engine::Window.debug.print("Saving floatingtext not implemented!", __LINE__, __FILE__);
			/*REWORK
			std::string txt = msg.entireString.getString();
			ar(msg.marginWidth);
			ar(msg.maxLength);
			ar(msg.size);
			ar(txt);
			ar(msg.color.r);
			ar(msg.color.g);
			ar(msg.color.b);
			ar(msg.color.a);
			ar(msg.iconName);
			ar(msg.text[0].first.getPosition().x);
			ar(msg.text[0].first.getPosition().y);
			ar(msg.offset.x);
			ar(msg.offset.y);
			ar(msg.duration);
			ar(msg.drawIcon);
			//*/
		}
		template <class Archive>
		void load(Archive& ar, GUI::Text::FloatingText& msg)
		{
			Engine::Window.debug.print("Loading floatingtext not implemented!", __LINE__, __FILE__);
			/*REWORK
			std::string iconName;
			std::string text;
			float x = 0;
			float y = 0;
			ar(msg.marginWidth);
			ar(msg.maxLength);
			ar(msg.size);
			ar(text);
			msg = text;
			ar(msg.color.r);
			ar(msg.color.g);
			ar(msg.color.b);
			ar(msg.color.a);
			ar(iconName);
			#ifdef _DEBUG
			try
			{
			msg.setIcon(iconName);
			}
			catch(MissingIconException ex)
			{
			MessageBox(Engine::Window.hWnd,"Missing Dialog Texture","Error:MissingDialogTexture",NULL);

			msg.iconSprite.setTexture(*ex.what());
			}
			#else

			msg.setIcon(iconName);

			#endif
			ar(x);
			ar(y);
			msg.setPosition(x,y);
			ar(msg.offset.x);
			ar(msg.offset.y);
			ar(msg.duration);
			ar(msg.drawIcon);
			*/
		}
	}
#pragma endregion
}

#pragma region Prefab
template <class Archive>
void load(Archive& ar,Prefab& pre)
{
	ar(pre.ID);
	unsigned int type;
	int size;
	ar(size);
	for(int i = 0; i < size; ++i)
	{
		ar(type);
		if(type == IBaseComponent<RenderComponent>::typeID)
		{
			RenderComponent* tmp = new RenderComponent();
			ar(*tmp);
			pre.base.push_back(tmp);
		}
		else if(type == IBaseComponent<TransformComponent>::typeID)
		{
			TransformComponent* tmp = new TransformComponent();
			ar(*tmp);
			pre.base.push_back(tmp);
		}
		else if(type == IBaseComponent<HitboxComponent>::typeID)
		{
			HitboxComponent* tmp = new HitboxComponent();
			ar(*tmp);
			pre.base.push_back(tmp);
		}
		else if(type == IBaseComponent<DialogComponent>::typeID)
		{
			DialogComponent* tmp = new DialogComponent();
			ar(*tmp);
			pre.base.push_back(tmp);
		}
		else if(type == IBaseComponent<OverheadComponent>::typeID)
		{
			OverheadComponent* tmp = new OverheadComponent();
			ar(*tmp);
			pre.base.push_back(tmp);
		}
		else if(type == IBaseComponent<RigidComponent>::typeID)
		{
			RigidComponent* tmp = new RigidComponent();
			ar(*tmp);
			pre.base.push_back(tmp);
		}
		else if(type == IBaseComponent<RigidComponent>::typeID)
		{
			ReputationComponent* tmp = new ReputationComponent();
			ar(*tmp);
			pre.base.push_back(tmp);
		}
		else if(type == IBaseComponent<HealthComponent>::typeID)
		{
			HealthComponent* tmp = new HealthComponent();
			ar(*tmp);
			pre.base.push_back(tmp);
		}
		else if(type == IBaseComponent<StatsComponent>::typeID)
		{
			StatsComponent* tmp = new StatsComponent();
			ar(*tmp);
			pre.base.push_back(tmp);
		}
	}
	ar(pre.name);
	ar(pre.tag);
}
template <class Archive>
void save(Archive& ar,const Prefab& pre)
{
	ar(pre.ID);
	ar(pre.base.size());
	size_t size = pre.base.size();
	for(int i = 0; i < size; ++i)
	{
		const unsigned int type = (Prefab(pre)).getTypeID(i);
		ar(type);
		if(type == IBaseComponent<RenderComponent>::typeID)
		{
			RenderComponent* rcp = (RenderComponent*)pre.base[i];
			ar(*rcp);
		}
		else if(type == IBaseComponent<TransformComponent>::typeID)
		{
			TransformComponent* tcp = (TransformComponent*)pre.base[i];
			ar(*tcp);
		}
		else if(type == IBaseComponent<HitboxComponent>::typeID)
		{
			HitboxComponent* hcp = (HitboxComponent*)pre.base[i];
			ar(*hcp);
		}
		else if(type == IBaseComponent<DialogComponent>::typeID)
		{
			DialogComponent* dcp = (DialogComponent*)pre.base[i];
			ar(*dcp);
		}
		else if(type == IBaseComponent<OverheadComponent>::typeID)
		{
			OverheadComponent* ohd = (OverheadComponent*)pre.base[i];
			ar(*ohd);
		}
		else if(type == IBaseComponent<RigidComponent>::typeID)
		{
			RigidComponent* tmp = (RigidComponent*)pre.base[i];
			ar(*tmp);
		}
		else if(type == IBaseComponent<ReputationComponent>::typeID)
		{
			ReputationComponent* tmp = (ReputationComponent*)pre.base[i];
			ar(*tmp);
		}
		else if(type == IBaseComponent<HealthComponent>::typeID)
		{
			HealthComponent* tmp = new HealthComponent();
			ar(*tmp);
		}
		else if(type == IBaseComponent<StatsComponent>::typeID)
		{
			StatsComponent* tmp = new StatsComponent();
			ar(*tmp);
		}
	}
	ar(pre.name);
	ar(pre.tag);
}
#pragma endregion

#pragma region PrefabContainer
template<class Archive>
void load(Archive& ar,PrefabContainer& con)
{
	int size;
	ar(size);
	for(int i = 0; i < size; ++i)
	{
		Prefab pre;
		size_t n;
		ar(n);
		ar(pre);
		con.mapOfPrefabs.insert(std::pair<size_t,Prefab>(n,pre));
	}
}
template<class Archive>
void save(Archive& ar,const PrefabContainer& con)
{
	ar(con.mapOfPrefabs.size());
	for(std::map<size_t,Prefab>::const_iterator it = con.mapOfPrefabs.begin(); it != con.mapOfPrefabs.end(); ++it)
	{
		ar(it->first);
		ar(it->second);
	}
}
#pragma endregion

#pragma region DatabaseIndex
template<class Archive>
void load(Archive& ar, DatabaseIndex& index)
{
	ar(index.row);
	ar(index.ID);
	ar(index.type);
	ar(index.flags);
}
template<class Archive>
void save(Archive& ar, const DatabaseIndex& index)
{
	ar(index.row);
	ar(index.ID);
	ar(index.type);
	ar(index.flags);
}
#pragma endregion

#pragma region Modloader
template <class Archive>
void load(Archive& ar, ModLoader& mod)
{
	std::string tmp;
	size_t size;
	ar(size);
	for (size_t i= 0; i < size; i++)
	{
		ar(tmp);
		mod.loadOrder.insert(std::pair<std::string, size_t>(tmp, i));
	}
}
bool loadModOrderFile(ModLoader& mod)
{
	std::ifstream file("ModLoadOrder.xml");
	if (file.is_open())
	{
		cereal::XMLInputArchive ar(file);
		ar(mod);
		return true;
	}
	return false;
}
#pragma endregion

#pragma region notdefined
void loadPrefab(std::string modname, Prefab& prefab,const DatabaseIndex& index)
{
	if (index.type == "Prefab")
	{
		if (index.flags == "-")
		{
			std::ifstream file(modname, std::ios::binary);
			cereal::BinaryInputArchive ar(file);
			{
				file.seekg(index.row);
				ar(prefab);
			}
		}
	}
	else
		Engine::Window.debug.print("Type is not a Prefab!", __LINE__, __FILE__);
}
DatabaseIndex loadIndex(std::string modname, size_t objectID, std::string loadType)
{
	DatabaseIndex index;
	
	std::ifstream file(modname + ".index", std::ios::binary);
	if(file.is_open())
	{
		cereal::BinaryInputArchive ar(file);
		while (index.flags != "EoF")
		{
			ar(index);
			if (index.ID == objectID && loadType == index.type)
				break;
		}
		if (index.type != loadType)
			index.type == "Err";
	}
	return index;
}
#pragma endregion

#pragma region zoneFile
void loadZoneFile(std::string modname,const DatabaseIndex& index, DBZone& zone)
{
	if (index.type == "Zone")
	{
		if (index.flags == "-")
		{
			std::ifstream file(modname, std::ios::binary);
			if (file.is_open())
			{
				cereal::BinaryInputArchive ar(file);
				{
					file.seekg(index.row);
					ar(zone);
				}
			}
		}
	}
	else
		Engine::Window.debug.print("Type is not a Zone!", __LINE__, __FILE__);
}
void loadZoneFromDB(DBZone& zoneToLoad, size_t zoneID)
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
						database.seekg(ind.row);
						cereal::BinaryInputArchive zoneLoad(database);
						zoneLoad(zoneToLoad);
						if (zoneToLoad.ID == zoneID);
							break;
					}
					else if (ind.flags == "EoF")
						eof = true;
				}
			}
		}
	}
}
void LoadAllZones(std::map<unsigned int, DBZone>& worldmap)
{
	for each (std::pair<std::string,size_t> var in Engine::World.modLoadOrder.loadOrder)
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
						std::map<unsigned int, DBZone>::iterator it = worldmap.find(ind.ID);
						if (it != worldmap.end())
						{
							// stuff exist add extra things to zone.
						}
						else
						{
							database.seekg(ind.row);
							DBZone tmp;
							cereal::BinaryInputArchive zoneLoad(database);
							zoneLoad(tmp);
							worldmap.insert(std::pair<unsigned int, DBZone>(tmp.ID, tmp));
						}
					}
					else if (ind.flags == "EoF")
						eof = true;
				}
			}
		}
	}
}
void LoadAllPrefabs(PrefabContainer& pre)
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
						std::map<unsigned int, Prefab>::iterator it = pre.find(ind.ID);
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
#pragma endregion