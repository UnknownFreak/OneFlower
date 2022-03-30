#include "TextureLoader.hpp"
#include <fstream>
#include <Module\EngineModuleManager.hpp>
#include <filesystem>

Enums::EngineResourceType Interfaces::IEngineResource<File::Resource::Texture::Loader>::type = Enums::EngineResourceType::TextureLoader;

namespace File::Resource::Texture
{

	bool Loader::loadTexture(const Core::String& name)
	{
		Core::String path = "Data/" + name;
		if (!std::filesystem::exists(path))
		{
			auto& logger = Engine::GetModule <EngineModule::Logger::OneLogger>().getLogger("File::Resource::Texture::Loader");
			logger.Error("Unable to load texture [" + name + "]", logger.fileInfo(__FILE__, __LINE__));
			return false;
		}
	#ifdef _DEBUG
			//MessageBox(0,"Error loading this file",name.c_str(),MB_OK);
	#endif
		mtx.lock();
		loadedTextureMap/*[Engine::settings.textureQuality]*/.insert(
			std::make_pair(name, std::make_shared<sf::Texture>(loadTexture_internal(path))));
		mtx.unlock();
		return true;
	}
	sf::Texture Loader::loadTexture_internal(const Core::String& name)
	{
		std::wstring wstr = Engine::GetModule<Core::StringConverter>().toUtf16(name);
		std::ifstream i(wstr , std::ios::in | std::ifstream::binary);
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
			auto& logger = Engine::GetModule <EngineModule::Logger::OneLogger>().getLogger("File::Resource::Texture::Loader");
			logger.Info("Failed to load texture: " + name, logger.fileInfo(__FILE__, __LINE__));
			return sf::Texture();
		}
		return tempTexture;
	}

	std::shared_ptr<sf::Texture>& Loader::requestTexture(const Core::String& name, const Core::String& path)
	{
		if (!name.empty())
		{
			std::unordered_map<Core::String, std::shared_ptr<sf::Texture>>::iterator it;
			it = loadedTextureMap/*[Engine::settings.textureQuality]*/.find(path + name);

			if (it != loadedTextureMap/*[Engine::settings.textureQuality]*/.end())
				return it->second;

			if (loadTexture(path + name))
				return loadedTextureMap/*[Engine::settings.textureQuality]*/.find(path + name)->second;

			//LOW set propper texturename
			it = loadedTextureMap/*[Engine::settings.textureQuality]*/.find(Globals::texturePath + missingTexture);
			if (it != loadedTextureMap/*[Engine::settings.textureQuality]*/.end())
				return it->second;
			loadTexture(Globals::texturePath + missingTexture);
			return loadedTextureMap/*[Engine::settings.textureQuality]*/.find(Globals::texturePath + missingTexture)->second;
		}
		return requestTexture(missingTexture, Globals::texturePath);
	}

	void Loader::requestRemovalOfTexture(const Core::String& name)
	{
		if (loadedTextureMap.find(name) != loadedTextureMap.end())
		{
			auto& logger = Engine::GetModule <EngineModule::Logger::OneLogger>().getLogger("File::Resource::Texture::Loader");
			logger.Info("Unloading texture " + name, logger.fileInfo(__FILE__, __LINE__));
			loadedTextureMap.erase(name);
		}
	}
}
