#ifndef GameConfig_HPP
#define GameConfig_HPP

#include <vector>

#include <module/IEngineModule.hpp>

#include <utils/common/String.hpp>
#include <module/logger/LogLevel.hpp>
#include <utils/config/parser.hpp>

namespace EngineModule
{
	class GameConfig : public of::module::interface::IEngineResource<GameConfig>
	{
		bool configLoaded = false;
		const of::common::String configName;
		of::config::ConfigParser parser;
		std::pair<uint32_t, uint32_t> defaultMode;
		bool fullscreen;
		unsigned antialiasing;
		unsigned framerate;
		of::module::logger::LogLevel logLevel;
		unsigned physicsThreadCount;
		bool physicsForceSingleThread;
		bool physicsAdaptiveRegions;
	public:

		std::pair<uint32_t, uint32_t> videoMode;

		std::vector<std::pair<uint32_t, uint32_t>> videoModes;

		GameConfig();
		~GameConfig();

		// Inherited via IEngineResource
		virtual of::module::EngineResourceType& getType() const override;

		void save();
		void load();
		void setVideoMode(const size_t& index);
		void toggleFullscreen();
		void setAntiAliasing(const unsigned& aa);
		unsigned getAntiAliasing() const;

		of::module::logger::LogLevel getCurrentLogLevel() const;
		of::module::logger::LogLevel getModuleLogLevel(const of::common::String& module);

		void setFramerateLimit(const unsigned& u);
		unsigned getFramerateLimit() const;

		unsigned getPhysicsThreadcount() const;
		bool getPhysicsForceSingleThread() const;
		bool getPhysicsAdaptiveRegions() const;

	};
}
#endif