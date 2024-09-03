#pragma once
#include <utils/config/parser.hpp>

#include <logger/LogLevel.hpp>

namespace of::settings
{
	class Settings
	{

		struct ScreenResolution
		{
			unsigned int width;
			unsigned int height;
		};

		of::config::ConfigParser parser;

		bool mFixedSeed;
		bool mRenderHitboxes;
		bool mUsePvdDebugger;
		bool mShowLoadingScreenInfo;
		bool mFullscreen;
		bool mBorderless;
		ScreenResolution mScreenResolution;
		of::logger::LogLevel mLogLevel;
		unsigned int mThreadCount;

	public:
		Settings();
		~Settings();
		Settings& operator=(const Settings&) = delete;

		of::config::ConfigParser& getParser();

		bool& useFixedSeed();
		bool& renderHitboxes();
		bool& usePvdDebugger();
		bool& showLoadingScreenInfo();

		of::logger::LogLevel getCurrentLogLevel() const;
		of::logger::LogLevel getModuleLogLevel(const of::common::String& module);
		unsigned int getPhysicsThreadCount() const;
		bool isFullscreen() const;
		bool isBorderless() const;
		ScreenResolution getScreenResolution() const; 

		of::config::Section& getPluginSettings(const of::common::String& pluginName);

	};

	void init();
	void shutdown();
	Settings& get();
}
