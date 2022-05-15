#ifndef VisionCollider_HPP
#define VisionCollider_HPP

#include <glm/vec2.hpp>
#include <Object/Transform.hpp>
#include <Interfaces/ICollider.hpp>

class GameObject;
class VisionCollider : public Interfaces::ICollider, public Component::IBase<VisionCollider>
{
	Component::Transform* transform;
	bool hitObject = false;
public:
	glm::vec2 hitboxOffset;

	VisionCollider();
	VisionCollider(const glm::vec2& coneSize);
	~VisionCollider();
	virtual VisionCollider* copy() const override
	{
		return new VisionCollider(*this);
	}

	void attachOn(GameObject* go);
	void detach();

	virtual void doParentSimulate(const float& fElapsedTime) override;
	virtual std::tuple<glm::vec2, bool> Collides(ICollider* other) override;


	// Inherited via IBase
	virtual void onCollision(Interfaces::ICollider* the_collidee) override;
	void updateColliderPos(const glm::vec3& pos, const float& extra_offset);

	// Inherited via IBase
	virtual void Update() override;

	virtual void Simulate(const float& dt) override;
	virtual void onDeath() override;

	virtual bool isActive() const override;

};


#endif