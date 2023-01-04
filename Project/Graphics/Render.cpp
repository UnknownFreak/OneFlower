#include "Render.hpp"
#include <Object/GameObject.hpp>
#include <Graphics/Window.hpp>

#include <module/resource/TextureLoader.hpp>
#include <module/resource/MeshLoader.hpp>
#include <module/resource/ShaderLoader.hpp>

using namespace of::object;

void Render::loadAndSetModel()
{
	auto& wnd = of::engine::GetModule<Graphics::RenderWindow>();
	//auto temp = wnd.getUploadBuffer();
	//auto trans = temp->begin();
	auto gfx = wnd.getGfxContext();

	textureName = "temporary.png";
	meshName = "test.swm";
	shaderName = "simple.shader";

	model = std::make_shared<Graphics::Model>();

	model->mesh = of::engine::GetModule<of::module::mesh::Loader>().requestMesh(meshName);
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

	if (of::engine::GetModule<of::module::mesh::Loader>().getResult() == false)
	{
		model->texture = of::engine::GetModule<of::module::texture::Loader>().requestTexture("missingMeshTexture.png");
	}
	else
		model->texture = of::engine::GetModule<of::module::texture::Loader>().requestTexture(textureName);
	model->shader = of::engine::GetModule<of::module::shader::Loader>().requestShader(shaderName);
	auto gfxContext = of::engine::GetModule<Graphics::RenderWindow>().getGfxContext();

	model->material = gfxContext->createMaterial(model->shader);

	model->material->setDescriptorTextureResource(0u, model->texture);
	model->material->setDescriptorBufferResource(1u, model->mBoneBuffer, ~0ull);

	initialized = true;
	//wnd.getCommandBuffer()->end(std::move(trans));
	//wnd.getGfxContext()->submit(&temp, 1, nullptr);
}

void Render::onMessage(const of::object::messaging::Message&)
{
}

Render::~Render()
{
	detach();
}

void Render::detach()
{
	if (attachedOn)
	{
		of::engine::GetModule<Graphics::RenderWindow>().RemoveRenderable(attachedOn);
		attachedOn = nullptr;
	}
}

std::unique_ptr<of::object::component::Base> Render::ucopy() const
{
	return std::make_unique<Render>(*this);
}

void Render::attachOn(of::object::GameObject* go)
{
	Render::Base::attachOn(go);
	//go->getComponent<Collider>()->hitboxOffset = { 8.f, 32.f };
	loadAndSetModel();
	transform = go->get<of::object::component::Transform>();
	of::engine::GetModule<Graphics::RenderWindow>().AddRenderable(go);
}

void Render::onCollision(of::object::GameObject*)
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