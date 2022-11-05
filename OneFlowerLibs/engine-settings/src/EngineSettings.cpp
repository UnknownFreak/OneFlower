#include <module/settings/EngineSettings.hpp>

OneFlower::Module::EngineResourceType  OneFlower::Module::Interface::IEngineResource< OneFlower::Module::Settings>::type = OneFlower::Module::EngineResourceType::EngineSettings;

namespace OneFlower::Module
{
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