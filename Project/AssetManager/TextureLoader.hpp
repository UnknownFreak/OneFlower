#ifndef TEXTURELOADER_HPP
#define TEXTURELOADER_HPP

#include "TextureRef.hpp"
#include <SFML\Graphics\Texture.hpp>
#include <Core/String.hpp>
#include <map>
#ifndef _EDITOR_
#include <future>
#endif
//#include "../Settings/EngineSettings.hpp"

class TextureLoader
{
	/*std::map<Settings::EngineSettings::TextureRes,*/
	std::map<Core::String, TextureRef>/*> */loadedTextureMap;
	bool loadTexture(const Core::String& name);
	sf::Texture loadTexture_internal(const Core::String& name);


public:
	// used by TextureRef
#ifdef _EDITOR_
	sf::Texture loadTextureAsync(const Core::String& name);
#else
	std::shared_future<sf::Texture> loadTextureAsync(Core::String& name);
#endif
	TextureRef* requestTexture(const Core::String& name);

	//request removal of texture if its not in use
	void requestRemovalOfTexture(const Core::String& name);

};

#endif
