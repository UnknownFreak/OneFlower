#include "GameConfig.hpp"

#include <Module/Logger/OneLogger.hpp>

of::module::EngineResourceType of::module::interface::IEngineResource<EngineModule::GameConfig>::type = of::module::EngineResourceType::Settings;

EngineModule::GameConfig::GameConfig() : configName("gameConfig.cfg"), videoModes({}), antialiasing(32), framerate(0), parser(configName)
{
	defaultMode = videoMode = {1920, 1080};
	load();
}

EngineModule::GameConfig::~GameConfig()
{
	save();
}

of::module::EngineResourceType& EngineModule::GameConfig::getType() const
{
	return type;
}

void EngineModule::GameConfig::save()
{
	parser.put("window", "height", videoMode.second);
	parser.put("window", "width", videoMode.first);
	parser.put("window", "framerate", framerate);
	parser.put("window", "aa", antialiasing);
	parser.put("window", "fullscreen", fullscreen);
	parser.save();
}

void EngineModule::GameConfig::load()
{
	parser.load();
	videoMode.second = parser.get("window", "height", defaultMode.second);
	videoMode.first = parser.get("window", "width", defaultMode.first);
	framerate = parser.get("window", "framerate", 0);
	antialiasing = parser.get("window", "aa", 32);
	fullscreen = parser.get("window", "fullscreen", false);
	logLevel = of::module::logger::fromString(parser.get("logger", "core.level", of::module::logger::to_string(of::module::logger::LogLevel::INFO, false)));
	physicsThreadCount = parser.get("physics", "threadCount", 4);
	physicsForceSingleThread = parser.get("physics", "forceSingleThread", false);
	physicsAdaptiveRegions = parser.get("physics", "adaptiveRegions", true);

	of::engine::GetModule<of::module::logger::OneLogger>().setLogLevel(logLevel);
	for (auto& logger_level : parser.get("logger").values)
	{
		if (logger_level.first != "core.level")
			of::engine::GetModule<of::module::logger::OneLogger>().getLogger(logger_level.first).setLogLevel(of::module::logger::fromString(logger_level.second));
	}

	configLoaded = true;
}

void EngineModule::GameConfig::setVideoMode(const size_t& index)
{
	videoMode = videoModes[index];
	save();
}

void EngineModule::GameConfig::toggleFullscreen()
{
	fullscreen = !fullscreen;
	save();
}

void EngineModule::GameConfig::setAntiAliasing(const unsigned& aa)
{
	antialiasing = aa;
	save();
}

unsigned EngineModule::GameConfig::getAntiAliasing() const
{
	return antialiasing;
}

of::module::logger::LogLevel EngineModule::GameConfig::getCurrentLogLevel() const
{
	return logLevel;
}

of::module::logger::LogLevel EngineModule::GameConfig::getModuleLogLevel(const of::common::String& module)
{
	if (configLoaded)
		return of::module::logger::fromString(parser.get("logger", module, of::module::logger::to_string(logLevel, false)));
	return of::module::logger::LogLevel::INFO;
}

void EngineModule::GameConfig::setFramerateLimit(const unsigned& u)
{
	framerate = u;
	save();
}

unsigned EngineModule::GameConfig::getFramerateLimit() const
{
	return framerate;
}

unsigned EngineModule::GameConfig::getPhysicsThreadcount() const
{
	return physicsThreadCount;
}

bool EngineModule::GameConfig::getPhysicsForceSingleThread() const
{
	return physicsForceSingleThread;
}

bool EngineModule::GameConfig::getPhysicsAdaptiveRegions() const
{
	return physicsAdaptiveRegions;
}
