#ifndef EngineSettings_HPP
#define EngineSettings_HPP

#include <module/IEngineModule.hpp>
#include <utils/config/parser.hpp>

namespace of::module
{
	class Settings : public Interface::IEngineResource<Settings>
	{
		of::config::ConfigParser parser;

	public:
		Settings();
		~Settings();

		bool useFixedSeed();

		EngineResourceType& getType() const override;


		static const common::String texturePath;
		static const common::String skyboxTexturePath;
		static const common::String uiTexturePath;
		static const common::String tileTexturePath;
		static const common::String meshPath;
		static const common::String shaderPath;
	};
}

#endif