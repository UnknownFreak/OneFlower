#include "Render.hpp"
#include <Object/GameObject.hpp>
#include <File/Asset/Manager.hpp>
#include <Graphics/Window.hpp>
#include <File/Resource/TextureLoader.hpp>

#include <Physics/Colliders/EntityCollider.hpp>

Enums::ComponentType Component::IBase<Render>::typeID = Enums::ComponentType::Render;
Core::String Component::IBase<Render>::componentName = "Render";

void Render::loadAndSetModel()
{
	textureName = "temporary.png";

	model = std::make_shared<Graphics::Model>();

	model->texture = Engine::GetModule<File::Resource::Texture::Loader>().requestTexture(textureName);
//	model->material = ...;
//	model->shader = ...;

//	model->mesh = ...;

	initialized = true;
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
	transform = go->getComponent<Component::Transform>();
	Engine::GetModule<Graphics::RenderWindow>().AddRenderable(go);
	//go->getComponent<Collider>()->hitboxOffset = { 8.f, 32.f };
	loadAndSetModel();
}

void Render::onCollision(Interfaces::ICollider*)
{
}

void Render::Update()
{
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