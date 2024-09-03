#include <engine/settings.hpp>

#include <logger/Logger.hpp>

of::settings::Settings* g_EngSettings = nullptr;

namespace of::settings
{

	Settings::Settings() 
		: parser("settings.ini")
		, mFixedSeed(false)
		, mRenderHitboxes(false)
		, mUsePvdDebugger(false)
		, mShowLoadingScreenInfo(false)
		, mFullscreen(false)
		, mBorderless(false)
		, mScreenResolution{1920, 1080}
		, mLogLevel(of::logger::LogLevel::INFO)
		, mThreadCount(2)
	{
		if (parser.exists("random-generator"))
		{
			mFixedSeed = parser.get("random-generator").get<bool>("fixed-seed", false);
		}
		if (parser.exists("physics"))
		{
			mUsePvdDebugger = parser.get("physics").get<bool>("use-pvd-debugger", false);
			mThreadCount = parser.get("physics").get("threadCount", 2u);
		}

		if (parser.exists("scene"))
		{
			mShowLoadingScreenInfo = parser.get("scene").get<bool>("show-loaginscreen-info", false);
		}

		if (parser.exists("logger"))
		{
			mLogLevel = of::logger::fromString(parser.get("logger", "core.level", of::logger::to_string(of::logger::LogLevel::INFO, false)));
		
			of::logger::get().setLogLevel(mLogLevel);
			for (auto& logger_level : parser.get("logger").values)
			{
				if (logger_level.first != "core.level")
				{
					of::logger::get().getLogger(logger_level.first).setLogLevel(of::logger::fromString(logger_level.second));
				}
			}
		}
		if (parser.exists("window"))
		{
			mFullscreen = parser.get("window").get("fullscreen", false);
			mBorderless = parser.get("window").get("borderless", false);
			mScreenResolution.height = parser.get("window").get("height", 1080);
			mScreenResolution.width = parser.get("window").get("width", 1080);
		}

		mRenderHitboxes = parser.get("graphics").get<bool>("render-hitboxes", false);
		
	}

	Settings::~Settings()
	{
		if (parser.exists("random-generator"))
		{
			parser.get("random-generator").put<bool>("fixed-seed", mFixedSeed);
		}
		if (parser.exists("physics"))
		{
			parser.get("physics").put<bool>("use-pvd-debugger", mUsePvdDebugger);
		}
		if (parser.exists("scene"))
		{
			parser.get("scene").put<bool>("show-loadingscreen-info", mShowLoadingScreenInfo);
		}
		parser.get("graphics").put<bool>("render-hitboxes", mRenderHitboxes);
		parser.save();
	}

	of::config::ConfigParser& Settings::getParser()
	{
		return parser;
	}

	bool& Settings::useFixedSeed()
	{
		return mFixedSeed;
	}

	bool& Settings::renderHitboxes()
	{
		return mRenderHitboxes;
	}

	bool& Settings::usePvdDebugger()
	{
		return mUsePvdDebugger;
	}
	bool& Settings::showLoadingScreenInfo()
	{
		return mShowLoadingScreenInfo;
	}

	of::logger::LogLevel Settings::getCurrentLogLevel() const
	{
		return mLogLevel;
	}

	of::logger::LogLevel Settings::getModuleLogLevel(const of::common::String& module)
	{
		return of::logger::fromString(parser.get("logger", module, of::logger::to_string(mLogLevel, false)));
	}

	unsigned int Settings::getPhysicsThreadCount() const
	{
		return mThreadCount;
	}

	bool Settings::isFullscreen() const
	{
		return mFullscreen;
	}

	bool Settings::isBorderless() const
	{
		return mBorderless;
	}

	Settings::ScreenResolution Settings::getScreenResolution() const
	{
		return mScreenResolution;
	}

	of::config::Section& Settings::getPluginSettings(const of::common::String& pluginName)
	{
		return parser.get(pluginName);
	}

	void init()
	{
		if (g_EngSettings == nullptr)
		{
			of::logger::get().Info("Initializing module: EngineSettings");
			g_EngSettings = new Settings();
		}
		else
		{
			of::logger::get().getLogger("of::settings").Warning("Trying to initialize Engine Settings multiple times!");
		}
	}

	void shutdown()
	{
		delete g_EngSettings;
		g_EngSettings = nullptr;
	}

	Settings& get()
	{
		return *g_EngSettings;
	}
}