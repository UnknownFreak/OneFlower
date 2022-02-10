#ifndef RenderComponent_HPP
#define RenderComponent_HPP

#include "Renderable.hpp"
#include <Object/IBaseComponent.hpp>
#include <Object/Transform.hpp>

#include <File/ModFileUUIDHelper.hpp>
#include "Model/IModel.hpp"

class Render : public Renderable, public Component::IBase<Render>
{
	bool initialized = false;
	mutable sf::VertexArray tmpSpriteTest;

	Component::Transform* transform;

	std::shared_ptr<sf::Sprite> sprite;
	std::shared_ptr<sf::Texture> texture;
	std::unique_ptr<IModel> model;

	Core::String textureName;

	ModFileUUIDHelper modelId;

	void loadAndSetModel();

public:
	Render();
	Render(const Render& copy);
	~Render();

	void detach();

	virtual Render* copy() const override
	{
		return new Render(*this);
	}

	virtual std::unique_ptr<Base> ucopy() const override;

	// maybe not needed
	void attachOn(GameObject* go);
	// Inherited via IBase
	virtual void onCollision(Interfaces::ICollider* the_collidee) override;
	virtual void Update() override;
	virtual void Simulate(const float& fElapsedTime) override;
	virtual void onDeath() override;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	template<class Archive>
	void save(Archive& ar) const
	{
		ar(textureName);
		ar(modelId);
	}
	template<class Archive>
	void load(Archive& ar)
	{
		ar(textureName);
		ar(modelId);
		loadAndSetModel();
	}
};

#endif