#ifndef GameConfig_HPP
#define GameConfig_HPP

#include <vector>

#include <Interfaces/IEngineModule.hpp>

#include <Helpers/String.hpp>
#include <Helpers/Enum/LogLevel.hpp>
#include <File/CfgParser.hpp>

namespace EngineModule
{
	class GameConfig : public Interfaces::IEngineResource<GameConfig>
	{
		bool configLoaded = false;
		const Core::String configName;
		File::Resource::Config::ConfigParser parser;
		std::pair<uint32_t, uint32_t> defaultMode;
		bool fullscreen;
		unsigned antialiasing;
		unsigned framerate;
		Enums::LogLevel logLevel;
		unsigned physicsThreadCount;
		bool physicsForceSingleThread;
		bool physicsAdaptiveRegions;
	public:

		std::pair<uint32_t, uint32_t> videoMode;

		std::vector<std::pair<uint32_t, uint32_t>> videoModes;

		GameConfig();
		~GameConfig();

		// Inherited via IEngineResource
		virtual Enums::EngineResourceType& getType() const override;

		void save();
		void load();
		void setVideoMode(const size_t& index);
		void toggleFullscreen();
		void setAntiAliasing(const unsigned& aa);
		unsigned getAntiAliasing() const;

		Enums::LogLevel getCurrentLogLevel() const;
		Enums::LogLevel getModuleLogLevel(const Core::String& module);

		void setFramerateLimit(const unsigned& u);
		unsigned getFramerateLimit() const;

		unsigned getPhysicsThreadcount() const;
		bool getPhysicsForceSingleThread() const;
		bool getPhysicsAdaptiveRegions() const;

	};
}
#endif