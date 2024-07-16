#include <module/resource/ShaderLoader.hpp>

#include <filesystem>

#include <glm/glm.hpp>
#include <swizzle/gfx/Shader.hpp>

#include <logger/Logger.hpp>
#include <module/window/GraphicsProxy.hpp>

of::module::EngineResourceType of::module::interface::IEngineResource<of::module::shader::Loader>::type = of::module::EngineResourceType::ShaderLoader;

namespace of::module::shader
{
	bool Loader::loadShader(const common::String& instanceName, const common::String& name, const swizzle::gfx::ShaderAttributeList& attribs)
	{
		common::String path = "Data/" + name;
		if (!std::filesystem::exists(path))
		{
			auto& logger = engine::GetModule <logger::Logger>().getLogger("shader::Loader");
			logger.Error("Unable to locate shader [" + name + "]", logger.fileInfo(__FILE__, __LINE__));
			return false;
		}
#ifdef _DEBUG
		//MessageBox(0,"Error loading this file",name.c_str(),MB_OK);
#endif
		mtx.lock();
		auto& wnd = engine::GetModule<window::Proxy>();
		loadedShaders.insert(std::make_pair(instanceName, wnd.getGfxDevice()->createShader(wnd.getSwapchain(), swizzle::gfx::ShaderType::ShaderType_Graphics, attribs)));
		auto& shader = loadedShaders[instanceName];
		bool loaded = shader->load(path.c_str());
		if (!loaded)
		{
			auto& logger = engine::GetModule <logger::Logger>().getLogger("shader::Loader");
			logger.Error("Unable to load shader [" + name + "]", logger.fileInfo(__FILE__, __LINE__));
		}
		//, path.c_str(), true)));
		mtx.unlock();
		return true;
	}

	std::shared_ptr<swizzle::gfx::Shader>& Loader::requestShader(const common::String& insstanceName, const common::String& shaderName, const common::String& path)
	{
		swizzle::gfx::ShaderAttributeList attribs = {};
		attribs.mBufferInput = {
			{ swizzle::gfx::ShaderBufferInputRate::InputRate_Vertex, sizeof(float) * (3U + 3U + 2U) }
			//{ sw::gfx::ShaderBufferInputRate::InputRate_Vertex, sizeof(float) * (3U + 3U + 2U + 4u + 4u) },
			//{ sw::gfx::ShaderBufferInputRate::InputRate_Instance, sizeof(float) * (16u) },
		};

		attribs.mAttributes = {
			{ 0U, swizzle::gfx::ShaderAttributeDataType::vec3f, 0U},
			{ 0U, swizzle::gfx::ShaderAttributeDataType::vec3f, sizeof(float) * 3U },
			{ 0U, swizzle::gfx::ShaderAttributeDataType::vec2f, sizeof(float) * 6U }
			//{0u, swizzle::gfx::ShaderAttributeDataType::vec3f, 0u},
			//{0u, swizzle::gfx::ShaderAttributeDataType::vec3f, sizeof(float) * 3u},
			//{0u, swizzle::gfx::ShaderAttributeDataType::vec2f, sizeof(float) * 6u},
			//{0u, swizzle::gfx::ShaderAttributeDataType::vec4u, sizeof(float) * 8u},
			//{0u, swizzle::gfx::ShaderAttributeDataType::vec4f, sizeof(float) * 12u},
			//{1u, swizzle::gfx::ShaderAttributeDataType::vec4f, 0u},
			//{1u, swizzle::gfx::ShaderAttributeDataType::vec4f, sizeof(float) * 4u},
			//{1u, swizzle::gfx::ShaderAttributeDataType::vec4f, sizeof(float) * 8u},
			//{1u, swizzle::gfx::ShaderAttributeDataType::vec4f, sizeof(float) * 12u},
		};
		attribs.mDescriptors = {
			{swizzle::gfx::DescriptorType::TextureSampler, swizzle::gfx::Count(1u), {swizzle::gfx::StageType::fragmentStage}},
			{swizzle::gfx::DescriptorType::UniformBuffer, swizzle::gfx::Count(1u), {swizzle::gfx::StageType::fragmentStage}},
			//{swizzle::gfx::DescriptorType::UniformBuffer, swizzle::gfx::Count(1u), {swizzle::gfx::StageType::fragmentStage, swizzle::gfx::StageType::vertexStage}},
		};
		attribs.mEnableDepthTest = true;
		attribs.mEnableDepthWrite = true;
		attribs.mEnableBlending = false;
		attribs.mPushConstantSize = sizeof(glm::mat4)*4u;
		attribs.mPrimitiveType = swizzle::gfx::PrimitiveType::triangle;
		return requestShader(insstanceName, shaderName, attribs, path);
	}

	std::shared_ptr<swizzle::gfx::Shader>& Loader::requestShader(const common::String& instanceName, const common::String& shaderName, const swizzle::gfx::ShaderAttributeList& attribs, const common::String& path)
	{
		if (!shaderName.empty() && !instanceName.empty())
		{
			std::unordered_map<common::String, std::shared_ptr<swizzle::gfx::Shader>>::iterator it;
			it = loadedShaders.find(instanceName);
			lastResult = true;
			if (it != loadedShaders.end())
				return it->second;

			if (loadShader(instanceName, path + shaderName, attribs))
				return loadedShaders.find(instanceName)->second;

			//LOW set propper texturename
			it = loadedShaders.find("missingShader");
			lastResult = false;
			if (it != loadedShaders.end())
				return it->second;
			loadShader("missing", Settings::shaderPath + missingShader, attribs);
			return loadedShaders.find("missing")->second;
		}
		return requestShader("missing", missingShader, attribs, Settings::shaderPath);
	}

	bool Loader::getResult()
	{
		return lastResult;
	}

	void Loader::requestRemovalOfShader(const common::String& name)
	{
		if (loadedShaders.find(name) != loadedShaders.end())
		{
			auto& logger = engine::GetModule <logger::Logger>().getLogger("shader::Loader");
			logger.Info("Unloading shader " + name, logger.fileInfo(__FILE__, __LINE__));
			loadedShaders.erase(name);
		}
	}

}