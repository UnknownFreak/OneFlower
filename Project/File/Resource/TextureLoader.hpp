#ifndef TEXTURELOADER_HPP
#define TEXTURELOADER_HPP

#include <swizzle/gfx/Texture.hpp>

#include <utils/common/string.hpp>
#include <Module/Globals.hpp>
#include <unordered_map>
#include <mutex>

#include <module/IEngineModule.hpp>

namespace File::Resource::Texture
{
	class Loader : public of::module::interface::IEngineResource<Loader>
	{
		std::mutex mtx;
		const of::common::String missingTexture = "missingTexture.png";
		/*std::map<Settings::EngineSettings::TextureRes,*/
		std::unordered_map<of::common::String, std::shared_ptr<swizzle::gfx::Texture>>/*> */loadedTextureMap;
		bool loadTexture(const of::common::String& name);
		bool loadCubeMap(const of::common::String& folderName);

	public:
		std::shared_ptr<swizzle::gfx::Texture>& requestTexture(const of::common::String& name, const of::common::String& path = Globals::texturePath);
		std::shared_ptr<swizzle::gfx::Texture>& requestCubemapTexture(const of::common::String& folderName, const of::common::String& path = Globals::skyboxTexturePath);

		void requestRemovalOfTexture(const of::common::String& name);

		of::module::EngineResourceType& getType() const
		{
			return type;
		}
	};
}

#endif
