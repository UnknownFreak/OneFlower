#ifndef ShaderLoader_HPP
#define ShaderLoader_HPP

#include <unordered_map>
#include <mutex>

#include <utils/common/string.hpp>
#include <module/IEngineModule.hpp>
#include <module/settings/EngineSettings.hpp>
#include <swizzle/gfx/Shader.hpp>


namespace of::module::shader
{
	class Loader : public interface::IEngineResource<Loader>
	{
		bool lastResult = false;
		std::mutex mtx;
		const common::String missingShader = "default.shader";
		std::unordered_map<common::String, std::shared_ptr<swizzle::gfx::Shader>> loadedShaders;
		bool loadShader(const common::String& name, const swizzle::gfx::ShaderAttributeList& attribs);

	public:
		std::shared_ptr<swizzle::gfx::Shader>& requestShader(const common::String& name, const common::String& path = Settings::shaderPath);
		std::shared_ptr<swizzle::gfx::Shader>& requestShader(const common::String& name, const swizzle::gfx::ShaderAttributeList& attribs, const common::String& path = Settings::shaderPath);
		bool getResult();

		void requestRemovalOfShader(const common::String& name);

		EngineResourceType& getType() const
		{
			return type;
		}
	};
}

#endif