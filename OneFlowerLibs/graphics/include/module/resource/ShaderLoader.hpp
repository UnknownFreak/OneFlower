#pragma once

#include <unordered_map>
#include <mutex>

#include <utils/common/string.hpp>
#include <swizzle/gfx/Shader.hpp>
#include <swizzle/gfx/Material.hpp>
#include <engine/paths.hpp>

#include <swizzle/gfx/GfxDevice.hpp>
#include <swizzle/gfx/Swapchain.hpp>

namespace of::module::shader
{
	class Loader
	{
		bool lastResult = false;
		std::mutex mtx;
		const common::String missingShader = "default.shader";
		std::unordered_map<common::String, std::weak_ptr<swizzle::gfx::Shader>> loadedShaders;
		std::shared_ptr<swizzle::gfx::Shader> loadShader(const common::String& instanceName, const common::String& name, const swizzle::gfx::ShaderAttributeList& attribs);

		std::weak_ptr<swizzle::gfx::GfxDevice> mGfxDev;
		std::weak_ptr<swizzle::gfx::Swapchain> mSwapchain;

	public:

		Loader(std::weak_ptr<swizzle::gfx::GfxDevice> gfxDev, std::weak_ptr<swizzle::gfx::Swapchain> swapchain);
		Loader& operator=(const Loader&) = delete;

		std::shared_ptr<swizzle::gfx::Shader> requestShader(const common::String& insstanceName, const common::String& shaderName, const common::String& path = engine::path::shaders);
		std::shared_ptr<swizzle::gfx::Shader> requestShader(const common::String& instanceName, const common::String& shaderName, const swizzle::gfx::ShaderAttributeList& attribs, const common::String& path = engine::path::shaders);

		std::shared_ptr<swizzle::gfx::Material> createMaterial(std::shared_ptr<swizzle::gfx::Shader> shader, swizzle::gfx::SamplerMode samplerMode);
		
		bool getResult();

		void requestRemovalOfShader(const common::String& name);
	};

	Loader& get();
}
