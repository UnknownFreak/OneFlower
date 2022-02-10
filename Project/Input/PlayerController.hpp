#ifndef PlayerController_HPP
#define PlayerController_HPP

#include <Helpers/Vector3.hpp>
#include <Object/IBaseComponent.hpp>
#include <Object/Transform.hpp>
#include <Combat/Combat.hpp>

#include "InputHandler.hpp"
#include <Graphics/Window.hpp>

namespace Component
{
	struct PlayerController : public Component::IBase<PlayerController>
	{
		Graphics::RenderWindow& window;
		void clearBindings();
		Component::Transform* transform = nullptr;
		Component::CombatComponent* combat = nullptr;
		bool enabled = false;
		Input::InputHandler& handler;

		PlayerController();
		~PlayerController();

		virtual PlayerController* copy() const override
		{
			return new PlayerController(*this);
		}

		virtual std::unique_ptr<Base> ucopy() const override
		{
			return std::make_unique<PlayerController>(*this);
		}

		void disable();
		void enable();

		void attachOn(GameObject* go);

		// Inherited via IBase
		virtual void onCollision(Interfaces::ICollider* the_collidee);
		virtual void Update() override;
		virtual void Simulate(const float& dt) override;
		virtual void onDeath() override;

	};
}

#endif