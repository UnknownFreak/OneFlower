#ifndef _UNITTESTS_
// Windows.h has to be included first. Due to how clr works (only affects editormode).
#ifdef _EDITOR_
#include <Windows.h>
#endif
//#include <Windows.h>

#include <iostream>

#include <Main/GameEntry.hpp>

#include <Module/EngineModuleManager.hpp>
#include <Module/BuildMode.hpp>
#include <Module/Logger/OneLogger.hpp>
#include <Input/InputHandler.hpp>
#include <File/Asset/Manager.hpp>
#include <File/Resource/TextureLoader.hpp>
#include <File/Resource/MeshLoader.hpp>
#include <File/Resource/ShaderLoader.hpp>
#include <File/Mod/ModLoader.hpp>
#include <File/GameConfig.hpp>
#include <Object/ObjectInstanceHandler.hpp>

Core::String to_string(const Enums::EngineResourceType& state)
{
	switch (state)
	{
		// Logger
	case Enums::EngineResourceType::Logger: return "Logger";
		// Console
	case Enums::EngineResourceType::Console: return "Console";
		// Core
	case Enums::EngineResourceType::StringConverter: return "StringConverter";
	case Enums::EngineResourceType::Globals: return "Globals";
	case Enums::EngineResourceType::Time: return "Time";
	case Enums::EngineResourceType::Settings: return "EngineSettings";
		// Asset
	case Enums::EngineResourceType::TextureLoader: return "TextureLoader";
	case Enums::EngineResourceType::MeshLoader: return "MeshLoader";
	case Enums::EngineResourceType::ShaderLoader: return "ShaderLoader";
	case Enums::EngineResourceType::AssetManager: return "AssetManager";
	case Enums::EngineResourceType::SpriterContainer: return "SpriterContainer";
	case Enums::EngineResourceType::ObjectInstanceHandler: return "ObjectInstanceHandler";
		// Engine
	case Enums::EngineResourceType::ModLoader: return "ModLoader";
	case Enums::EngineResourceType::Input: return "Input";
	case Enums::EngineResourceType::Graphics: return "Graphics";
	case Enums::EngineResourceType::Physics: return "Physics";
	case Enums::EngineResourceType::UIHandler: return "Console";

		// Unused
	case Enums::EngineResourceType::WorldManager: return "WorldManager";
	case Enums::EngineResourceType::WorldManagerAddon: return "WorldManagerAddon";
	case Enums::EngineResourceType::GameVariableMapping: return "GameVariableMapping";
	}
	return "";
}

volatile void initializeSystems()
{
	auto& logger = Engine::GetModule<EngineModule::Logger::OneLogger>();
	logger.Info("Initializing Engine");
	for (auto& str : Engine::GetBuildMode().toLogString())
		logger.Info(str);

	logger.Info("Initializing Module: " + to_string(Engine::GetModule<EngineModule::GameConfig>().type));

	auto mainModule = logger.getLogger("Main");

	mainModule.Info("Initializing Module: " + to_string(Engine::GetModule<Console>().type));
	mainModule.Info("Initializing Modules group: Core");
	mainModule.Info("Initializing Module: " + to_string(Engine::GetModule<Core::StringConverter>().type));
	mainModule.Info("Initializing Module: " + to_string(Engine::GetModule<Globals>().type));
	mainModule.Info("Initializing Module: " + to_string(Engine::GetModule<EngineModule::Time>().type));

	mainModule.Info("Initializing Modules group: Asset Management");
	mainModule.Info("Initializing Module: " + to_string(Engine::GetModule<File::Resource::Texture::Loader>().type));
	mainModule.Info("Initializing Module: " + to_string(Engine::GetModule<File::Resource::Mesh::Loader>().type));
	mainModule.Info("Initializing Module: " + to_string(Engine::GetModule<File::Resource::Shader::Loader>().type));
	mainModule.Info("Initializing Module: " + to_string(Engine::GetModule<File::Asset::Manager>().type));
	mainModule.Info("Initializing Module: " + to_string(Engine::GetModule<EngineModule::ObjectInstanceHandler>().type));

	mainModule.Info("Initializing Modules group: Engine");
	mainModule.Info("Initializing Module: " + to_string(Engine::GetModule<File::Mod::Loader>().type));
	mainModule.Info("Initializing Module: " + to_string(Engine::GetModule<Input::InputHandler>().type));
	mainModule.Info("Initializing Module: " + to_string(Engine::GetModule<Graphics::RenderWindow>().type));
	mainModule.Info("Initializing Module: " + to_string(Engine::GetModule<Graphics::UI::UIHandler>().type));
	mainModule.Info("Initializing Module: " + to_string(Engine::GetModule<Physics::PhysicsEngine>().type));

	mainModule.Info("Finished initializing engine ");
}

class EngineLogger : public swizzle::core::LogDevice
{
	// Inherited via LogDevice
	virtual void logMessage(const SwChar* messageType, const SwChar* message) override
	{
		//Engine::GetModule<EngineModule::Logger::OneLogger>().Always(messageType, ": ", message);
		printf("%s: %s\n", messageType, message);
	}

	EngineLogger& operator=(const EngineLogger& other)
	{
		// Guard self assignment
		if (this == &other)
			return *this;
	}

};


#ifdef _EDITOR_
[System::STAThread]
#endif
#pragma warning(disable: 28251)
#ifdef  _DEBUG
	int main(int , char* )
#else //  _DEBUG
	int __stdcall WinMain(HINSTANCE /*hInstance*/, HINSTANCE /*prevInstance*/, LPSTR /*lpCmnLine*/, int /*nShowCmd*/)
#endif
{
	initializeSystems();
	EngineLogger logger;
	sw::core::AddLogger(&logger);

	GameEntry g;
	const int return_value = g.Run();
	sw::core::RemoveLogger(&logger);

	Engine::Dispose();

#ifdef _EDITOR_
	exit(return_value);
#else
	return return_value;
#endif
}
#pragma warning(default: 28251)

#endif
