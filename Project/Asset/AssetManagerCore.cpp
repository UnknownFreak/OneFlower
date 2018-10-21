#include "AssetManagerCore.hpp"

#include <Core/Component/BaseComponent.hpp>
#include <Core\Component\TransformComponent.hpp>
#include <Core\Component\GameObject.h>
#include <Graphic\Component\RenderComponent.h>
#include <Physics\Component\HitboxComponent.hpp>

#include "DatabaseIndex.hpp"
#include <fstream>

#include <cereal\archives\binary.hpp>
#include <cereal\archives\xml.hpp>
#include <cereal\types\string.hpp>
#include <cereal\types\polymorphic.hpp>
#include <cereal\types\map.hpp>
#include <cereal\types\memory.hpp>
#include <cereal\access.hpp>

#include <Graphic\World\WorldManager.hpp>
#include <Graphic\World\Zone.hpp>

#include <Model\TextureMap.hpp>
#include <Model\SpriteSheetAnimation.hpp>

#include <Model\IModel.hpp>
#include <Model\StaticModel.hpp>
#include <Model\SpriteSheetModel.hpp>

#ifdef _EDITOR_
#include <Editor/EditorEvents.hpp>
#endif

CEREAL_REGISTER_TYPE(Component::Base);
//CEREAL_REGISTER_TYPE(IBaseComponent<Component::DialogComponent>)
CEREAL_REGISTER_TYPE(Component::HitboxComponent)
//CEREAL_REGISTER_TYPE(IBaseComponent<Component::OverheadComponent>)
//CEREAL_REGISTER_TYPE(IBaseComponent<Component::PlayerComponent> )
CEREAL_REGISTER_TYPE(Component::RenderComponent)
//CEREAL_REGISTER_TYPE(IBaseComponent<Component::RigidComponent> )
//CEREAL_REGISTER_TYPE(IBaseComponent<Component::Timer>)
CEREAL_REGISTER_TYPE(Component::Transform)

CEREAL_REGISTER_TYPE(StaticModel);

//CEREAL_REGISTER_TYPE_WITH_NAME(Component::DialogComponent, "Dialog")
//CEREAL_REGISTER_TYPE_WITH_NAME(Component::HitboxComponent, "Hitbox")
//CEREAL_REGISTER_TYPE_WITH_NAME(Component::OverheadComponent, "Overhead")
//CEREAL_REGISTER_TYPE_WITH_NAME(Component::PlayerComponent, "Player")
//CEREAL_REGISTER_TYPE_WITH_NAME(Component::RenderComponent, "Render")
//CEREAL_REGISTER_TYPE_WITH_NAME(Component::RigidComponent, "Rigid")
//CEREAL_REGISTER_TYPE_WITH_NAME(Component::Timer, "Timer")
//CEREAL_REGISTER_TYPE_WITH_NAME(Component::Transform, "Transform")

//CEREAL_REGISTER_POLYMORPHIC_RELATION(Component::Base, Component::DialogComponent)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Component::Base, Component::HitboxComponent)
//CEREAL_REGISTER_POLYMORPHIC_RELATION(Component::Base, Component::OverheadComponent)
//CEREAL_REGISTER_POLYMORPHIC_RELATION(Component::Base, Component::PlayerComponent)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Component::Base, Component::RenderComponent)
//CEREAL_REGISTER_POLYMORPHIC_RELATION(Component::Base, Component::RigidComponent)
//CEREAL_REGISTER_POLYMORPHIC_RELATION(Component::Base, Component::Timer)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Component::Base, Component::Transform)

CEREAL_REGISTER_POLYMORPHIC_RELATION(IModel, StaticModel);
CEREAL_REGISTER_POLYMORPHIC_RELATION(IModel, SpriteSheetModel);


ResourceType IEngineResource<Asset::AssetManager>::type = ResourceType::AssetManager;

namespace Asset
{

	void AssetManager::saveModOrderFile()
	{
		std::ofstream file("Data\\ModLoadOrder.xml");
		{
			cereal::XMLOutputArchive ar(file);
			ar(modLoader);
		}
	}


#ifdef _DEBUG

	void testSave()
	{
		//GameObject *test = new GameObject();
		//test->tag = "debug";
		//test->name = "TestPlatform";
		//test->GetComponent<Component::Transform>()->position.x = 300;
		//test->GetComponent<Component::Transform>()->position.y = 316;
		//test->AddComponent(new Component::HitboxComponent(0, 0, 40, 40));
		//test->AddComponent(new Component::RenderComponent("testCutHalf.png"));
		//Prefab pref(test);
		//pref.ID = 1;
		////zone.addGameObject(test);

		//GameObject *ground = new GameObject();
		//ground->name = "da kewl ground";
		//ground->tag = "debug";
		//ground->GetComponent<Component::Transform>()->position.x = 400;
		//ground->GetComponent<Component::Transform>()->position.y = 550;
		//ground->AddComponent(new Component::HitboxComponent(0, 0, 40, 40));
		//ground->AddComponent(new Component::RenderComponent("ground.marker_1.png"));
		//ground->GetComponent<Component::RenderComponent>()->sprite.setScale(2, 1);
		//ground->GetComponent<Component::HitboxComponent>()->bounding.size.x = ground->GetComponent<Component::HitboxComponent>()->bounding.size.x * 2;
		//Prefab pref2(ground);
		//pref2.ID = 2;

		////zone.addGameObject(ground);

		//GameObject *target = new GameObject();
		//target->name = "testTarget";
		//target->tag = "debug";
		//target->GetComponent<Component::Transform>()->position.x = 580;
		//target->GetComponent<Component::Transform>()->position.y = 480;
		//target->AddComponent(new Component::HitboxComponent(0, 0, 40, 40));
		//target->AddComponent(new Component::RenderComponent("testTarget.png"));

		////target->AddComponent(new Component::DialogComponent(2));
		//////target->GetComponent<DialogComponent>()->msg->iconName = "TestDialogChat.png";
		////target->GetComponent<Component::DialogComponent>()->dialogMessage = "Senpai!\nNotice me!";
		////target->GetComponent<Component::DialogComponent>()->position.x = 64;
		////target->GetComponent<Component::DialogComponent>()->position.y = 80;
		////target->GetComponent<DialogComponent>()->msg->setOffset(10, 5);

		//Prefab pref3(target);
		//pref3.ID = 3;


		//std::ofstream index("TestSave.xml.index", std::ios::binary);
		//std::ofstream file("TestSave.xml", std::ios::binary);
		//{
		//	DatabaseIndex ind;
		//	cereal::BinaryOutputArchive mainAr(file);
		//	cereal::BinaryOutputArchive indexAr(index);
		//	//ind.flags = "-";
		//	//ind.ID = zone.ID;
		//	//ind.type = "Zone";
		//	//ind.row = file.tellp();
		//	//indexAr(ind);
		//	//mainAr(zone);

		//	ind.ID = pref.ID;
		//	ind.type = DatabaseIndex::ObjectTypeEnum::Prefab;
		//	ind.row = file.tellp();
		//	indexAr(ind);
		//	mainAr(pref);

		//	ind.ID = pref2.ID;
		//	ind.type = DatabaseIndex::ObjectTypeEnum::Prefab;
		//	ind.row = file.tellp();
		//	indexAr(ind);
		//	mainAr(pref2);

		//	ind.ID = pref3.ID;
		//	ind.type = DatabaseIndex::ObjectTypeEnum::Prefab;
		//	ind.row = file.tellp();
		//	indexAr(ind);
		//	mainAr(pref3);

		//	ind.ID = 0xffffffff;
		//	ind.type = DatabaseIndex::ObjectTypeEnum::EoF;
		//	ind.row = file.tellp();
		//	ind.flags = DatabaseIndex::ObjectFlag::EoF;
		//	indexAr(ind);
		//}
		//delete test;
		//test = 0;
		//delete target;
		//target = 0;
		//delete ground;
		//ground = 0;
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


	AssetManager::AssetManager() : openedMod("<Not Set>"), prefabRequestor(DatabaseIndex::ObjectTypeEnum::Prefab), modelRequestor(DatabaseIndex::ObjectTypeEnum::Model),
		modLoader(), textureloader(), zoneRequestor(DatabaseIndex::ObjectTypeEnum::Zone), textureMapRequestor(DatabaseIndex::ObjectTypeEnum::TextureMap),
		intRequestor(DatabaseIndex::ObjectTypeEnum::PrimitiveInt), doubleRequestor(DatabaseIndex::ObjectTypeEnum::PrimitiveDouble), stringRequestor(DatabaseIndex::ObjectTypeEnum::PrimitiveString),
		stringVectorRequestor(DatabaseIndex::ObjectTypeEnum::StringList), elementRequestor(DatabaseIndex::ObjectTypeEnum::Element), lang(DatabaseIndex::ObjectTypeEnum::Language)
	{
	}


	Requestor<Asset::Prefab>& AssetManager::getPrefabRequester()
	{
		return prefabRequestor;
	}

	Requestor<IModel*>& AssetManager::getModelRequester()
	{
		return modelRequestor;
	}

	Requestor<Database::Zone>& AssetManager::getZoneRequester()
	{
		return zoneRequestor;
	}

	Requestor<TextureMap>& AssetManager::getTextureMapRequester()
	{
		return textureMapRequestor;
	}

	Requestor<PrimitiveSaveable<int>>& AssetManager::getIntRequestor()
	{
		return intRequestor;
	}

	Requestor<PrimitiveSaveable<double>>& AssetManager::getDoubleRequestor()
	{
		return doubleRequestor;
	}

	Requestor<PrimitiveSaveable<Core::String>>& AssetManager::getStringRequestor()
	{
		return stringRequestor;
	}

	Requestor<PrimitiveSaveable<std::vector<Core::String>>>& AssetManager::getStringVectorRequestor()
	{
		return stringVectorRequestor;
	}

	Requestor<Element>& AssetManager::getElementRequestor()
	{
		return elementRequestor;
	}

	Language & AssetManager::getLanguage()
	{
		return lang.request("BUILTIN", 0);
	}

	ModLoader & AssetManager::getModLoader()
	{
		return modLoader;
	}

	void AssetManager::saveGameDatabase(
		std::string filename,
		ModHeader& modhdr)
		//,
		//std::map<std::pair<std::string, size_t>, Items::Item*>& editorAllItems,
		//std::map<std::pair<std::string, size_t>, Quests::Quest>& EditorAllQuests)
	{
		std::ofstream file("Data//" + filename, std::ios::binary);
		filename.append(".index");
		std::ofstream index("Data//" + filename, std::ios::binary);
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

			prefabRequestor.save(ind, file, indexAr, mainAr);
			modelRequestor.save(ind, file, indexAr, mainAr);
			zoneRequestor.save(ind, file, indexAr, mainAr);
			textureMapRequestor.save(ind, file, indexAr, mainAr);
			intRequestor.save(ind, file, indexAr, mainAr);
			doubleRequestor.save(ind, file, indexAr, mainAr);
			stringRequestor.save(ind, file, indexAr, mainAr);
			stringVectorRequestor.save(ind, file, indexAr, mainAr);
			elementRequestor.save(ind, file, indexAr, mainAr);
			lang.save(ind, file, indexAr, mainAr);

			ind.ID = 0xFFFFFFFF;
			ind.type = DatabaseIndex::ObjectTypeEnum::EoF;
			ind.row = file.tellp();
			ind.flags = DatabaseIndex::ObjectFlag::EoF;
			indexAr(ind);
		}
		file.close();
		index.close();
	}

	void AssetManager::loadAllEditorVariables()
	{
#ifdef _EDITOR_
		prefabRequestor.editorLoadAll(&Editor::onObjectLoaded);
		modelRequestor.editorLoadAll(&Editor::onObjectLoaded);
		zoneRequestor.editorLoadAll(&Editor::onObjectLoaded);
		textureMapRequestor.editorLoadAll(&Editor::onObjectLoaded);
		intRequestor.editorLoadAll(&Editor::onObjectLoaded);
		doubleRequestor.editorLoadAll(&Editor::onObjectLoaded);
		stringRequestor.editorLoadAll(&Editor::onObjectLoaded);
		stringVectorRequestor.editorLoadAll(&Editor::onObjectLoaded);
		lang.editorLoadAll(&Editor::onObjectLoaded);
#endif	
		//	LoadAllTextureMaps(Engine::ModelContainer);
		//	LoadAllPrefabs(Editor::addons.myWorldManager.editorPrefabContainer);
		//	LoadAllZones(Editor::addons.myWorldManager.EditorAllZones);
	}

	bool AssetManager::loadModHeader(Core::String modName, ModHeader & myheader)
	{
		bool eof = false;
		DatabaseIndex ind;
		std::ifstream index("Data//" + modName + ".index", std::ios::binary);
		std::ifstream database("Data//" + modName, std::ios::binary);

		if (!index.is_open())
			Engine::GetModule<OneLogger>().Critical("Unable to open mod index file [" + modName + ".index]", __FILE__, __LINE__);
		else if (!database.is_open())
			Engine::GetModule<OneLogger>().Critical("Unable to open database file [" + modName + "]", __FILE__, __LINE__);
		else
		{
			cereal::BinaryInputArchive ar(index);
			{
				while (!eof)
				{
					ar(ind);
					if (ind.type == DatabaseIndex::ObjectTypeEnum::Header)
					{
						database.seekg(ind.row);
						cereal::BinaryInputArchive headerLoad(database);
						headerLoad(myheader);
						index.close();
						database.close();
						return true;
					}
					else if (ind.flags == DatabaseIndex::ObjectFlag::EoF)
						eof = true;
				}
			}
		}
		Engine::GetModule<OneLogger>().Critical("Unable to load mod header for mod [" + modName + "]", __FILE__, __LINE__);
		return false;
	}
	bool AssetManager::loadModOrderFile()
	{
		std::ifstream file("Data\\ModLoadOrder.xml");
		if (file.is_open())
		{
			cereal::XMLInputArchive ar(file);
			ar(modLoader);
			return true;
		}
		Engine::GetModule<OneLogger>().Critical("Unable to load mod load order file [ModLoadOrder.xml]", __FILE__, __LINE__);
		return false;
	}
}