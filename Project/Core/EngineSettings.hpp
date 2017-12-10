#ifndef EngineSettings_HPP
#define EngineSettings_HPP

#include <SFML\Window\VideoMode.hpp>
#include <Core\IEngineResource\IEngineResource.hpp>
#include <Core/String.hpp>
namespace Settings
{

	class EngineSettings : public IEngineResource<EngineSettings>
	{
	public:
		// Video and sound
#pragma region Video and sound
		enum class VSYNC
		{
			DEFAULT,
			ON,
			OFF,
		};
		
		enum class TextureRes
		{
			HIGH,
			MEDIUM = 2,
			LOW = 4,
		};

		const ResourceType& getType()
		{
			return type;
		}

		sf::VideoMode res;
		__int8 volume;
		__int8 effects;
		VSYNC vsync = VSYNC::DEFAULT;
#pragma endregion

#pragma region TextureQuality
		TextureRes textureQuality = TextureRes::HIGH;
#pragma endregion

#pragma region System

		Core::String Language;
		// PrimaryDisplay

#pragma endregion 


#pragma region SaveLoad

		//template <class Archive>
		//friend void save(Archive& ar, const EngineSettings & settings);
		//template <class Archive>
		//friend void load(Archive& ar, EngineSettings& settings);

#pragma endregion

	};
};

#endif
