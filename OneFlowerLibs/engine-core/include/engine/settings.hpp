#pragma once
#include <utils/config/parser.hpp>

namespace of::settings
{
	class Settings
	{
		of::config::ConfigParser parser;

		bool mFixedSeed;
		bool mRenderHitboxes;
		bool mUsePvdDebugger;
		bool mShowLoadingScreenInfo;

	public:
		Settings();
		~Settings();
		Settings& operator=(const Settings&) = delete;

		of::config::ConfigParser& getParser();

		bool& useFixedSeed();
		bool& renderHitboxes();
		bool& usePvdDebugger();
		bool& showLoadingScreenInfo();
	};

	void init();
	void shutdown();
	Settings& get();
}
