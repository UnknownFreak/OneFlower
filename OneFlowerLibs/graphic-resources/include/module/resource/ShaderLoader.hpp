#ifndef ShaderLoader_HPP
#define ShaderLoader_HPP

#include <unordered_map>
#include <mutex>

#include <core/String.hpp>
#include <module/IEngineModule.hpp>
#include <module/settings/EngineSettings.hpp>
#include <swizzle/gfx/Shader.hpp>


namespace OneFlower::Module::Shader
{
	class Loader : public Interface::IEngineResource<Loader>
	{
		bool lastResult = false;
		std::mutex mtx;
		const Core::String missingShader = "default.shader";
		std::unordered_map<Core::String, std::shared_ptr<swizzle::gfx::Shader>> loadedShaders;
		bool loadShader(const Core::String& name, const swizzle::gfx::ShaderAttributeList& attribs);

	public:
		std::shared_ptr<swizzle::gfx::Shader>& requestShader(const Core::String& name, const Core::String& path = Settings::shaderPath);
		std::shared_ptr<swizzle::gfx::Shader>& requestShader(const Core::String& name, const swizzle::gfx::ShaderAttributeList& attribs, const Core::String& path = Settings::shaderPath);
		bool getResult();

		void requestRemovalOfShader(const Core::String& name);

		EngineResourceType& getType() const
		{
			return type;
		}
	};
}

#endif