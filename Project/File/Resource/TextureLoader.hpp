#ifndef TEXTURELOADER_HPP
#define TEXTURELOADER_HPP

#include <swizzle/gfx/Texture.hpp>

#include <Helpers/String.hpp>
#include <Module/Globals.hpp>
#include <unordered_map>
#include <mutex>

#include <Interfaces/IEngineModule.hpp>

namespace File::Resource::Texture
{
	class Loader : public Interfaces::IEngineResource<Loader>
	{
		std::mutex mtx;
		const Core::String missingTexture = "missingTexture.png";
		/*std::map<Settings::EngineSettings::TextureRes,*/
		std::unordered_map<Core::String, std::shared_ptr<swizzle::gfx::Texture>>/*> */loadedTextureMap;
		bool loadTexture(const Core::String& name);
		bool loadCubeMap(const Core::String& folderName);

	public:
		std::shared_ptr<swizzle::gfx::Texture>& requestTexture(const Core::String& name, const Core::String& path = Globals::texturePath);
		std::shared_ptr<swizzle::gfx::Texture>& requestCubemapTexture(const Core::String& folderName, const Core::String& path = Globals::skyboxTexturePath);

		void requestRemovalOfTexture(const Core::String& name);

		Enums::EngineResourceType& getType() const
		{
			return type;
		}
	};
}

#endif
