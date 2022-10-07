#include "Render.hpp"
#include <Object/GameObject.hpp>
#include <File/Asset/Manager.hpp>
#include <Graphics/Window.hpp>

#include <File/Resource/TextureLoader.hpp>
#include <File/Resource/MeshLoader.hpp>
#include <File/Resource/ShaderLoader.hpp>

#include <Physics/Colliders/EntityCollider.hpp>

Enums::ComponentType Component::IBase<Render>::typeID = Enums::ComponentType::Render;
Core::String Component::IBase<Render>::componentName = "Render";

void Render::loadAndSetModel()
{
	auto& wnd = Engine::GetModule<Graphics::RenderWindow>();
	wnd.getCommandBuffer()->begin();
	textureName = "temporary.png";
	meshName = "test.swm";
	shaderName = "simple.shader";

	model = std::make_shared<Graphics::Model>();

	model->mesh = Engine::GetModule<File::Resource::Mesh::Loader>().requestMesh(meshName);
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

	initialized = true;
	wnd.getCommandBuffer()->end();
	auto buf = wnd.getCommandBuffer();
	wnd.getGfxContext()->submit(&buf, 1, nullptr);
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
	model->material->setDescriptorTextureResource(0u, model->texture);
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