#include <cereal/types/map.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/archives/binary.hpp>
#include <fstream>
#include "LoadAndSave.hpp"
#include "Component\RenderComponent.h"
#include "Component\GameObject.h"
#include <cereal/archives/xml.hpp>
#include <fstream>
#include <cereal\types\string.hpp>
#include <cereal\types\polymorphic.hpp>
#include "Component\BaseComponent.hpp"


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
	GameObject test;
	test.name = "SaveTestObject";
	test.AddComponent(new RenderComponent);
	std::ofstream file("test.binary", std::ios::binary);
	{
		cereal::BinaryOutputArchive ar(file);
		ar(test);
	}
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
void save(Archive& archive, const RenderComponent& rc)
{
//	archive(rc.getTypeName());
	archive(rc.componentName);
	archive(rc.renderlayer);
	archive(rc.textureName);
}



template<class Archive>
void save(Archive& archive,const BaseComponent& bc)
{
	archive(versionName);
	archive(bc.componentName);
}

template<class Archive>
void load(Archive& archive,GameObject& go)
{
	int componentCount = 0;
	std::string versionName = "";
	{
		archive(versionName);
		//archive(a);
		archive(go.name);
	}
}
