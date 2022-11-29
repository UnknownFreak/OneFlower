#ifndef RenderComponent_HPP
#define RenderComponent_HPP

#include <Object/IBaseComponent.hpp>
#include <Object/Transform.hpp>

#include <File/Mod/ModFileUUIDHelper.hpp>
#include "Model.hpp"

class Render : public Component::IBase<Render>
{
	bool initialized = false;

	Component::Transform* transform;

	of::common::String textureName;
	of::common::String meshName;
	of::common::String shaderName;

	void loadAndSetModel();

public:
	std::shared_ptr<Graphics::Model> model;

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
	virtual void onCollision(GameObject* the_collidee) override;
	virtual void Update() override;
	virtual void Simulate(const float& fElapsedTime) override;
	virtual void onDeath() override;

	template<class Archive>
	void save(Archive& ar) const
	{
		ar(textureName);
		ar(meshName);
		ar(shaderName);
	}
	template<class Archive>
	void load(Archive& ar)
	{
		ar(textureName);
		ar(meshName);
		ar(shaderName);
		loadAndSetModel();
	}
};

#endif