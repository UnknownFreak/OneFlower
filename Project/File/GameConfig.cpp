#include "GameConfig.hpp"

#include <SFML/Window/WindowStyle.hpp>
#include <Module/Logger/OneLogger.hpp>

Enums::EngineResourceType Interfaces::IEngineResource<EngineModule::GameConfig>::type = Enums::EngineResourceType::Settings;

EngineModule::GameConfig::GameConfig() : configName("gameConfig.cfg"), videoModes(sf::VideoMode::getFullscreenModes()),
windowStyle(sf::Style::Close), antialiasing(32), framerate(0), parser(configName)
{
	defaultMode = videoMode = sf::VideoMode::getDesktopMode();
	load();
}

EngineModule::GameConfig::~GameConfig()
{
	save();
}

Enums::EngineResourceType& EngineModule::GameConfig::getType() const
{
	return type;
}

void EngineModule::GameConfig::save()
{
	parser.put("window", "height", videoMode.height);
	parser.put("window", "width", videoMode.width);
	parser.put("window", "framerate", framerate);
	parser.put("window", "aa", antialiasing);
	parser.put("window", "fullscreen", fullscreen);
	parser.save();
}

void EngineModule::GameConfig::load()
{
	parser.load();
	videoMode.height = parser.get("window", "height", defaultMode.height);
	videoMode.width = parser.get("window", "width", defaultMode.width);
	framerate = parser.get("window", "framerate", 0);
	antialiasing = parser.get("window", "aa", 32);
	fullscreen = parser.get("window", "fullscreen", false);
	windowStyle = fullscreen ? (sf::Uint32)sf::Style::Fullscreen : (sf::Uint32)sf::Style::Close;
	logLevel = Enums::fromString(parser.get("logger", "core.level", Enums::to_string(Enums::LogLevel::INFO, false)));
	physicsThreadCount = parser.get("physics", "threadCount", 4);
	physicsForceSingleThread = parser.get("physics", "forceSingleThread", false);
	physicsAdaptiveRegions = parser.get("physics", "adaptiveRegions", true);

	Engine::GetModule<EngineModule::Logger::OneLogger>().setLogLevel(logLevel);
	for (auto& logger_level : parser.get("logger").values)
	{
		if (logger_level.first != "core.level")
			Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger(logger_level.first).setLogLevel(Enums::fromString(logger_level.second));
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
	windowStyle = fullscreen ? (sf::Uint32)sf::Style::Fullscreen : (sf::Uint32)sf::Style::Close;
	save();
}

sf::Uint32 EngineModule::GameConfig::getWindowStyle() const
{
	return windowStyle;
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

Enums::LogLevel EngineModule::GameConfig::getCurrentLogLevel() const
{
	return logLevel;
}

Enums::LogLevel EngineModule::GameConfig::getModuleLogLevel(const Core::String& module)
{
	if (configLoaded)
		return Enums::fromString(parser.get("logger", module, Enums::to_string(logLevel, false)));
	return Enums::LogLevel::INFO;
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
