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
	}

	Settings::~Settings()
	{
		parser.save();
	}

	bool Settings::useFixedSeed()
	{
		return parser.get("random-generator").get<bool>("fixed-seed", false);
	}

	EngineResourceType& Settings::getType() const
	{
		return type;
	}
}