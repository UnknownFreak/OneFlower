#ifndef EngineSettings_HPP
#define EngineSettings_HPP

#include <module/IEngineModule.hpp>
#include <module/ModuleManager.hpp>

#include <utils/config/parser.hpp>

namespace of::module
{
	class Settings : public interface::IEngineResource<Settings>
	{
		of::config::ConfigParser parser;

		bool mFixedSeed;
		bool mRenderHitboxes;
		bool mUsePvdDebugger;

	public:
		Settings();
		~Settings();

		of::config::ConfigParser& getParser();

		bool& useFixedSeed();
		bool& renderHitboxes();
		bool& usePvdDebugger();

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