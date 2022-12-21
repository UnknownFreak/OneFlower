#ifndef AttachToParent_HPP
#define AttachToParent_Hpp

#include <object/component/IBaseComponent.hpp>

namespace of::object::component
{

	class AttachToParent : public IBase<AttachToParent>
	{
		GameObject* objectToFollow;
	public:
		AttachToParent(GameObject* objectToFollow);

		// Inherited via IBase
		virtual void onCollision(GameObject* the_collidee) override;
		virtual void Update() override;
		virtual void Simulate(const float& fElapsedTime) override;
		virtual void onDeath();

		virtual void onMessage(const messaging::Message& message) override;

	};
}

#endif