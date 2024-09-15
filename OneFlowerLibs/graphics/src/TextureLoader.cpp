#include <module/resource/TextureLoader.hpp>
#include <module/resource/internalLoaders.hpp>

#include <swizzle/asset2/Assets.hpp>

#include <logger/Logger.hpp>

#include <filesystem>

static of::module::texture::Loader* g_textureLoader = nullptr;

namespace of::module::texture
{

	Loader::Loader(std::weak_ptr<swizzle::gfx::GfxDevice> gfxDevice, std::weak_ptr<swizzle::gfx::CommandBuffer> commandBuffer) : m_gfxDevice(gfxDevice), m_cmdBuffer(commandBuffer)
	{
		
	}

	bool Loader::loadTexture(const common::String& name)
	{
		common::String path = "Data/" + name;
		if (!std::filesystem::exists(path))
		{
			auto& logger = of::logger::get().getLogger("texture::Loader");
			logger.Error("Unable to load texture [" + name + "]", logger.fileInfo(__FILE__, __LINE__));
			return false;
		}
	#ifdef _DEBUG
			//MessageBox(0,"Error loading this file",name.c_str(),MB_OK);
	#endif
		mtx.lock();
		auto textureData = swizzle::asset2::LoadTexture(path.c_str());
		
		if (auto device = m_gfxDevice.lock())
		{
			auto cmdBuffer = m_cmdBuffer.lock();

			loadedTextureMap/*[Engine::settings.textureQuality]*/.insert(
				std::make_pair(name, device->createTexture(textureData->getWidth(), textureData->getHeight(), 4u, false)));

			auto trans = cmdBuffer->begin();

			auto buffer = device->createBuffer(swizzle::gfx::GfxBufferType::UniformBuffer, swizzle::gfx::GfxMemoryArea::Host);
			buffer->setBufferData(textureData->getData()->data(), textureData->getData()->size(), 4u);

			swizzle::gfx::TextureDimensions size{};
			size.mHeight = textureData->getHeight();
			size.mWidth = textureData->getWidth();
			size.mLayers = 1u;
			size.mMipLevels = 1u;

			trans->copyBufferToTexture(loadedTextureMap[name], buffer, size);
			cmdBuffer->end(std::move(trans));
			device->submit(&cmdBuffer, 1u, nullptr);
		}
		mtx.unlock();
		return true;
	}

	bool Loader::loadCubeMap(const common::String& folderName)
	{
		auto& logger = of::logger::get().getLogger("texture::Loader");
		logger.Info("Loading skybox cubemap texture [" + folderName + "]", logger.fileInfo(__FILE__, __LINE__));
		common::String path = "Data/" + folderName;
		for (auto& file : { "top.png", "back.png", "bottom.png", "front.png", "left.png", "right.png" })
		{
			if (!std::filesystem::exists(path + file))
			{
				logger.Error("Unable to load skybox [" + folderName + file + "]", logger.fileInfo(__FILE__, __LINE__));
				return false;
			}
		}
		mtx.lock();

		auto textureData = swizzle::asset2::LoadCubeTexture(
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

		if (auto device = m_gfxDevice.lock())
		{
			auto cmdBuffer = m_cmdBuffer.lock();
			loadedTextureMap[folderName] = device->createCubeMapTexture(textureData->getWidth(), textureData->getHeight(), 4u);

			auto trans = cmdBuffer->begin();

			auto buffer = device->createBuffer(swizzle::gfx::GfxBufferType::UniformBuffer, swizzle::gfx::GfxMemoryArea::Host);
			buffer->setBufferData(textureData->getData()->data(), textureData->getData()->size(), 4u);

			swizzle::gfx::TextureDimensions size{};
			size.mHeight = textureData->getHeight();
			size.mWidth = textureData->getWidth();
			size.mLayers = 6u;
			size.mMipLevels = 1u;

			trans->copyBufferToTexture(loadedTextureMap[folderName], buffer, size);
			cmdBuffer->end(std::move(trans));
			device->submit(&cmdBuffer, 1u, nullptr);
		}
		mtx.unlock();
		return true;
	}

	std::shared_ptr<swizzle::gfx::Texture>& Loader::requestTexture(const common::String& name, const common::String& path)
	{
		auto& logger = of::logger::get().getLogger("texture::Loader");
		logger.Info("Request texture [" + name + "]", logger.fileInfo(__FILE__, __LINE__));
		if (!name.empty())
		{
			std::unordered_map<common::String, std::shared_ptr<swizzle::gfx::Texture>>::iterator it;
			it = loadedTextureMap/*[Engine::settings.textureQuality]*/.find(path + name);

			if (it != loadedTextureMap/*[Engine::settings.textureQuality]*/.end())
				return it->second;

			if (loadTexture(path + name))
				return loadedTextureMap/*[Engine::settings.textureQuality]*/.find(path + name)->second;

			//LOW set propper texturename
			it = loadedTextureMap/*[Engine::settings.textureQuality]*/.find(of::engine::path::textures +missingTexture);
			if (it != loadedTextureMap/*[Engine::settings.textureQuality]*/.end())
				return it->second;
			loadTexture(of::engine::path::textures + missingTexture);
			return loadedTextureMap/*[Engine::settings.textureQuality]*/.find(of::engine::path::textures + missingTexture)->second;
		}
		return requestTexture(missingTexture, of::engine::path::textures);
	}

	std::shared_ptr<swizzle::gfx::Texture>& Loader::requestCubemapTexture(const common::String& folderName, const common::String& path)
	{
		auto& logger = of::logger::get().getLogger("texture::Loader");
		logger.Info("Request cubemap texture [" + folderName + "]", logger.fileInfo(__FILE__, __LINE__));
		if (!folderName.empty())
		{
			std::unordered_map<common::String, std::shared_ptr<swizzle::gfx::Texture>>::iterator it;
			it = loadedTextureMap/*[Engine::settings.textureQuality]*/.find(path + folderName);

			if (it != loadedTextureMap/*[Engine::settings.textureQuality]*/.end())
				return it->second;

			if (loadCubeMap(path + folderName))
				return loadedTextureMap/*[Engine::settings.textureQuality]*/.find(path + folderName)->second;
		}
		return requestTexture(missingTexture, engine::path::textures);
	}

	void Loader::requestRemovalOfTexture(const common::String& name)
	{
		if (loadedTextureMap.find(name) != loadedTextureMap.end())
		{
			auto& logger = of::logger::get().getLogger("texture::Loader");
			logger.Info("Unloading texture " + name, logger.fileInfo(__FILE__, __LINE__));
			loadedTextureMap.erase(name);
		}
	}

	Loader& get()
	{
		return *g_textureLoader;
	}

	void init(std::weak_ptr<swizzle::gfx::GfxDevice> gfxDevice, std::weak_ptr<swizzle::gfx::CommandBuffer> commandBuffer)
	{
		if (g_textureLoader == nullptr)
		{
			g_textureLoader = new Loader(gfxDevice, commandBuffer);
		}
	}

	void shutdown()
	{
		delete g_textureLoader;
		g_textureLoader = nullptr;
	}
}
