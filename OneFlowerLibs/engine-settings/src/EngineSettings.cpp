#include <module/settings/EngineSettings.hpp>

OneFlower::Module::EngineResourceType  OneFlower::Module::Interface::IEngineResource< OneFlower::Module::Settings>::type = OneFlower::Module::EngineResourceType::EngineSettings;

namespace OneFlower::Module
{

	const Core::String Settings::texturePath = "Textures/";
	const Core::String Settings::skyboxTexturePath = Settings::texturePath + "skybox/";
	const Core::String Settings::uiTexturePath = Settings::texturePath + "Ui/";
	const Core::String Settings::tileTexturePath = Settings::texturePath + "Tiles/";
	const Core::String Settings::meshPath = "Meshes/";
	const Core::String Settings::shaderPath = "Shaders/";

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