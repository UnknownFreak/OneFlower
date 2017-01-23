#pragma once
#ifndef TEXTURELOADER_HPP
#define TEXTURELOADER_HPP

#include "TextureRef.hpp"
#include <SFML\Graphics\Texture.hpp>
#include <string>
#include <map>
#include <future>
//#include "../Settings/EngineSettings.hpp"

class TextureLoader
{
	/*std::map<Settings::EngineSettings::TextureRes,*/
	std::map<std::string, TextureRef>/*> */loadedTextureMap;
	bool loadTexture(std::string name);
	sf::Texture loadTexture_internal(std::string name);


public:
	// used by TextureRef
	std::shared_future<sf::Texture> loadTextureAsync(std::string name);
	
	TextureRef* requestTexture(std::string name);

	//request removal of texture if its not in use
	void requestRemovalOfTexture(std::string name);

};

#endif
