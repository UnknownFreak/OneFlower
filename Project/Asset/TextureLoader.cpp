#include "TextureLoader.hpp"
#include <fstream>
#include <Core\EngineModule\EngineModuleManager.hpp>

bool TextureLoader::loadTexture(const Core::String& name)
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
sf::Texture TextureLoader::loadTexture_internal(const Core::String& name)
{
	Core::String path = "Data/" + name;
	std::wstring wstr = Engine::GetModule<Core::StringConverter>().toUtf16(path);
	std::ifstream i(path , std::ios::in | std::ifstream::binary);
	i.seekg(0, i.end);
	size_t len = (size_t)i.tellg();
	i.seekg(0, i.beg);
	char* data = new char[len];
	i.read(data, len);
	
	sf::Texture tempTexture;
	bool ok = tempTexture.loadFromMemory(data, len);
	
	delete[] data;
	if (! ok)
	{
		return sf::Texture();
	}
	return tempTexture;
}

#ifdef _EDITOR_
sf::Texture TextureLoader::loadTextureAsync(const Core::String& name)
{
	return loadTexture_internal(name);
}
#else

std::shared_future<sf::Texture> TextureLoader::loadTextureAsync(const Core::String& name)
{
	
	std::shared_future<sf::Texture>tp = std::async(std::launch::async, [this](std::string name) -> sf::Texture {return loadTexture_internal(name); }, name);
	return tp;
}
#endif
TextureRef* TextureLoader::requestTexture(const Core::String& name, const Core::String& path)
{
	if (!name.empty())
	{
		std::map<Core::String, TextureRef>::iterator it;
		it = loadedTextureMap/*[Engine::settings.textureQuality]*/.find(path + name);

		if (it != loadedTextureMap/*[Engine::settings.textureQuality]*/.end())
			return &it->second;

		if (loadTexture(path + name))
			return &loadedTextureMap/*[Engine::settings.textureQuality]*/.find(path + name)->second;

		//LOW set propper texturename
		it = loadedTextureMap/*[Engine::settings.textureQuality]*/.find(Globals::texturePath + "test.png");
		if (it != loadedTextureMap/*[Engine::settings.textureQuality]*/.end())
			return &it->second;
		loadTexture(Globals::texturePath+"test.png");
		return &loadedTextureMap/*[Engine::settings.textureQuality]*/.find(Globals::texturePath + "test.png")->second;
	}
	return requestTexture("test.png", Globals::texturePath);
}

void TextureLoader::requestRemovalOfTexture(const Core::String& name)
{
	if (loadedTextureMap.find(name) != loadedTextureMap.end())
		loadedTextureMap.erase(name);
}
