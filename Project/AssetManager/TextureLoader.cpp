#include "TextureLoader.hpp"
//#include "../../Engine.hpp"

bool TextureLoader::loadTexture(std::string name)
{
	//sf::Texture tempTexture;
	//if (!tempTexture.loadFromFile("Texture/" + name))
	//{
#ifdef _DEBUG
		//MessageBox(0,"Error loading this file",name.c_str(),MB_OK);
#endif
	//	return false;
	//}
	loadedTextureMap/*[Engine::settings.textureQuality]*/.insert(loadedTextureMap/*[Engine::settings.textureQuality]*/.end(), std::make_pair(name, TextureRef(name)));

	return true;
}
sf::Texture TextureLoader::loadTexture_internal(std::string name)
{
	sf::Texture tempTexture;
	if (!tempTexture.loadFromFile("Texture/" + name))
	{
		return sf::Texture();
	}
	return tempTexture;
}

#ifdef _EDITOR_
sf::Texture TextureLoader::loadTextureAsync(std::string name)
{
	return loadTexture_internal(name);
}
#else

std::shared_future<sf::Texture> TextureLoader::loadTextureAsync(std::string name)
{
	
	std::shared_future<sf::Texture>tp = std::async(std::launch::async, [this](std::string name) -> sf::Texture {return loadTexture_internal(name); }, name);
	return tp;
}
#endif
TextureRef* TextureLoader::requestTexture(std::string name)
{
	if (!name.empty())
	{
		std::map<std::string, TextureRef>::iterator it;
		it = loadedTextureMap/*[Engine::settings.textureQuality]*/.find(name);

		if (it != loadedTextureMap/*[Engine::settings.textureQuality]*/.end())
			return &it->second;

		if (loadTexture(name))
			return &loadedTextureMap/*[Engine::settings.textureQuality]*/.find(name)->second;

		//LOW set propper texturename
		it = loadedTextureMap/*[Engine::settings.textureQuality]*/.find("test.png");
		if (it != loadedTextureMap/*[Engine::settings.textureQuality]*/.end())
			return &it->second;
		loadTexture("test.png");
		return &loadedTextureMap/*[Engine::settings.textureQuality]*/.find("test.png")->second;
	}
	return nullptr;
}

void TextureLoader::requestRemovalOfTexture(std::string name)
{
	//TODO
}
