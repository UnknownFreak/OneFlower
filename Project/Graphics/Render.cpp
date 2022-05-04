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

	texture = Engine::GetModule<File::Resource::Texture::Loader>().requestTexture(textureName);
	sprite = std::make_shared<sf::Sprite>(*texture.get());
	if (!modelId.uuid.is_nil())
	{
		model = std::unique_ptr<IModel>(Engine::GetModule<File::Asset::Manager>().requestor.requestUniqueInstancePtr<IModel>(modelId));
		model->setRenderSprite(sprite);
	}

	tmpSpriteTest.append(sf::Vertex({ transform->pos.x, transform->pos.y }, { 0, 0 }));
	tmpSpriteTest.append(sf::Vertex({ transform->pos.x, transform->pos.y + 48.f }, { 0, 48 }));
	tmpSpriteTest.append(sf::Vertex({ transform->pos.x + 32.f, transform->pos.y + 48.f }, { 32, 48 }));
	tmpSpriteTest.append(sf::Vertex({ transform->pos.x + 32.f, transform->pos.y }, { 32, 0 }));
	initialized = true;
}

Render::Render() : Renderable({ 0,0,16.f,16.f }), tmpSpriteTest(sf::PrimitiveType::Quads)
{
}

Render::Render(const Render& copy) : Renderable(copy), tmpSpriteTest(copy.tmpSpriteTest.getPrimitiveType())
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
	if (!initialized)
		return;
	auto pos = transform->pos.toVector2();
	if (model)
	{
		model->setPosition({ pos.x, pos.y + (transform->pos.z * Globals::Z_OFFSET) });
	}
	drawBox.x = pos.x;
	drawBox.y = pos.y + (transform->pos.z * Globals::Z_OFFSET);

	tmpSpriteTest[0].position = sf::Vector2f(pos.x, pos.y + (transform->buffered.z * Globals::Z_OFFSET));
	tmpSpriteTest[1].position = sf::Vector2f(pos.x, pos.y + (transform->buffered.z * Globals::Z_OFFSET)) + tmpSpriteTest[1].texCoords;
	tmpSpriteTest[2].position = sf::Vector2f(pos.x, pos.y + (transform->buffered.z * Globals::Z_OFFSET)) + tmpSpriteTest[2].texCoords;
	tmpSpriteTest[3].position = sf::Vector2f(pos.x, pos.y + (transform->buffered.z * Globals::Z_OFFSET)) + tmpSpriteTest[3].texCoords;
}

void Render::Simulate(const float& fElapsedTime)
{
	if (model)
	{
		model->updateFrame(fElapsedTime);
	}
}

void Render::onDeath()
{
	if (model.get())
	{
		model->setAnimation("onDeath");
	}
}

void Render::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// TODO: change to check renderMode instead combined with objectState
	if (!initialized || (attachedOn && attachedOn->objectState == Enums::ObjectState::Inactive))
		return;
	if (model.get())
	{
		model.get()->preRender(0);
		// dont think needed
		// model->setPosition({ newPos.x, newPos.y + (bufferedZ * Globals::Z_OFFSET) });
		target.draw(*(model.operator->()), states);
	}
	else
	{
		auto pos = transform->pos.toVector2();

		//sf::RectangleShape r({ 32.f, 32.f });
		//r.setPosition(pos.x, pos.y + (transform->buffered.z * Globals::Z_OFFSET));// -(drawZ * Globals::Z_OFFSET));
		//r.setFillColor(sf::Color::Blue);
		////sprite->setPosition(pos.x, pos.y + (transform->buffered.z * Globals::Z_OFFSET));
		////target.draw(*sprite, states);
		//target.draw(r, states);

		const sf::Texture* origTexture = states.texture;
		states.texture = texture.get();
		target.draw(tmpSpriteTest, states);
		states.texture = origTexture;
	}
}