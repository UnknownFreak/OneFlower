
#include <fstream>
#include "LoadAndSave.hpp"
#include "Component\RenderComponent.h"
#include "Component\GameObject.h"
#include <cereal/archives/xml.hpp>
#include <fstream>
#include <cereal\types\string.hpp>
#include <cereal\types\polymorphic.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/archives/binary.hpp>
#include "Component\BaseComponent.hpp"
#include "ZoneMaker.hpp"
#include "Zone.hpp"
#include "WorldManagement.hpp"
#include <map>
#include"Component\HitboxComponent.hpp"
#include "Component\TransformComponent.hpp"
#include "Component\DialogComponent.hpp"
#include "MessageDefiner.hpp"
#include "FloatingText.hpp"
std::string versionName = "Alpha Test: 1.3v";
CEREAL_REGISTER_ARCHIVE(RenderComponent);


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


void testSave()
{
	ZoneMap zone;
	zone.ID = 1;
	GameObject test;
	test.name = "TestPlatform";
	
	test.GetComponent<TransformComponent>()->position.x = 200;
	test.GetComponent<TransformComponent>()->position.y = 300;
	test.AddComponent(new HitboxComponent());
	test.AddComponent(new RenderComponent("testCutHalf.png"));
	zone.objects.push_back(test);
	GameObject ground;
	ground.name = "da kewl ground";
	ground.AddComponent(new HitboxComponent());
	ground.AddComponent(new RenderComponent("ground.marker.png"));
	ground.GetComponent<TransformComponent>()->position.x = 0;
	ground.GetComponent<TransformComponent>()->position.y = 500;
	ground.GetComponent<RenderComponent>()->sprite.setScale(2,1);
	zone.objects.push_back(ground);

	zone.setBackground(Tile("testBackground.png",400,300));
	zone.background.sizeX = 4000;
	zone.background.sizeY = 800;
	
	zone.foregrounds.push_back(Tile("blacktree.png",250,50));
	zone.foregrounds.push_back(Tile("blacktree.png", 450, 250));
	zone.foregrounds.push_back(Tile("blacktree.png", 400, 250));
	zone.foregrounds.push_back(Tile("blacktree.png", 350, 250));
	zone.foregrounds.push_back(Tile("blacktree.png", 550, 250));
	zone.foregrounds.push_back(Tile("blacktree.png", 500, 250));
	std::ofstream file("test.zone", std::ios::binary);
	{
		cereal::BinaryOutputArchive ar(file);
		ar(zone);
	}
	/*
	GameObject go;
	go.name = "testObject";
	go.AddComponent(new DialogComponent(2.0f));
	go.GetComponent<DialogComponent>()->dialogTexture = "TestDialogChat.png";
	go.GetComponent<DialogComponent>()->msg = "Testmsg";
	std::ofstream file("test.binary", std::ios::binary);
	{
		cereal::BinaryOutputArchive ar(file);
		ar(go);
	}
	//*/
}

void testLoad()
{
	GameObject test;
	test.name = "SaveTestObjectNotLoaded";

	std::ifstream file("test.binary", std::ios::binary);
	{
		cereal::BinaryInputArchive ar(file);
		ar(test);
	}
}



#pragma region GameObject
template<class Archive>
void save(Archive& archive, const GameObject& go)
{

	//if (go != NULL)
	{
		archive(versionName);
		archive(go.name);
		archive(go.componentMap.size());
		for (std::map<int, BaseComponent*>::const_iterator it = go.componentMap.begin(); it != go.componentMap.end(); ++it)
		{	
			archive(it->first);
			//Make directives id instead and use switches
			if(it->first == IBaseComponent<RenderComponent>::typeID)
			{
				RenderComponent* rcp = (RenderComponent*)it->second;
				archive(*rcp);
			}
			else if (it->first == IBaseComponent<TransformComponent>::typeID)
			{
				TransformComponent* tcp = (TransformComponent*)it->second;
				archive(*tcp);
			}
			else if (it->first == IBaseComponent<HitboxComponent>::typeID)
			{
				HitboxComponent* hcp = (HitboxComponent*)it->second;
				archive(*hcp);
			}
			else if (it->first == IBaseComponent<DialogComponent>::typeID)
			{
				DialogComponent* dcp = (DialogComponent*)it->second;
				archive(*dcp);
			}
		}	
	}
}

template<class Archive>
void load(Archive& archive, GameObject& go)
{
	RenderComponent rcp;
	TransformComponent tcp;
	HitboxComponent hcp;
	DialogComponent dcp;
	int ID;
	int componentCount = 0;
	std::string versionName = "";
	{
		archive(versionName);
		//archive(a);
		archive(go.name);
		archive(componentCount);
		for (int i = 0; i < componentCount; i++)
		{
			archive(ID);
			if (ID == IBaseComponent<RenderComponent>::typeID)
			{
				archive(rcp);
				go.AddComponent(new RenderComponent(rcp));
			}
			else if (ID == IBaseComponent<TransformComponent>::typeID)
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
			else if (ID == IBaseComponent<HitboxComponent>::typeID)
			{
				archive(hcp);
				go.AddComponent(new HitboxComponent(hcp));
			}
			else if (ID == IBaseComponent<DialogComponent>::typeID)
			{
				archive(dcp);
				go.AddComponent(new DialogComponent(dcp));
			}
		}
	}
}

#pragma endregion

#pragma region RenderComponent
template<class Archive>
void save(Archive& archive, const RenderComponent& rc)
{
	float x = rc.sprite.getScale().x;
	float y = rc.sprite.getScale().y;
//	archive(rc.getTypeName());
	archive(rc.componentName);
	archive(rc.renderlayer);
	archive(rc.textureName);
	archive(x);
	archive(y);
}
template<class Archive>
void load(Archive& archive, RenderComponent& rc)
{
	float x, y;
	//	archive(rc.getTypeName());
	archive(rc.componentName);
	archive(rc.renderlayer);
	archive(rc.textureName);
	archive(x);
	archive(y);
	rc.sprite.setScale(x, y);
}
#pragma endregion

#pragma region BaseComponent
template<class Archive>
void save(Archive& archive,const BaseComponent& bc)
{
	archive(versionName);
	archive(bc.componentName);
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
void load(Archive &ar, TransformComponent &tc)
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
	ar(hc.position.x);
	ar(hc.position.y);
	ar(hc.size.x);
	ar(hc.size.y);
}
template <class Archive>
void load(Archive &ar, HitboxComponent &hc)
{
	ar(hc.position.x);
	ar(hc.position.y);
	ar(hc.size.x);
	ar(hc.size.y);
}
#pragma endregion

#pragma region ZoneMap
// Saves a Zone with name, id, and vector of tiles, and gameobjects
template<class Archive>
void save(Archive &ar, const ZoneMap &zm)
{

	ar(zm.name);
	ar(zm.ID);
	ar(zm.background);
	ar(zm.foregrounds.size());
	for (int i = 0; i < zm.foregrounds.size(); i++)
	{
		ar(zm.foregrounds[i]);
	}
	ar(zm.objects.size());
	for (int i = 0; i < zm.objects.size(); i++)
	{
		ar(zm.objects[i]);
	}
}
// Loads a Zone with name, id, and vector of tiles and gameobjects
template<class Archive>
void load(Archive &ar, Zone &zone) 
{
	// Variables
	int objs;
	int fgs;
	GameObject *go = nullptr;
	Tile t;
	ar(zone.name);
	ar(zone.ID);
	ar(t);
	zone.background = t;
	ar(fgs);
	for (int i = 0; i < fgs; i++)
	{
		Tile qq;
		ar(qq);
		zone.foregrounds.push_back(Tile(qq));
	}
	ar(objs);
	for (int i = 0; i < objs; i++) 
	{
		go = new GameObject();
		ar(*go);
		zone.objects.push_back(go);
	}
}
#pragma endregion

#pragma region Tile

// Saves a tile texture name, and x, y pos
template<class Archive>
void save(Archive &ar, const Tile & t)
{
	ar(t.name);
	ar(t.position.x);
	ar(t.position.y);
	ar(t.sizeX);
	ar(t.sizeY);
}

// loads a tile texture name, and x,y pos
template<class Archive>
void load(Archive &ar, Tile & t)
{
	ar(t.name);
	ar(t.position.x);
	ar(t.position.y);
	ar(t.sizeX);
	ar(t.sizeY);
}
#pragma endregion

#pragma region keybinds

// prepared save function for keybinds
template<class Archive>
void save(Archive &ar, int q)
{

}
// prepared load function for keybinds
template<class Archive>
void load(Archive &ar, int q)
{

}
#pragma endregion

#pragma region zoneInfo
void saveInfo(std::map<unsigned int, Zone>map){ 
	std::ofstream file("zone.info", std::ios::binary);
	{
		cereal::BinaryOutputArchive ar(file);
		std::map<unsigned int, Zone>::iterator it = map.begin();
		ar(map.size());
		for (it; it != map.end(); ++it) {
			ar(it->first);
			ar(it->second.getName()+".zone");
		}
	}
 }
void loadZoneInfo(std::map<unsigned int, std::string> & zoneInfo)
{
	
	std::ifstream file("zone.info", std::ios::binary);
	if(file.is_open())
	{
		cereal::BinaryInputArchive ar(file);
		unsigned int zoneID;
		std::string zoneName;
		int number;
		ar(number);
		for (int i = 0; i < number; i++) 
		{
			ar(zoneID);
			ar(zoneName);
			zoneInfo.insert(std::pair<int, std::string>(zoneID, zoneName));
		}
	}
	else
	{
		std::cout << "File did not get opened" << std::endl;
	}
}
#pragma endregion

#pragma region zoneFile
void loadZoneFile(std::string name, Zone& zone) 
{
	std::ifstream file(name, std::ios::binary);
	
	if (file.is_open())
	{
		cereal::BinaryInputArchive ar(file);
		ar(zone); //load(Archive &ar, Zone &zone);
	}
	else {
		std::cout << "Could not open file" << name << std::endl;
	}
}
#pragma endregion

#pragma region DialogComponent

template <class Archive>
void save(Archive& ar, const DialogComponent& dc)
{
	ar(dc.duration);
	ar(dc.dialogTexture);
	ar(dc.fontName);
	ar(dc.msg);

}

template <class Archive>
void load(Archive& ar, DialogComponent& dc)
{
	ar(dc.duration);
	ar(dc.dialogTexture);
	ar(dc.fontName);
	ar(dc.msg);

}
#pragma endregion

#pragma region Message
template <class Archive>
void save(Archive& ar, const Message& msg)
{
	std::string txt= msg.text.getString();
	ar(msg.marginWidth);
	ar(msg.renderLayer);
	ar(msg.maxLength);
	ar(msg.size);
	ar(txt);
	ar(msg.color.r);
	ar(msg.color.g);
	ar(msg.color.b);
	ar(msg.color.a);
	ar(msg.text.getPosition().x);
	ar(msg.text.getPosition().y);
	ar(msg.duration);
}

template <class Archive>
void load(Archive& ar, Message& msg)
{
	std::string text;
	int x = 0;
	int y = 0;
	ar(msg.marginWidth);
	ar(msg.renderLayer);
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
	msg.text.setPosition(x,y);
	ar(msg.duration);
}

#pragma endregion

#pragma region FloatingText
template <class Archive>
void save(Archive& ar, const FloatingText& msg)
{
	std::string txt = msg.text.getString();
	ar(msg.marginWidth);
	ar(msg.renderLayer);
	ar(msg.maxLength);
	ar(msg.size);
	ar(txt);
	ar(msg.color.r);
	ar(msg.color.g);
	ar(msg.color.b);
	ar(msg.color.a);
	ar(msg.iconName);
	ar(msg.text.getPosition().x);
	ar(msg.text.getPosition().y);
	ar(msg.offsetX);
	ar(msg.offsetY);
	ar(msg.duration);
}

template <class Archive>
void load(Archive& ar, FloatingText& msg)
{
	std::string iconName;
	std::string text;
	int x = 0;
	int y = 0;
	ar(msg.marginWidth);
	ar(msg.renderLayer);
	ar(msg.maxLength);
	ar(msg.size);
	ar(text);
	msg = text;
	ar(msg.color.r);
	ar(msg.color.g);
	ar(msg.color.b);
	ar(msg.color.a);
	ar(iconName);
	msg.setIcon(iconName);
	ar(x);
	ar(y);
	msg.text.setPosition(x, y);
	ar(msg.offsetX);
	ar(msg.offsetY);
	ar(msg.duration);
}

#pragma endregion