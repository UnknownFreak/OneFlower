#ifndef EngineSettings_HPP
#define EngineSettings_HPP

#include <module/IEngineModule.hpp>
#include <utils/config/parser.hpp>

namespace OneFlower::Module
{
	class Settings : public Interface::IEngineResource<Settings>
	{
		OneFlower::Config::ConfigParser parser;

	public:
		Settings();
		~Settings();

		bool useFixedSeed();

		EngineResourceType& getType() const override;
	};
}

#endif