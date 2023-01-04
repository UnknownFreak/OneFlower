#ifndef PlayerController_HPP
#define PlayerController_HPP

#include <Object/component/IBaseComponent.hpp>
#include <Object/component/Transform.hpp>
#include <Combat/Combat.hpp>

#include "InputHandler.hpp"
#include <Graphics/Window.hpp>

namespace of::object::component
{
	class PlayerController : public Base
	{
		virtual void onMessage(const of::object::messaging::Message& message) override;
	public:
		Graphics::RenderWindow& window;
		void clearBindings();
		Transform* transform = nullptr;
		of::object::component::CombatComponent* combat = nullptr;
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
		virtual void onCollision(GameObject* the_collidee);
		virtual void Update() override;
		virtual void Simulate(const float& dt) override;
		virtual void onDeath() override;

		void persist(of::object::ObjectSaveState*) override {};
		void onReconstruct(of::object::ObjectSaveState*) override {};
		void resolveReferences() override {};

		of::common::uuid getType() const override
		{
			return typeId;
		};

		of::common::String getTypeName() const override
		{
			return "PlayerController";
		};

		static constexpr of::common::uuid typeId = "4eb8d991-d06e-4231-b3bc-82e4b5d5199d";
	};
}

#endif