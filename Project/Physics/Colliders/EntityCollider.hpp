#ifndef EntityCollider_HPP
#define EntityCollider_HPP

#include <cereal/cereal.hpp>

#include <Object/Transform.hpp>
#include <Interfaces/ICollider.hpp>

class GameObject;
class Collider : public Interfaces::ICollider, public Component::IBase<Collider>
{
	 Component::Transform* transform;
	 float fallTime = 0.f;

public:
	ICollider* floor = nullptr;
	glm::vec2 hitboxOffset;

	Collider();
	Collider(const glm::vec2& size);
	Collider(const glm::vec2& size, const glm::vec2& hitboxOffset);
	Collider(const Collider& copy);
	~Collider();

	virtual Collider* copy() const override
	{
		return new Collider(*this);
	}

	void detach();

	virtual std::unique_ptr<Base> ucopy() const override;

	void attachOn(GameObject* go);

	virtual void doParentSimulate(const float& fElapsedTime) override;
	virtual std::tuple<glm::vec2, bool> Collides(ICollider* other) override;


	// Inherited via IBase
	virtual void onCollision(Interfaces::ICollider* the_collidee) override;
	virtual void Update() override;
	virtual void onDeath() override;

	virtual void postUpdate() override;

	virtual void Simulate(const float& dt) override;

	virtual bool isActive() const override;

	template <class Archive>
	void save(Archive& ar) const
	{
		cereal::base_class<Interfaces::ICollider>(this);
		ar(hitboxOffset.x, hitboxOffset.y);
	}
	template <class Archive>
	void load(Archive& ar)
	{
		cereal::base_class<Interfaces::ICollider>(this);
		ar(hitboxOffset.x, hitboxOffset.y);
	}
};


#endif