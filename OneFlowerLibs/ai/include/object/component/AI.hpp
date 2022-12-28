#pragma once

#include <object/component/IBaseComponent.hpp>
#include <ai/AIBehavior.hpp>

namespace of::object::component
{

	class AI : public IBase<AI>
	{
		virtual void onMessage(const messaging::Message& message) override;

	public:

		std::shared_ptr<ai::AIBehavior> behavior;

		AI() = default;
		~AI() = default;

		// Inherited via IBase
		virtual void onCollision(GameObject* the_collidee) override;
		virtual void Update() override;
		virtual void Simulate(const float& fElapsedTime) override;
		virtual void onDeath() override;
	};

}