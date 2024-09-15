#ifndef TEXTURELOADER_HPP
#define TEXTURELOADER_HPP

#include <unordered_map>
#include <mutex>

#include <swizzle/gfx/Texture.hpp>

#include <utils/common/string.hpp>
#include <engine/paths.hpp>

#include <swizzle/gfx/GfxDevice.hpp>
#include <swizzle/gfx/CommandBuffer.hpp>

namespace of::module::texture
{
	class Loader
	{
		std::mutex mtx;
		const common::String missingTexture = "missingTexture.png";
		/*std::map<Settings::EngineSettings::TextureRes,*/
		std::unordered_map<common::String, std::shared_ptr<swizzle::gfx::Texture>>/*> */loadedTextureMap;
		bool loadTexture(const common::String& name);
		bool loadCubeMap(const common::String& folderName);

		std::weak_ptr<swizzle::gfx::GfxDevice> m_gfxDevice;
		std::weak_ptr<swizzle::gfx::CommandBuffer> m_cmdBuffer;

	public:

		Loader(std::weak_ptr<swizzle::gfx::GfxDevice> gfxDevice, std::weak_ptr<swizzle::gfx::CommandBuffer> commandBuffer);
		Loader& operator=(const Loader&) = delete;

		std::shared_ptr<swizzle::gfx::Texture>& requestTexture(const common::String& name, const common::String& path = engine::path::textures);
		std::shared_ptr<swizzle::gfx::Texture>& requestCubemapTexture(const common::String& folderName, const common::String& path = engine::path::skybox);

		void requestRemovalOfTexture(const common::String& name);
	};

	Loader& get();
}

#endif
