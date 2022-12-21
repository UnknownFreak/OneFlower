#ifndef _UNITTESTS_

#include <iostream>

#include <Main/GameEntry.hpp>

#include <Module/ModuleManager.hpp>

#include <Module/BuildMode.hpp>
#include <Module/Logger/OneLogger.hpp>
#include <Input/InputHandler.hpp>

#include <file/Handler.hpp>
#include <file/Loader.hpp>

#include <module/resource/TextureLoader.hpp>
#include <module/resource/MeshLoader.hpp>
#include <module/resource/ShaderLoader.hpp>
#include <File/GameConfig.hpp>
#include <module/ObjectInstanceHandler.hpp>

#include "RegisterArchiveDefaults.hpp"

of::common::String to_string(const of::module::EngineResourceType& state)
{
	switch (state)
	{
		// Logger
	case of::module::EngineResourceType::Logger: return "Logger";
		// Console
	case of::module::EngineResourceType::Console: return "Console";
		// Core
	case of::module::EngineResourceType::Globals: return "Globals";
	case of::module::EngineResourceType::Time: return "Time";
	case of::module::EngineResourceType::Settings: return "EngineSettings";
		// Asset
	case of::module::EngineResourceType::TextureLoader: return "TextureLoader";
	case of::module::EngineResourceType::MeshLoader: return "MeshLoader";
	case of::module::EngineResourceType::ShaderLoader: return "ShaderLoader";
	case of::module::EngineResourceType::AssetManager: return "AssetManager";
	case of::module::EngineResourceType::ObjectInstanceHandler: return "ObjectInstanceHandler";
		// Engine
	case of::module::EngineResourceType::Loader: return "ModLoader";
	case of::module::EngineResourceType::Input: return "Input";
	case of::module::EngineResourceType::Graphics: return "Graphics";
	case of::module::EngineResourceType::Physics: return "Physics";
	case of::module::EngineResourceType::UIHandler: return "Console";

		// Unused
	case of::module::EngineResourceType::WorldManager: return "WorldManager";
	case of::module::EngineResourceType::WorldManagerAddon: return "WorldManagerAddon";
	case of::module::EngineResourceType::GameVariableMapping: return "GameVariableMapping";
	}
	return "";
}

volatile void initializeSystems()
{
	auto& logger = of::engine::GetModule<of::module::logger::OneLogger>();
	logger.Info("Initializing Engine");
	for (auto& str : Engine::GetBuildMode().toLogString())
		logger.Info(str);

	logger.Info("Initializing Module: " + to_string(of::engine::GetModule<EngineModule::GameConfig>().type));

	auto mainModule = logger.getLogger("Main");

	mainModule.Info("Initializing Module: " + to_string(of::engine::GetModule<Console>().type));
	mainModule.Info("Initializing Modules group: Core");
	mainModule.Info("Initializing Module: " + to_string(of::engine::GetModule<Globals>().type));
	mainModule.Info("Initializing Module: " + to_string(of::engine::GetModule<EngineModule::Time>().type));

	mainModule.Info("Initializing Modules group: Asset Management");
	mainModule.Info("Initializing Module: " + to_string(of::engine::GetModule<of::module::texture::Loader>().type));
	mainModule.Info("Initializing Module: " + to_string(of::engine::GetModule<of::module::mesh::Loader>().type));
	mainModule.Info("Initializing Module: " + to_string(of::engine::GetModule<of::module::shader::Loader>().type));
	mainModule.Info("Initializing Module: " + to_string(of::engine::GetModule<of::file::Handler>().type));
	mainModule.Info("Initializing Module: " + to_string(of::engine::GetModule<of::module::ObjectInstanceHandler>().type));

	mainModule.Info("Initializing Modules group: Engine");
	mainModule.Info("Initializing Module: " + to_string(of::engine::GetModule<of::file::Loader>().type));
	mainModule.Info("Initializing Module: " + to_string(of::engine::GetModule<Input::InputHandler>().type));
	mainModule.Info("Initializing Module: " + to_string(of::engine::GetModule<Graphics::RenderWindow>().type));
	mainModule.Info("Initializing Module: " + to_string(of::engine::GetModule<Graphics::UI::UIHandler>().type));

	mainModule.Info("Finished initializing engine ");

	registerArchiveDefaults();
}

class EngineLogger : public swizzle::core::LogDevice
{
	// Inherited via LogDevice
	virtual void logMessage(const SwChar* messageType, const SwChar* message) override
	{
		of::common::String tType = messageType;
		of::engine::GetModule<of::module::logger::OneLogger>().EngineLogging(tType, message);
		printf("%s: %s\n", messageType, message);
	}

	EngineLogger& operator=(const EngineLogger& other)
	{
		// Guard self assignment
		if (this == &other)
			return *this;
	}

};


#pragma warning(disable: 28251)
#ifdef  _DEBUG
	int main(int c, char** argv )
#else //  _DEBUG
	int __stdcall WinMain(HINSTANCE /*hInstance*/, HINSTANCE /*prevInstance*/, LPSTR /*lpCmnLine*/, int /*nShowCmd*/)
#endif
{
		c; argv;
	Engine::GetBuildMode().setEditorMode();
	// Parse argv;
	initializeSystems();
	EngineLogger logger;
	sw::core::AddLogger(&logger);

	GameEntry g;
	const int return_value = g.Run();
	sw::core::RemoveLogger(&logger);

	of::engine::Dispose();

	return return_value;
}
#pragma warning(default: 28251)

#endif
