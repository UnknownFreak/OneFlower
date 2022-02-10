#ifndef VisionCollider_HPP
#define VisionCollider_HPP

#include <Helpers/Vector3.hpp>
#include <Object/Transform.hpp>
#include <Interfaces/ICollider.hpp>

class GameObject;
class VisionCollider : public Interfaces::ICollider, public Component::IBase<VisionCollider>
{
	Component::Transform* transform;
	bool hitObject = false;
public:
	Core::Vector2f hitboxOffset;

	VisionCollider();
	VisionCollider(const Core::Vector2f& coneSize);
	~VisionCollider();
	virtual VisionCollider* copy() const override
	{
		return new VisionCollider(*this);
	}

	void attachOn(GameObject* go);
	void detach();

	virtual void doParentSimulate(const float& fElapsedTime) override;
	virtual std::tuple<Core::Vector2f, bool> Collides(ICollider* other) override;


	// Inherited via IBase
	virtual void onCollision(Interfaces::ICollider* the_collidee) override;
	void updateColliderPos(const Core::Vector2f& pos, const float& extra_offset);

	// Inherited via IBase
	virtual void Update() override;

	virtual void Simulate(const float& dt) override;
	virtual void onDeath() override;
};


#endif