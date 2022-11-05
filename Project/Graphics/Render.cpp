#include "Render.hpp"
#include <Object/GameObject.hpp>
#include <File/Asset/Manager.hpp>
#include <Graphics/Window.hpp>

#include <File/Resource/TextureLoader.hpp>
#include <File/Resource/MeshLoader.hpp>
#include <File/Resource/ShaderLoader.hpp>

Enums::ComponentType Component::IBase<Render>::typeID = Enums::ComponentType::Render;
Core::String Component::IBase<Render>::componentName = "Render";

void Render::loadAndSetModel()
{
	auto& wnd = Engine::GetModule<Graphics::RenderWindow>();
	//auto temp = wnd.getUploadBuffer();
	//auto trans = temp->begin();
	auto gfx = wnd.getGfxContext();

	textureName = "temporary.png";
	meshName = "test.swm";
	shaderName = "simple.shader";

	model = std::make_shared<Graphics::Model>();

	model->mesh = Engine::GetModule<File::Resource::Mesh::Loader>().requestMesh(meshName);
	{

		model->mMeshBuffer = gfx->createBuffer(swizzle::gfx::BufferType::Vertex);
		model->mIndexBuffer = gfx->createBuffer(swizzle::gfx::BufferType::Index);
		model->mBoneBuffer = gfx->createBuffer(swizzle::gfx::BufferType::UniformBuffer);
		model->mMeshBuffer->setBufferData((U8*)model->mesh->getVertexDataPtr(), model->mesh->getVertexDataSize(),
			sizeof(float) * (3u + 3u + 2u + 4u + 4u));

		model->mIndexBuffer->setBufferData((U8*)model->mesh->getIndexDataPtr(), model->mesh->getIndexDataSize(), sizeof(U32) * 3u);

		model->mBoneBuffer->setBufferData((U8*)model->mesh->getAnimationDataPtr(0, 0), model->mesh->getNumberOfBones() * sizeof(glm::mat4),
			sizeof(glm::mat4));

	}

	if (Engine::GetModule<File::Resource::Mesh::Loader>().getResult() == false)
	{
		model->texture = Engine::GetModule<File::Resource::Texture::Loader>().requestTexture("missingMeshTexture.png");
	}
	else
		model->texture = Engine::GetModule<File::Resource::Texture::Loader>().requestTexture(textureName);
	model->shader = Engine::GetModule<File::Resource::Shader::Loader>().requestShader(shaderName);
	auto gfxContext = Engine::GetModule<Graphics::RenderWindow>().getGfxContext();

	model->material = gfxContext->createMaterial(model->shader);

	model->material->setDescriptorTextureResource(0u, model->texture);
	model->material->setDescriptorBufferResource(1u, model->mBoneBuffer, ~0ull);

	initialized = true;
	//wnd.getCommandBuffer()->end(std::move(trans));
	//wnd.getGfxContext()->submit(&temp, 1, nullptr);
}

Render::~Render()
{
	detach();
}

void Render::detach()
{
	if (attachedOn)
	{
		Engine::GetModule<Graphics::RenderWindow>().RemoveRenderable(attachedOn);
		attachedOn = nullptr;
	}
}

std::unique_ptr<Component::Base> Render::ucopy() const
{
	return std::make_unique<Render>(*this);
}

void Render::attachOn(GameObject* go)
{
	Render::Base::attachOn(go);
	//go->getComponent<Collider>()->hitboxOffset = { 8.f, 32.f };
	loadAndSetModel();
	transform = go->getComponent<Component::Transform>();
	Engine::GetModule<Graphics::RenderWindow>().AddRenderable(go);
}

void Render::onCollision(Interfaces::ICollider*)
{
}

void Render::Update()
{
	//model->material->setDescriptorTextureResource(0u, model->texture);
}

void Render::Simulate(const float& fElapsedTime)
{
	fElapsedTime;
	if (model)
	{
		//model->mesh->updateFrame(fElapsedTime);
	}
}

void Render::onDeath()
{
	if (model.get())
	{
//		model->setAnimation("onDeath");
	}
}