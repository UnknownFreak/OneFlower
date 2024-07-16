#include "SkyBox.hpp"

#include <logger/Logger.hpp>

#include <module/resource/MeshLoader.hpp>
#include <module/resource/TextureLoader.hpp>
#include <module/resource/ShaderLoader.hpp>

#include <module/window/GraphicsProxy.hpp>

namespace of::graphics::sky
{


	Skybox::Skybox() : mModel(), loaded(false)
	{
	}

	Skybox::Skybox(const of::common::String& skyboxTextureFolder) : Skybox()
	{
		if (skyboxTextureFolder.empty())
			return;
		setSkyBox(skyboxTextureFolder);
	}

	void Skybox::setSkyBox(const of::common::String& skyboxTextureFolder)
	{
		of::engine::GetModule<of::logger::Logger>().getLogger("Graphics::Skybox").Info("Loading skybox");
		loaded = false;

		swizzle::gfx::ShaderAttributeList attribs = {};
		attribs.mBufferInput = {
			{ swizzle::gfx::ShaderBufferInputRate::InputRate_Vertex, sizeof(float) * (3U + 3U + 2U) }
		};
		attribs.mAttributes = {
			{ 0U, swizzle::gfx::ShaderAttributeDataType::vec3f, 0U},
			{ 0U, swizzle::gfx::ShaderAttributeDataType::vec3f, sizeof(float) * 3U },
			{ 0U, swizzle::gfx::ShaderAttributeDataType::vec2f, sizeof(float) * 6U }
		};
		attribs.mDescriptors = {
			{swizzle::gfx::DescriptorType::TextureSampler, swizzle::gfx::Count(1u), {swizzle::gfx::StageType::fragmentStage}},
		};
		attribs.mPushConstantSize = sizeof(glm::mat4) * 4u;
		attribs.mEnableDepthTest = false;
		attribs.mEnableBlending = false;
		
		auto& wnd = of::engine::GetModule<of::module::window::Proxy>();

		mModel = of::engine::GetModule<of::module::mesh::Loader>().requestModel("inverted_sphere.obj");

		mModel.shader = of::engine::GetModule<of::module::shader::Loader>().requestShader("sky.shader", "sky.shader", attribs);
		
		mModel.texture = of::engine::GetModule<of::module::texture::Loader>().requestCubemapTexture(skyboxTextureFolder + "/");
		
		mModel.material = wnd.getGfxDevice()->createMaterial(mModel.shader, swizzle::gfx::SamplerMode::SamplerModeClamp);
		
		mModel.material->setDescriptorTextureResource(0, mModel.texture);

		loaded = true;
		of::engine::GetModule<of::logger::Logger>().getLogger("Graphics::Skybox").Info("Finished loading skybox");

	}

	void Skybox::render(std::unique_ptr<swizzle::gfx::DrawCommandTransaction>& trans, view::MVP& mvp)
	{
		if (loaded)
		{
			mModel.renderNoIndex(trans, mvp);
		}
	}
	void Skybox::updateFrame(const float )
	{
	}
}