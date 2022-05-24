#ifndef ShaderLoader_HPP
#define ShaderLoader_HPP

#include <swizzle/gfx/Shader.hpp>

#include <Helpers/String.hpp>
#include <Module/Globals.hpp>
#include <unordered_map>
#include <mutex>

#include <Interfaces/IEngineModule.hpp>

namespace File::Resource::Shader
{
	class Loader : public Interfaces::IEngineResource<Loader>
	{
		bool lastResult = false;
		std::mutex mtx;
		const Core::String missingShader = "default.shader";
		std::unordered_map<Core::String, std::shared_ptr<swizzle::gfx::Shader>> loadedShaders;
		bool loadShader(const Core::String& name, const swizzle::gfx::ShaderAttributeList& attribs);

	public:
		std::shared_ptr<swizzle::gfx::Shader>& requestShader(const Core::String& name, const Core::String& path = Globals::shaderPath);
		std::shared_ptr<swizzle::gfx::Shader>& requestShader(const Core::String& name, const swizzle::gfx::ShaderAttributeList& attribs, const Core::String& path = Globals::shaderPath);
		bool getResult();

		void requestRemovalOfShader(const Core::String& name);

		Enums::EngineResourceType& getType() const
		{
			return type;
		}
	};
}

#endif