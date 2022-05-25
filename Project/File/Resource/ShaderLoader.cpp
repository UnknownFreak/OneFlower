#include "ShaderLoader.hpp"

#include <Module\EngineModuleManager.hpp>
#include <Graphics/Window.hpp>
#include <filesystem>

Enums::EngineResourceType Interfaces::IEngineResource<File::Resource::Shader::Loader>::type = Enums::EngineResourceType::ShaderLoader;

namespace File::Resource::Shader
{
	bool Loader::loadShader(const Core::String& name, const swizzle::gfx::ShaderAttributeList& attribs)
	{
		Core::String path = "Data/" + name;
		if (!std::filesystem::exists(path))
		{
			auto& logger = Engine::GetModule <EngineModule::Logger::OneLogger>().getLogger("File::Resource::Shader::Loader");
			logger.Error("Unable to locate shader [" + name + "]", logger.fileInfo(__FILE__, __LINE__));
			return false;
		}
#ifdef _DEBUG
		//MessageBox(0,"Error loading this file",name.c_str(),MB_OK);
#endif
		mtx.lock();
		auto& wnd = Engine::GetModule<Graphics::RenderWindow>();
		loadedShaders.insert(std::make_pair(name, wnd.getSwapchain()->createShader(attribs)));
		auto& shader = loadedShaders[name];
		bool loaded = shader->load(path.c_str());
		if (!loaded)
		{
			auto& logger = Engine::GetModule <EngineModule::Logger::OneLogger>().getLogger("File::Resource::Shader::Loader");
			logger.Error("Unable to load shader [" + name + "]", logger.fileInfo(__FILE__, __LINE__));
		}
		//, path.c_str(), true)));
		mtx.unlock();
		return true;
	}

	std::shared_ptr<swizzle::gfx::Shader>& Loader::requestShader(const Core::String& name, const Core::String& path)
	{
		sw::gfx::ShaderAttributeList attribs = {};
		attribs.mBufferInput = {
			{ sw::gfx::ShaderBufferInputRate::InputRate_Vertex, sizeof(float) * (3U + 3U + 2U) }
		};
		attribs.mAttributes = {
			{ 0U, sw::gfx::ShaderAttributeDataType::vec3f, 0U},
			{ 0U, sw::gfx::ShaderAttributeDataType::vec3f, sizeof(float) * 3U },
			{ 0U, sw::gfx::ShaderAttributeDataType::vec2f, sizeof(float) * 6U }
		};
		attribs.mDescriptors = {
			{swizzle::gfx::DescriptorType::TextureSampler, swizzle::gfx::Count(1u), {swizzle::gfx::StageType::fragmentStage}},
		};
		attribs.mEnableDepthTest = true;
		attribs.mEnableBlending = false;
		return requestShader(name, attribs, path);
	}

	std::shared_ptr<swizzle::gfx::Shader>& Loader::requestShader(const Core::String& name, const swizzle::gfx::ShaderAttributeList& attribs, const Core::String& path)
	{
		if (!name.empty())
		{
			std::unordered_map<Core::String, std::shared_ptr<swizzle::gfx::Shader>>::iterator it;
			it = loadedShaders.find(path + name);
			lastResult = true;
			if (it != loadedShaders.end())
				return it->second;

			if (loadShader(path + name, attribs))
				return loadedShaders.find(path + name)->second;

			//LOW set propper texturename
			it = loadedShaders.find(Globals::shaderPath + missingShader);
			lastResult = false;
			if (it != loadedShaders.end())
				return it->second;
			loadShader(Globals::shaderPath + missingShader, attribs);
			return loadedShaders.find(Globals::shaderPath + missingShader)->second;
		}
		return requestShader(missingShader, attribs, Globals::shaderPath);
	}

	bool Loader::getResult()
	{
		return lastResult;
	}

	void Loader::requestRemovalOfShader(const Core::String& name)
	{
		if (loadedShaders.find(name) != loadedShaders.end())
		{
			auto& logger = Engine::GetModule <EngineModule::Logger::OneLogger>().getLogger("File::Resource::Shader::Loader");
			logger.Info("Unloading shader " + name, logger.fileInfo(__FILE__, __LINE__));
			loadedShaders.erase(name);
		}
	}

}