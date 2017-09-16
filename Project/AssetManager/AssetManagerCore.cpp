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

#include <Model\TextureMap.hpp>
#include <Model\SpriterEntityInstance.hpp>
#include <Model\SpriterModelContainer.hpp>
#include <Model\SpriteSheetAnimation.hpp>
#include <Model\SpriterTextureMapper.hpp>

#include <Model\IModel.hpp>
#include <Model\StaticModel.hpp>
#include <Model\SpriteSheetModel.hpp>

CEREAL_REGISTER_TYPE(BaseComponent);
//CEREAL_REGISTER_TYPE(IBaseComponent<Component::DialogComponent>)
CEREAL_REGISTER_TYPE(Component::HitboxComponent)
//CEREAL_REGISTER_TYPE(IBaseComponent<Component::OverheadComponent>)
//CEREAL_REGISTER_TYPE(IBaseComponent<Component::PlayerComponent> )
CEREAL_REGISTER_TYPE(Component::RenderComponent)
//CEREAL_REGISTER_TYPE(IBaseComponent<Component::RigidComponent> )
//CEREAL_REGISTER_TYPE(IBaseComponent<Component::Timer>)
CEREAL_REGISTER_TYPE(Component::TransformComponent)

CEREAL_REGISTER_TYPE(StaticModel);

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

CEREAL_REGISTER_POLYMORPHIC_RELATION(IModel, StaticModel);
CEREAL_REGISTER_POLYMORPHIC_RELATION(IModel, SpriteSheetModel);

AssetManagerCore::AssetMode AssetManagerCore::assetMode = AssetManagerCore::AssetMode::FINE;
AssetManagerCore::Mode AssetManagerCore::state = AssetManagerCore::Mode::UNDEFINED;
Core::String AssetManagerCore::openedMod = "<Not Set>";

OneVersion AssetManagerCore::assetManagerVersion = OneVersion(0, 0, 1);

AssetManagerCore::Mode AssetManagerCore::getMode()
{
	return state;
}

void AssetManagerCore::testRequestor()
{

	Prefab p;
	p.name = "test.pref";
	p.tag = "TESTING";
	p.fromMod = "test";
	p.ID = 0;
	p.base.push_back(new Component::TransformComponent());
	p.base.push_back(new Component::HitboxComponent(0, 0, 50, 50));
	Requester<Prefab>* req = &Engine::PrefabRequester;
#ifdef _EDITOR_
	Engine::PrefabRequester.add("test", 0, p);

	ModHeader modhdr;
	modhdr.name = "test";
	std::ofstream file("test", std::ios::binary);
	std::ofstream index("test.index", std::ios::binary);
	{
		DatabaseIndex ind;
		ind.flags = DatabaseIndex::ObjectFlag::NoFlag;
		ind.ID = 0;
		ind.type = DatabaseIndex::ObjectTypeEnum::Header;
		ind.modFile = modhdr.name;
		ind.row = file.tellp();
		cereal::BinaryOutputArchive mainAr(file);
		cereal::BinaryOutputArchive indexAr(index);


		Engine::PrefabRequester.save(ind, file, indexAr, mainAr);
		ind.flags = DatabaseIndex::ObjectFlag::EoF;
		ind.ID = 0;
		ind.type = DatabaseIndex::ObjectTypeEnum::EoF;
		ind.modFile = modhdr.name;
		ind.row = file.tellp();
	}
	file.close();
	index.close();
#endif _EDITOR_
	Engine::World.modLoadOrder.loadOrder.clear();
	Engine::World.modLoadOrder.loadOrder.insert(std::make_pair("test", 0));
	Engine::PrefabRequester.clear();

	{

		Reference<Prefab>*& pr = Engine::PrefabRequester.request("test", 0);

		pr->getReferenced();
	}

	StaticModel* m = new StaticModel();
	m->m_TopLeft = Core::Vector2i(50, 50);
	m->m_BottomRight = Core::Vector2i(50, 50);
	m->fromMod = "test";
	IModel* mpr = m;

	Requester<IModel*>* reqq = &Engine::ModelRequester;
#ifdef _EDITOR_
	Engine::ModelRequester.add("test", 0, mpr);

	modhdr.name = "testIModel";
	std::ofstream file2("testIModel", std::ios::binary);
	std::ofstream index2("testIModel.index", std::ios::binary);
	{
		DatabaseIndex ind;
		ind.flags = DatabaseIndex::ObjectFlag::NoFlag;
		ind.ID = 0;
		ind.type = DatabaseIndex::ObjectTypeEnum::Header;
		ind.modFile = modhdr.name;
		ind.row = file.tellp();
		cereal::BinaryOutputArchive mainAr(file2);
		cereal::BinaryOutputArchive indexAr(index2);



		Engine::ModelRequester.save(ind, file2, indexAr, mainAr);
		ind.flags = DatabaseIndex::ObjectFlag::EoF;
		ind.ID = 0;
		ind.type = DatabaseIndex::ObjectTypeEnum::EoF;
		ind.modFile = modhdr.name;
		ind.row = file.tellp();
	}
	file2.close();
	index2.close();
#endif _EDITOR_
	Engine::World.modLoadOrder.loadOrder.clear();
	Engine::World.modLoadOrder.loadOrder.insert(std::make_pair("testIModel", 0));
	Engine::ModelRequester.clear();

	Reference<IModel*>*& mr = Engine::ModelRequester.request("test", 0);

	{
		IModel*& mdl = mr->getReferenced();
		Engine::ModelRequester.requestRemoval("test", 0);
		bool b = mdl == nullptr;
		if (b)
			Logger::Info("Success: mdl is nullpointer, as requested");
		else
		{
			Core::String s;

			std::stringstream ss;
			ss << "Failed: mdl is not nullpointer: mdl=" << mdl << " nullptr:" << NULL << " is true:" << (mdl == nullptr) << std::endl;
			ss >> s;
			s = ss.str();
			Logger::Error(s);
		}
	}

	//Engine::ModelRequester.clear();

	//IModel*& mdl = mr->getReferenced();

}

void AssetManagerCore::saveGameDatabase(
	std::string filename,
	ModHeader& modhdr,
	PrefabContainer& prefabs,
	std::map<std::pair<std::string, size_t>, DBZone>& EditorAllZones)
	//,
	//std::map<std::pair<std::string, size_t>, Items::Item*>& editorAllItems,
	//std::map<std::pair<std::string, size_t>, Quests::Quest>& EditorAllQuests)
{
	std::ofstream file(filename, std::ios::binary);
	filename.append(".index");
	std::ofstream index(filename, std::ios::binary);
	{
		DatabaseIndex ind;
		cereal::BinaryOutputArchive mainAr(file);
		cereal::BinaryOutputArchive indexAr(index);
		ind.flags = DatabaseIndex::ObjectFlag::NoFlag;
		ind.ID = 0;
		ind.type = DatabaseIndex::ObjectTypeEnum::Header;
		ind.modFile = modhdr.name;
		ind.row = file.tellp();
		indexAr(ind);
		mainAr(modhdr);

		ind.flags = DatabaseIndex::ObjectFlag::NoFlag;
		ind.ID = 0;
		ind.type = DatabaseIndex::ObjectTypeEnum::ModelContainer;
		ind.modFile = "NULL";
		ind.row = file.tellp();
		indexAr(ind);
		mainAr(Engine::ModelContainer);

		
		saveZones(ind, EditorAllZones, file, index, indexAr, mainAr);
		savePrefabs(ind, prefabs, file, index, indexAr, mainAr);
		
		//for (std::map<std::pair<std::string, size_t>, Items::Item*>::iterator it = editorAllItems.begin(); it != editorAllItems.end(); it++)
		//{
		//	ind.flags = "-";
		//	ind.ID = it->first.second;
		//	ind.type = "Item";
		//	ind.modFile = it->second->fromMod;
		//	ind.row = file.tellp();
		//	if (it->second->fromMod == Engine::World.openedMod && it->second->mode == EditorObjectSaveMode::EDIT)
		//		it->second->mode = EditorObjectSaveMode::DEFAULT;
		//	else if (it->second->fromMod == Engine::World.openedMod && it->second->mode == EditorObjectSaveMode::ADD)
		//		it->second->mode = EditorObjectSaveMode::DEFAULT;
		//	indexAr(ind);
		//	saveItem(mainAr, it->second);
		//}
		//for (std::map<std::pair<std::string, size_t>, Quests::Quest>::iterator it = EditorAllQuests.begin(); it != EditorAllQuests.end(); it++)
		//{
		//	ind.flags = "-";
		//	ind.ID = it->first.second;
		//	ind.type = "Quest";
		//	ind.modFile = it->second.fromMod;
		//	ind.row = file.tellp();
		//	if (it->second.mode != EditorObjectSaveMode::REMOVE)
		//	{
		//		bool b = true;
		//		if (it->second.fromMod == Engine::World.openedMod && it->second.mode == EditorObjectSaveMode::EDIT)
		//			it->second.mode = EditorObjectSaveMode::DEFAULT;
		//		else if (it->second.fromMod == Engine::World.openedMod && it->second.mode == EditorObjectSaveMode::ADD)
		//			it->second.mode = EditorObjectSaveMode::DEFAULT;
		//		else if (it->second.fromMod != Engine::World.openedMod && it->second.mode == EditorObjectSaveMode::DEFAULT)
		//		{
		//			b = false;
		//		}
		//		else if (it->second.mode > EditorObjectSaveMode::ADD)
		//			it->second.mode = EditorObjectSaveMode::DEFAULT;
		//		if (b)
		//		{
		//			indexAr(ind);
		//			mainAr(it->second);
		//		}
		//	}
		//}
		ind.ID = 0xFFFFFFFF;
		ind.type = DatabaseIndex::ObjectTypeEnum::EoF;
		ind.row = file.tellp();
		ind.flags = DatabaseIndex::ObjectFlag::EoF;
		indexAr(ind);
	}
	file.close();
	index.close();
}

void AssetManagerCore::savePrefabs(DatabaseIndex & ind, PrefabContainer& prefabs, std::ostream& file, std::ostream& index, cereal::BinaryOutputArchive& indexAr, cereal::BinaryOutputArchive& mainAr)
{
	for (std::map<std::pair<std::string, size_t>, Prefab>::iterator it = prefabs.begin(); it != prefabs.end(); it++)
	{
		ind.flags = DatabaseIndex::ObjectFlag::NoFlag;
		ind.ID = it->first.second;
		ind.type = DatabaseIndex::ObjectTypeEnum::Prefab;
		ind.modFile = it->second.fromMod;
		ind.row = file.tellp();
		if (it->second.mode != ObjectSaveMode::REMOVE)
		{
			bool b = true;
			if (it->second.fromMod == AssetManagerCore::openedMod && it->second.mode == ObjectSaveMode::EDIT)
				it->second.mode = ObjectSaveMode::DEFAULT;
			else if (it->second.fromMod == AssetManagerCore::openedMod && it->second.mode == ObjectSaveMode::ADD)
				it->second.mode = ObjectSaveMode::DEFAULT;
			else if (it->second.fromMod != AssetManagerCore::openedMod && it->second.mode == ObjectSaveMode::DEFAULT)
				b = false;
			else if (it->second.mode > ObjectSaveMode::ADD)
				it->second.mode = ObjectSaveMode::DEFAULT;
			if (b)
			{
				indexAr(ind);
				mainAr(it->second);
			}
		}
	}
}

void AssetManagerCore::saveZones(DatabaseIndex & ind, std::map<std::pair<std::string, size_t>, DBZone>& allzones, std::ostream & file, std::ostream & index, cereal::BinaryOutputArchive & indexAr, cereal::BinaryOutputArchive & mainAr)
{
	for (std::map<std::pair<std::string, size_t>, DBZone>::iterator it = allzones.begin(); it != allzones.end(); it++)
	{
		ind.flags = DatabaseIndex::ObjectFlag::NoFlag;
		ind.ID = it->first.second;
		ind.type = DatabaseIndex::ObjectTypeEnum::Zone;
		ind.modFile = it->second.fromMod;
		ind.row = file.tellp();
		if (it->second.mode != ObjectSaveMode::REMOVE)
		{
			bool b = true;
			if (it->second.fromMod == AssetManagerCore::openedMod && it->second.mode == ObjectSaveMode::EDIT)
				it->second.mode = ObjectSaveMode::DEFAULT;
			else if (it->second.fromMod == AssetManagerCore::openedMod && it->second.mode == ObjectSaveMode::ADD)
				it->second.mode = ObjectSaveMode::DEFAULT;
			else if (it->second.fromMod != AssetManagerCore::openedMod && it->second.mode == ObjectSaveMode::DEFAULT)
				b = false;
			if (ind.ID == 0)
				b = false;
			if (b)
			{
				indexAr(ind);
				mainAr(it->second);
			}
		}
	}
}



void AssetManagerCore::saveModOrderFile(ModLoader & mod)
{
	std::ofstream file("Data\\ModLoadOrder.xml");
	{
		cereal::XMLOutputArchive ar(file);
		ar(mod);
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
		ind.type = DatabaseIndex::ObjectTypeEnum::Prefab;
		ind.row = file.tellp();
		indexAr(ind);
		mainAr(pref);

		ind.ID = pref2.ID;
		ind.type = DatabaseIndex::ObjectTypeEnum::Prefab;
		ind.row = file.tellp();
		indexAr(ind);
		mainAr(pref2);

		ind.ID = pref3.ID;
		ind.type = DatabaseIndex::ObjectTypeEnum::Prefab;
		ind.row = file.tellp();
		indexAr(ind);
		mainAr(pref3);

		ind.ID = 0xffffffff;
		ind.type = DatabaseIndex::ObjectTypeEnum::EoF;
		ind.row = file.tellp();
		ind.flags = DatabaseIndex::ObjectFlag::EoF;
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