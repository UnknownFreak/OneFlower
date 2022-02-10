#ifndef GameConfig_HPP
#define GameConfig_HPP

#include <vector>
#include <SFML/Window/VideoMode.hpp>

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
		File::ConfigParser parser;
		sf::VideoMode defaultMode;
		bool fullscreen;
		sf::Uint32 windowStyle;
		unsigned antialiasing;
		unsigned framerate;
		Enums::LogLevel logLevel;
		unsigned physicsThreadCount;
		bool physicsForceSingleThread;
		bool physicsAdaptiveRegions;
	public:

		sf::VideoMode videoMode;

		std::vector<sf::VideoMode> videoModes;

		GameConfig();
		~GameConfig();

		// Inherited via IEngineResource
		virtual Enums::EngineResourceType& getType() const override;

		void save();
		void load();
		void setVideoMode(const size_t& index);
		void toggleFullscreen();
		sf::Uint32 getWindowStyle() const;
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