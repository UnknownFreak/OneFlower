#pragma once

#include <component/base.hpp>
#include <component/collider.hpp>

#include <physics/physics.hpp>

namespace of::component
{
	class DoorHinge : public Base
	{
	public:
		virtual void onMessage(const of::object::messaging::Message& m) override 
		{
			if (m.messageTopic == of::object::messaging::Topic::of(of::object::messaging::Topics::TOGGLE_STATE))
			{
				dir = -dir;
				mActor->is<physx::PxRigidDynamic>()->clearTorque(physx::PxForceMode::eVELOCITY_CHANGE);
			}
		};

		virtual void attached() override;
		virtual void initialize() override;
		virtual void deconstruct() override;


	public:

		float dir = 0.8f;

		glm::vec3 mHingeOffset;

		physx::PxRigidActor* mActor;
		physx::PxD6Joint* mHinge;

		DoorHinge() = default;
		~DoorHinge() = default;

		virtual DoorHinge* copy() const override
		{
			return new DoorHinge(*this);
		}

		virtual std::unique_ptr<Base> ucopy() const override
		{
			return std::make_unique<DoorHinge>(*this);
		}

		void persist(of::object::ObjectSaveState*) override {};
		void onReconstruct(of::object::ObjectSaveState*) override {};
		void resolveReferences() override {};

		of::common::uuid getType() const override
		{
			return typeId;
		};

		of::common::String getTypeName() const override
		{
			return "DoorHinge";
		};

		static constexpr of::common::uuid typeId = "734239fd-57c0-462e-b767-b4be18d6c452";
	};
}