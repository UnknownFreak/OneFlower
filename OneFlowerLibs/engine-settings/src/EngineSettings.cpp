#include <module/settings/EngineSettings.hpp>

of::module::EngineResourceType  of::module::interface::IEngineResource< of::module::Settings>::type = of::module::EngineResourceType::EngineSettings;

namespace of::module
{

	const common::String Settings::texturePath = "Textures/";
	const common::String Settings::skyboxTexturePath = Settings::texturePath + "skybox/";
	const common::String Settings::uiTexturePath = Settings::texturePath + "Ui/";
	const common::String Settings::tileTexturePath = Settings::texturePath + "Tiles/";
	const common::String Settings::meshPath = "Meshes/";
	const common::String Settings::shaderPath = "Shaders/";

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

	EngineResourceType& Settings::getType() const
	{
		return type;
	}
}