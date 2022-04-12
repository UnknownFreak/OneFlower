#include "Manager.hpp"

//#include <Core/Component/BaseComponent.hpp>
//#include <Core\Component\TransformComponent.hpp>
//#include <Core\Component\GameObject.h>
//#include <Graphic\Component\RenderComponent.h>
//#include <Physics\Component\HitboxComponent.hpp>
//
#include <File/Archive/DatabaseIndex.hpp>
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


Enums::EngineResourceType Interfaces::IEngineResource<File::Asset::Manager>::type = Enums::EngineResourceType::AssetManager;

namespace File::Asset
{

	void Manager::saveModOrderFile()
	{
		std::ofstream file("Data\\ModLoadOrder.xml");
		{
			cereal::XMLOutputArchive ar(file);
			ar(modLoader);
		}
	}

	Manager::Manager() : 
		openedMod("<Not Set>"),
		modLoader(Engine::GetModule<File::Mod::Loader>()),
		lang(Enums::ObjectType::Language)
	{
	}

	void Manager::saveGameDatabase(
		std::string filename,
		File::Mod::Header& modhdr)
		//,
		//std::map<std::pair<std::string, size_t>, Items::Item*>& editorAllItems,
		//std::map<std::pair<std::string, size_t>, Quests::Quest>& EditorAllQuests)
	{
		std::ofstream file(Core::dataPath + filename, std::ios::binary | std::ios::out);
		filename.append(".index");
		std::ofstream index(Core::dataPath + filename, std::ios::binary | std::ios::out);
		{

			File::Archive::DatabaseIndex ind;
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

	Language::LanguageRequestor & Manager::getLanguage()
	{
		return lang.request(Core::Builtin, Core::uuid::nil());
	}

	File::Mod::Loader & Manager::getModLoader()
	{
		return modLoader;
	}

	void Manager::loadAllEditorVariables()
	{
#ifdef _EDITOR_
		requestor.editorLoadAll(&Editor::onObjectLoaded);
		lang.editorLoadAll(&Editor::onObjectLoaded);
#endif	
		//	LoadAllTextureMaps(Engine::ModelContainer);
		//	LoadAllPrefabs(Editor::addons.myWorldManager.editorPrefabContainer);
		//	LoadAllZones(Editor::addons.myWorldManager.EditorAllZones);
	}

	std::map<Core::String, Language::TranslationString> Manager::loadLanguages(const std::vector<Core::String>& languageFiles)
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

	void Manager::saveLanguages(const Language::LanguageRequestor& languageRequestor)
	{
		for(std::pair<Core::String, Language::TranslationString> x : languageRequestor.languages)
			saveLanguageFile(x.first, x.second);
	}

	void Manager::saveLanguageFile(Core::String & filename, Language::TranslationString & langHeader)
	{
		std::ofstream file(Core::langPath + filename, std::ios::binary);
		filename.append(".index");
		std::ofstream index(Core::langPath + filename, std::ios::binary);
		{
			File::Archive::DatabaseIndex ind;
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
	bool Manager::loadModOrderFile()
	{
		auto& logger = Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("File::Asset::Manager");
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