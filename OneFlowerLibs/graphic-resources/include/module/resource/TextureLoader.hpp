#ifndef TEXTURELOADER_HPP
#define TEXTURELOADER_HPP

#include <unordered_map>
#include <mutex>

#include <swizzle/gfx/Texture.hpp>

#include <utils/common/string.hpp>
#include <module/IEngineModule.hpp>
#include <module/ModuleManager.hpp>
#include <module/settings/EngineSettings.hpp>

namespace of::module::texture
{
	class Loader : public interface::IEngineResource<Loader>
	{
		std::mutex mtx;
		const common::String missingTexture = "missingTexture.png";
		/*std::map<Settings::EngineSettings::TextureRes,*/
		std::unordered_map<common::String, std::shared_ptr<swizzle::gfx::Texture>>/*> */loadedTextureMap;
		bool loadTexture(const common::String& name);
		bool loadCubeMap(const common::String& folderName);

	public:
		std::shared_ptr<swizzle::gfx::Texture>& requestTexture(const common::String& name, const common::String& path = Settings::texturePath);
		std::shared_ptr<swizzle::gfx::Texture>& requestCubemapTexture(const common::String& folderName, const common::String& path = Settings::skyboxTexturePath);

		void requestRemovalOfTexture(const common::String& name);

		EngineResourceType& getType() const
		{
			return type;
		}
	};
}

#endif
