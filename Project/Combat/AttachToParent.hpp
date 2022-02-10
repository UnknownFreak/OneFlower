#ifndef AttachToParent_HPP
#define AttachToParent_Hpp

#include <Object/IBaseComponent.hpp>

namespace Component
{

	class AttachToParent : public IBase<AttachToParent>
	{
		GameObject* objectToFollow;
	public:
		AttachToParent(GameObject* objectToFollow);

		// Inherited via IBase
		virtual void onCollision(Interfaces::ICollider* the_collidee) override;
		virtual void Update() override;
		virtual void Simulate(const float& fElapsedTime) override;
		virtual void onDeath();
	};
}

#endif