#ifndef RenderComponent_HPP
#define RenderComponent_HPP

#include <object/component/Transform.hpp>

#include <file/FileId.hpp>
#include "Model.hpp"

class Render : public of::object::component::Base
{
	bool initialized = false;

	of::object::component::Transform* transform;

	of::common::String textureName;
	of::common::String meshName;
	of::common::String shaderName;

	void loadAndSetModel();

	virtual void onMessage(const of::object::messaging::Message& message) override;

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
	void attachOn(of::object::GameObject* go);
	// Inherited via IBase
	virtual void onCollision(of::object::GameObject* the_collidee) override;
	virtual void Update() override;
	virtual void Simulate(const float& fElapsedTime) override;
	virtual void onDeath() override;

	void persist(of::object::ObjectSaveState*) override {};
	void onReconstruct(of::object::ObjectSaveState*) override {};
	void resolveReferences() override {};

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

	of::common::uuid getType() const override
	{
		return typeId;
	};

	of::common::String getTypeName() const override
	{
		return "Render";
	};

	static constexpr of::common::uuid typeId = "206d37a1-aa09-44ff-bd7b-bfdd4b5a4b87";
};

#endif