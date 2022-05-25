#include "SkyBox.hpp"

#include <File/Resource/MeshLoader.hpp>
#include <File/Resource/TextureLoader.hpp>
#include <File/Resource/ShaderLoader.hpp>

#include <swizzle/asset/TextureLoader.hpp>

#include "Window.hpp"

namespace Graphics
{


	Skybox::Skybox() : mModel(std::make_shared<Model>())
	{
	}

	Skybox::Skybox(const Core::String& skyboxTextureFolder) : Skybox()
	{
		setSkyBox(skyboxTextureFolder);
	}

	void Skybox::setSkyBox(const Core::String& skyboxTextureFolder)
	{
		Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("Graphics::Skybox").Info("Loading skybox");

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
		
		auto& wnd = Engine::GetModule<Graphics::RenderWindow>();
		mModel->shader = Engine::GetModule<File::Resource::Shader::Loader>().requestShader("sky.shader", attribs);
		
		mModel->texture = Engine::GetModule<File::Resource::Texture::Loader>().requestCubemapTexture(skyboxTextureFolder + "/");
		
		mModel->material = wnd.getGfxContext()->createMaterial(mModel->shader);
		
		mModel->material->setDescriptorTextureResource(0, mModel->texture);

		mModel->mesh = Engine::GetModule<File::Resource::Mesh::Loader>().requestMesh("inverted_sphere.obj");
		
		loaded = true;
		Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("Graphics::Skybox").Info("Finished loading skybox");

	}

	void Skybox::render(std::shared_ptr<swizzle::gfx::CommandBuffer> buffer, MVP mvp)
	{
		if (loaded)
		{
			buffer->bindShader(mModel->shader);
			buffer->bindMaterial(mModel->shader, mModel->material);
			buffer->setShaderConstant(mModel->shader, (U8*)&mvp, sizeof(mvp));
			buffer->draw(mModel->mesh.mVertexBuffer);
		}
	}
}