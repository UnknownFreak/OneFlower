#ifndef _UNITTESTS_

#include <iostream>

#include <Main/GameEntry.hpp>

#include <engine/runMode.hpp>
#include <engine/engine.hpp>

#include <Module/BuildMode.hpp>
#include <logger/Logger.hpp>
#include <logger/streams/ConsoleStream.hpp>

#include <Input/InputHandler.hpp>

#include <file/Handler.hpp>
#include <file/Loader.hpp>

#include <module/resource/TextureLoader.hpp>
#include <module/resource/MeshLoader.hpp>
#include <module/resource/ShaderLoader.hpp>

#include <courier/courier.hpp>

#include "RegisterArchiveDefaults.hpp"

static of::common::String to_string(const of::module::EngineResourceType state)
{
	switch (state)
	{
		// Console
	case of::module::EngineResourceType::Console: return "Console";
		// Asset
	case of::module::EngineResourceType::FileHandler: return "FileHandler";
		// Engine
	case of::module::EngineResourceType::Graphics: return "Graphics";
		// Unused
	case of::module::EngineResourceType::WorldManagerAddon: return "WorldManagerAddon";
	case of::module::EngineResourceType::GameVariableMapping: return "GameVariableMapping";
	}
	return "<undefined>" + std::to_string((int)state);
}

// todo change into a helper function available as include rather than do it in main
// move to engine.hpp -> of::engine::init()
static volatile void initializeSystems()
{
	auto& logger = of::logger::get();
	logger.Info("Initializing Engine");
	for (auto& str : Engine::GetBuildMode().toLogString())
		logger.Info(str);

	of::engine::initialize();
	
	auto& mainModule = logger.getLogger("Main");

	mainModule.Info("Initializing Modules group: Asset Management");
	mainModule.Info("Initializing Module: " + to_string(of::engine::GetModule<of::file::Handler>().type));

	mainModule.Info("Initializing Modules group: Engine");
	mainModule.Info("Initializing Modules group: Messaging");
	of::courier::init();

	mainModule.Info("Finished initializing engine ");

	registerArchiveDefaults();
}


class EngineLogger : public swizzle::core::LogDevice
{
	typedef of::logger::streams::ConsoleLogStream CLS;
	of::logger::ModuleLogger& stream;

public:
	inline EngineLogger() : stream(of::logger::get().getLogger<CLS>("Swizzle", std::make_shared<CLS>()))
	{
	}

	// Inherited via LogDevice
	virtual void logMessage(const SwChar* messageType, const SwChar* message) override
	{
		of::common::String tType = messageType;
		stream.EngineLogging(tType, message);
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
	of::logger::init();
	of::engine::setRunMode(of::engine::RunMode::EDITOR);
	of::engine::lockRunMode();

	// Parse argv;
	initializeSystems();
	EngineLogger logger;
	sw::core::AddLogger(&logger);

	GameEntry g;
	const int return_value = g.Run();
	sw::core::RemoveLogger(&logger);

	of::object::get().unloadAll();

	of::engine::shutdown();
	of::engine::Dispose();
	of::courier::shutdown();

	of::logger::shutdown();

	return return_value;
}
#pragma warning(default: 28251)

#endif
