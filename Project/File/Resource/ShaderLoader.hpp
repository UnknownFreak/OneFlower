#ifndef ShaderLoader_HPP
#define ShaderLoader_HPP

#include <swizzle/gfx/Shader.hpp>

#include <utils/common/string.hpp>
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
		const of::common::String missingShader = "default.shader";
		std::unordered_map<of::common::String, std::shared_ptr<swizzle::gfx::Shader>> loadedShaders;
		bool loadShader(const of::common::String& name, const swizzle::gfx::ShaderAttributeList& attribs);

	public:
		std::shared_ptr<swizzle::gfx::Shader>& requestShader(const of::common::String& name, const of::common::String& path = Globals::shaderPath);
		std::shared_ptr<swizzle::gfx::Shader>& requestShader(const of::common::String& name, const swizzle::gfx::ShaderAttributeList& attribs, const of::common::String& path = Globals::shaderPath);
		bool getResult();

		void requestRemovalOfShader(const of::common::String& name);

		Enums::EngineResourceType& getType() const
		{
			return type;
		}
	};
}

#endif