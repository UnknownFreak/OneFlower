
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
#include "ZoneMap.hpp"
#include "Zone.hpp"

std::string versionName = "Alpha Test: 1.3v";
	


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
	/*
	GameObject test;
	test.name = "SaveTestObject";
	test.AddComponent(new RenderComponent);
	std::ofstream file("test.binary", std::ios::binary);
	{
		cereal::BinaryOutputArchive ar(file);
		ar(test);
	}
	//*/
	GameObject go;
	go.name = "TestObject";
	ZoneMap zone;
	zone.name = "TestZone";
	zone.addBackground(Tile());
	zone.addBackground(Tile());
	zone.addGameObject(go);
	std::ofstream file("test.zone", std::ios::binary);
	{
		cereal::BinaryOutputArchive ar(file);
		ar(zone);
	}
}

void testLoad()
{
	/*
	GameObject test;
	test.name = "SaveTestObjectNotLoaded";

	std::ifstream file("test.binary", std::ios::binary);
	{
		cereal::BinaryInputArchive ar(file);
		ar(test);
	}
	//*/
	Zone test;
	test.name = "Test object not loaded";
	std::ifstream file("test.zone", std::ios::binary);
	{
		cereal::BinaryInputArchive ar(file);
		ar(test);
	}
}
//*/
#pragma region Player
void loadPlayer(GameObject& go)
{
	/*
	int m1, m2, m3;
	std::stringstream ss; // any stream can be used
	cereal::BinaryInputArchive iarchive(ss); // Create an input archive
	iarchive(m1, m2, m3); // Read the data from the archive
	printf("%d %d %d", m1, m2, m3);
	//*/
}

#pragma endregion

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
				RenderComponent*  rcp = (RenderComponent*)it->second;
				archive(*rcp);
			}
		}	
	}
}

template<class Archive>
void load(Archive& archive, GameObject& go)
{
	int componentCount = 0;
	std::string versionName = "";
	{
		archive(versionName);
		//archive(a);
		archive(go.name);
	}
}

#pragma endregion

#pragma region RenderComponent
template<class Archive>
void save(Archive& archive, const RenderComponent& rc)
{
//	archive(rc.getTypeName());
	archive(rc.componentName);
	archive(rc.renderlayer);
	archive(rc.textureName);
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

#pragma region ZoneMap
// Saves a Zone with name, id, and vector of tiles, and gameobjects
template<class Archive>
void save(Archive &ar, const ZoneMap &zm) {
	std::cout << "Starting save" << std::endl;
	
	ar(zm.name);
	std::cout << zm.name << std::endl;
	ar(zm.id);
	std::cout << zm.id << std::endl;
	ar(zm.backgrounds.size());
	std::cout << zm.backgrounds.size() << std::endl;
	for (int i = 0; i < zm.backgrounds.size(); i++) {
		ar(zm.backgrounds[i]);
		std::cout << zm.backgrounds[i].name << std::endl;
		std::cout << zm.backgrounds[i].position.x << std::endl;
		std::cout << zm.backgrounds[i].position.y << std::endl;
	}
	ar(zm.objects.size());
	std::cout << zm.objects.size() << std::endl;
	for (int i = 0; i < zm.objects.size(); i++) {
		ar(zm.objects[i]);
		std::cout << zm.objects[i].name << std::endl;
	}
	std::cout << "Save Done" << std::endl;
}
// Loads a Zone with name, id, and vector of tiles and gameobjects
template<class Archive>
void load(Archive &ar, Zone &zone) {
	std::cout << "Starting load" << std::endl;
	// Variables
	int bgs;
	int objs;
	int id;
	Tile t;
	GameObject go;
	std::string str;
	std::vector<Tile>tiles;
	std::vector<GameObject>gos;

	ar(str);
	std::cout << str << std::endl;
	ar(id);
	std::cout << id << std::endl;
	ar(bgs);

	std::cout << bgs << std::endl;
	
	for (int i = 0; i < bgs; i++) {
		ar(t);
		tiles.push_back(t);
		std::cout << tiles[i].name << std::endl;
		std::cout << tiles[i].position.x << std::endl;
		std::cout << tiles[i].position.y << std::endl;
	}
	ar(objs);
	for (int i = 0; i < objs; i++) {
		ar(go);
		gos.push_back(go);
		std::cout << gos[i].name << std::endl;
	}
	zone = Zone(str,id,tiles,gos);

	std::cout << zone.name << std::endl;
	std::cout << "Load finished" << std::endl;
}
#pragma endregion

#pragma region Tile

// Saves a tile texture name, and x, y pos
template<class Archive>
void save(Archive &ar, const Tile & t) {
	ar(t.name);
	ar(t.position.x);
	ar(t.position.y);
}

// loads a tile texture name, and x,y pos
template<class Archive>
void load(Archive &ar, Tile & t) {
	ar(t.name);
	ar(t.position.x);
	ar(t.position.y);
}
#pragma endregion


#pragma region keybinds

// prepared save function for keybinds
template<class Archive>
void save(Archive &ar, int q) {

}
// prepared load function for keybinds
template<class Archive>
void load(Archive &ar, int q) {

}
#pragma endregion