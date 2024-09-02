#include <engine/settings.hpp>

#include <logger/Logger.hpp>

of::settings::Settings* g_EngSettings = nullptr;

namespace of::settings
{

	Settings::Settings(): parser("EngineConfig.cfg")
	{
		if (parser.exists("random-generator"))
		{
			mFixedSeed = parser.get("random-generator").get<bool>("fixed-seed", false);
		}
		else
		{
			mFixedSeed = false;
		}

		if (parser.exists("physics"))
		{
			mUsePvdDebugger = parser.get("physics").get<bool>("use-pvd-debugger", false);
		}
		else
		{
			mUsePvdDebugger = false;
		}

		if (parser.exists("scene"))
		{
			mShowLoadingScreenInfo = parser.get("scene").get<bool>("show-loaginscreen-info", false);
		}
		else
		{
			mShowLoadingScreenInfo = false;
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

	void init()
	{
		if (g_EngSettings == nullptr)
		{
			of::logger::get().Info("Initializing module: EngineSettings");
			g_EngSettings = new Settings();
		}
		else
		{
			of::logger::get().getLogger("of::rng").Warning("Trying to initialize Engine Settings multiple times!");
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