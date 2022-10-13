#include "TextureLoader.hpp"

#include <swizzle/asset/TextureLoader.hpp>

#include <Module\EngineModuleManager.hpp>
#include <Graphics/Window.hpp>

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
		auto& wnd = Engine::GetModule<Graphics::RenderWindow>();
		loadedTextureMap/*[Engine::settings.textureQuality]*/.insert(
			std::make_pair(name, swizzle::asset::LoadTexture2D(wnd.getGfxContext(), path.c_str())));

		auto uploadBuffer = wnd.getUploadBuffer();
		auto trans = uploadBuffer->begin();
		trans->uploadTexture(loadedTextureMap[name]);
		uploadBuffer->end(std::move(trans));
		wnd.getGfxContext()->submit(&uploadBuffer, 1u, nullptr);
		mtx.unlock();
		return true;
	}

	bool Loader::loadCubeMap(const Core::String& folderName)
	{
		auto& logger = Engine::GetModule <EngineModule::Logger::OneLogger>().getLogger("File::Resource::Texture::Loader");
		logger.Info("Loading skybox cubemap texture [" + folderName + "]", logger.fileInfo(__FILE__, __LINE__));
		Core::String path = "Data/" + folderName;
		for (auto& file : { "top.png", "back.png", "bottom.png", "front.png", "left.png", "right.png" })
		{
			if (!std::filesystem::exists(path + file))
			{
				logger.Error("Unable to load skybox [" + folderName + file + "]", logger.fileInfo(__FILE__, __LINE__));
				return false;
			}
		}
		mtx.lock();
		auto& wnd = Engine::GetModule<Graphics::RenderWindow>();
		loadedTextureMap[folderName] = swizzle::asset::LoadTextureCubeMap(wnd.getGfxContext(),
					(path + "right.png").c_str(),
					(path + "left.png").c_str(),
					(path + "top.png").c_str(),
					(path + "bottom.png").c_str(),
					(path + "front.png").c_str(),
					(path + "back.png").c_str()
				);
		logger.Info("Loaded skybox cubemap texture [" + path + "right.png]", logger.fileInfo(__FILE__, __LINE__));
		logger.Info("Loaded skybox cubemap texture [" + path + "left.png]", logger.fileInfo(__FILE__, __LINE__));
		logger.Info("Loaded skybox cubemap texture [" + path + "tmp.png]", logger.fileInfo(__FILE__, __LINE__));
		logger.Info("Loaded skybox cubemap texture [" + path + "bottom.png]", logger.fileInfo(__FILE__, __LINE__));
		logger.Info("Loaded skybox cubemap texture [" + path + "front.png]", logger.fileInfo(__FILE__, __LINE__));
		logger.Info("Loaded skybox cubemap texture [" + path + "back.png]", logger.fileInfo(__FILE__, __LINE__));

		auto uploadBuffer = wnd.getUploadBuffer();
		auto trans = uploadBuffer->begin();
		trans->uploadTexture(loadedTextureMap[folderName]);
		uploadBuffer->end(std::move(trans));
		wnd.getGfxContext()->submit(&uploadBuffer, 1u, nullptr);

		mtx.unlock();
		return true;
	}

	std::shared_ptr<swizzle::gfx::Texture>& Loader::requestTexture(const Core::String& name, const Core::String& path)
	{
		auto& logger = Engine::GetModule <EngineModule::Logger::OneLogger>().getLogger("File::Resource::Texture::Loader");
		logger.Info("Request texture [" + name + "]", logger.fileInfo(__FILE__, __LINE__));
		if (!name.empty())
		{
			std::unordered_map<Core::String, std::shared_ptr<swizzle::gfx::Texture>>::iterator it;
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

	std::shared_ptr<swizzle::gfx::Texture>& Loader::requestCubemapTexture(const Core::String& folderName, const Core::String& path)
	{
		auto& logger = Engine::GetModule <EngineModule::Logger::OneLogger>().getLogger("File::Resource::Texture::Loader");
		logger.Info("Request cubemap texture [" + folderName + "]", logger.fileInfo(__FILE__, __LINE__));
		if (!folderName.empty())
		{
			std::unordered_map<Core::String, std::shared_ptr<swizzle::gfx::Texture>>::iterator it;
			it = loadedTextureMap/*[Engine::settings.textureQuality]*/.find(path + folderName);

			if (it != loadedTextureMap/*[Engine::settings.textureQuality]*/.end())
				return it->second;

			if (loadCubeMap(path + folderName))
				return loadedTextureMap/*[Engine::settings.textureQuality]*/.find(path + folderName)->second;
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
