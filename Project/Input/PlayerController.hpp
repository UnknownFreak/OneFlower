#ifndef PlayerController_HPP
#define PlayerController_HPP

#include <component/transform.hpp>
#include <component/combat.hpp>

#include <Input/inputHandler.hpp>
#include <physics/physics.hpp>

namespace of::component
{
	class PlayerController : public Base
	{
		virtual void onMessage(const of::object::messaging::Message& message) override;
		virtual void attached() override;
		virtual void initialize() override;
		virtual void deconstruct() override;

	public:
		void clearBindings();
		Transform* transform = nullptr;
		of::component::CombatComponent* combat = nullptr;
		bool enabled = false;
		physx::PxController* mActor;
		std::weak_ptr<of::input::InputHandler> handler;
		of::physics::ObjectType mColliderType;

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