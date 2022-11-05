#ifndef TEXTURELOADER_HPP
#define TEXTURELOADER_HPP

#include <unordered_map>
#include <mutex>

#include <swizzle/gfx/Texture.hpp>

#include <core/String.hpp>
#include <module/IEngineModule.hpp>
#include <module/settings/EngineSettings.hpp>

namespace OneFlower::Module::Texture
{
	class Loader : public Interface::IEngineResource<Loader>
	{
		std::mutex mtx;
		const Core::String missingTexture = "missingTexture.png";
		/*std::map<Settings::EngineSettings::TextureRes,*/
		std::unordered_map<Core::String, std::shared_ptr<swizzle::gfx::Texture>>/*> */loadedTextureMap;
		bool loadTexture(const Core::String& name);
		bool loadCubeMap(const Core::String& folderName);

	public:
		std::shared_ptr<swizzle::gfx::Texture>& requestTexture(const Core::String& name, const Core::String& path = Settings::texturePath);
		std::shared_ptr<swizzle::gfx::Texture>& requestCubemapTexture(const Core::String& folderName, const Core::String& path = Settings::skyboxTexturePath);

		void requestRemovalOfTexture(const Core::String& name);

		EngineResourceType& getType() const
		{
			return type;
		}
	};
}

#endif
