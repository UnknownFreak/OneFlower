#include "AssetManagerCore.hpp"

//#include <Core/Component/BaseComponent.hpp>
//#include <Core\Component\TransformComponent.hpp>
//#include <Core\Component\GameObject.h>
//#include <Graphic\Component\RenderComponent.h>
//#include <Physics\Component\HitboxComponent.hpp>
//
#include "DatabaseIndex.hpp"
#include <fstream>

#include <cereal\archives\binary.hpp>
//#include <cereal\archives\xml.hpp>
#include <cereal\types\string.hpp>
#include <cereal\types\polymorphic.hpp>
#include <cereal\types\map.hpp>
#include <cereal\types\unordered_map.hpp>
#include <cereal\types\unordered_set.hpp>
#include <cereal\types\memory.hpp>
#include <cereal\access.hpp>

//#include <Graphic\World\WorldManager.hpp>
//#include <Graphic\World\Zone.hpp>
//
//#include <Model\TextureMap.hpp>
//#include <Model\SpriteSheetAnimation.hpp>
//
//#include <Model\IModel.hpp>
//#include <Model\StaticModel.hpp>
//#include <Model\SpriteSheetModel.hpp>

#ifdef _EDITOR_
#include <Editor/EditorEvents.hpp>
#endif

//CEREAL_REGISTER_TYPE(Component::Base);
////CEREAL_REGISTER_TYPE(IBaseComponent<Component::DialogComponent>)
//CEREAL_REGISTER_TYPE(Component::HitboxComponent)
////CEREAL_REGISTER_TYPE(IBaseComponent<Component::OverheadComponent>)
////CEREAL_REGISTER_TYPE(IBaseComponent<Component::PlayerComponent> )
//CEREAL_REGISTER_TYPE(Component::RenderComponent)
////CEREAL_REGISTER_TYPE(IBaseComponent<Component::RigidComponent> )
////CEREAL_REGISTER_TYPE(IBaseComponent<Component::Timer>)
//CEREAL_REGISTER_TYPE(Component::Transform)
//
//CEREAL_REGISTER_TYPE(StaticModel);
//
////CEREAL_REGISTER_TYPE_WITH_NAME(Component::DialogComponent, "Dialog")
////CEREAL_REGISTER_TYPE_WITH_NAME(Component::HitboxComponent, "Hitbox")
////CEREAL_REGISTER_TYPE_WITH_NAME(Component::OverheadComponent, "Overhead")
////CEREAL_REGISTER_TYPE_WITH_NAME(Component::PlayerComponent, "Player")
////CEREAL_REGISTER_TYPE_WITH_NAME(Component::RenderComponent, "Render")
////CEREAL_REGISTER_TYPE_WITH_NAME(Component::RigidComponent, "Rigid")
////CEREAL_REGISTER_TYPE_WITH_NAME(Component::Timer, "Timer")
////CEREAL_REGISTER_TYPE_WITH_NAME(Component::Transform, "Transform")
//
////CEREAL_REGISTER_POLYMORPHIC_RELATION(Component::Base, Component::DialogComponent)
//CEREAL_REGISTER_POLYMORPHIC_RELATION(Component::Base, Component::HitboxComponent)
////CEREAL_REGISTER_POLYMORPHIC_RELATION(Component::Base, Component::OverheadComponent)
////CEREAL_REGISTER_POLYMORPHIC_RELATION(Component::Base, Component::PlayerComponent)
//CEREAL_REGISTER_POLYMORPHIC_RELATION(Component::Base, Component::RenderComponent)
////CEREAL_REGISTER_POLYMORPHIC_RELATION(Component::Base, Component::RigidComponent)
////CEREAL_REGISTER_POLYMORPHIC_RELATION(Component::Base, Component::Timer)
//CEREAL_REGISTER_POLYMORPHIC_RELATION(Component::Base, Component::Transform)
//
//CEREAL_REGISTER_POLYMORPHIC_RELATION(IModel, StaticModel);
//CEREAL_REGISTER_POLYMORPHIC_RELATION(IModel, SpriteSheetModel);


Enums::EngineResourceType Interfaces::IEngineResource<Asset::AssetManager>::type = Enums::EngineResourceType::AssetManager;

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
		//	ind.type = Enums::ObjectType::Prefab;
		//	ind.row = file.tellp();
		//	indexAr(ind);
		//	mainAr(pref);

		//	ind.ID = pref2.ID;
		//	ind.type = Enums::ObjectType::Prefab;
		//	ind.row = file.tellp();
		//	indexAr(ind);
		//	mainAr(pref2);

		//	ind.ID = pref3.ID;
		//	ind.type = Enums::ObjectType::Prefab;
		//	ind.row = file.tellp();
		//	indexAr(ind);
		//	mainAr(pref3);

		//	ind.ID = 0xffffffff;
		//	ind.type = Enums::ObjectType::EoF;
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
		//Prefab a;
		//Prefab b;
		//Prefab c;
		//std::ifstream index("TestSave.xml.index", std::ios::binary);
		//std::ifstream file("TestSave.xml", std::ios::binary);
		//{
		//	DatabaseIndex ind;
		//	cereal::BinaryInputArchive mainAr(file);
		//	cereal::BinaryInputArchive indexAr(index);
		//	mainAr(a);
		//	mainAr(b);
		//	mainAr(c);
		//}
	}
#endif

	AssetManager::AssetManager() : 
		openedMod("<Not Set>"),
		modLoader(Engine::GetModule<File::Mod::ModLoader>()),
		lang(Enums::ObjectType::Language)
	{
	}

	void AssetManager::saveGameDatabase(
		std::string filename,
		File::Mod::ModHeader& modhdr)
		//,
		//std::map<std::pair<std::string, size_t>, Items::Item*>& editorAllItems,
		//std::map<std::pair<std::string, size_t>, Quests::Quest>& EditorAllQuests)
	{
		std::ofstream file(Core::dataPath + filename, std::ios::binary | std::ios::out);
		filename.append(".index");
		std::ofstream index(Core::dataPath + filename, std::ios::binary | std::ios::out);
		{

			DatabaseIndex ind;
			cereal::BinaryOutputArchive mainAr(file);
			cereal::BinaryOutputArchive indexAr(index);
			ind.flags = Enums::ObjectFlag::NoFlag;
			ind.ID = Core::uuid::nil();
			ind.type = Enums::ObjectType::Header;
			ind.modFile = modhdr.name;
			ind.row = file.tellp();
			indexAr(ind);
			mainAr(modhdr);

			lang.save(ind, file, indexAr, mainAr);
			requestor.save(ind, file, indexAr, mainAr);

			ind.ID = Core::uuid::nil();
			ind.type = Enums::ObjectType::EoF;
			ind.row = file.tellp();
			ind.flags = Enums::ObjectFlag::EoF;
			indexAr(ind);
		}
		file.close();
		index.close();
	}

	Language::LanguageRequestor & AssetManager::getLanguage()
	{
		return lang.request(Core::Builtin, Core::uuid::nil());
	}

	File::Mod::ModLoader & AssetManager::getModLoader()
	{
		return modLoader;
	}

	void AssetManager::loadAllEditorVariables()
	{
#ifdef _EDITOR_
		requestor.editorLoadAll(&Editor::onObjectLoaded);
		lang.editorLoadAll(&Editor::onObjectLoaded);
#endif	
		//	LoadAllTextureMaps(Engine::ModelContainer);
		//	LoadAllPrefabs(Editor::addons.myWorldManager.editorPrefabContainer);
		//	LoadAllZones(Editor::addons.myWorldManager.EditorAllZones);
	}

	std::map<Core::String, Language::TranslationString> AssetManager::loadLanguages(const std::vector<Core::String>& languageFiles)
	{
		std::map<Core::String, Language::TranslationString> tmp;

		Language::TranslationString translationStr;
		for(Core::String var : languageFiles)
		{
			loadModHeader("Lang//" + var, translationStr);
			tmp.emplace(var, translationStr);
		}
		return tmp;
	}

	void AssetManager::saveLanguages(const Language::LanguageRequestor& languageRequestor)
	{
		for(std::pair<Core::String, Language::TranslationString> x : languageRequestor.languages)
			saveLanguageFile(x.first, x.second);
	}

	void AssetManager::saveLanguageFile(Core::String & filename, Language::TranslationString & langHeader)
	{
		std::ofstream file(Core::langPath + filename, std::ios::binary);
		filename.append(".index");
		std::ofstream index(Core::langPath + filename, std::ios::binary);
		{
			DatabaseIndex ind;
			cereal::BinaryOutputArchive mainAr(file);
			cereal::BinaryOutputArchive indexAr(index);
			ind.flags = Enums::ObjectFlag::NoFlag;
			ind.ID = Core::uuid::nil();
			ind.type = Enums::ObjectType::Header;
			ind.modFile = "notUsed";
			ind.row = file.tellp();
			indexAr(ind);
			mainAr(langHeader);
			langHeader.stringList.save(ind, file, indexAr, mainAr);

			ind.ID = Core::uuid::nil();
			ind.type = Enums::ObjectType::EoF;
			ind.row = file.tellp();
			ind.flags = Enums::ObjectFlag::EoF;
			indexAr(ind);
		}
	}

#pragma warning(disable: 6262)
	bool AssetManager::loadModOrderFile()
	{
		auto& logger = Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("Asset::AssetManager");
		std::ifstream file("Data\\ModLoadOrder.xml");
		if (file.is_open())
		{
			cereal::XMLInputArchive ar(file);
			ar(modLoader);
			return true;
		}
		logger.Critical("Unable to load mod load order file [ModLoadOrder.xml]", logger.fileInfo(__FILE__, __LINE__));
		return false;
	}
#pragma warning(default: 6262)

}