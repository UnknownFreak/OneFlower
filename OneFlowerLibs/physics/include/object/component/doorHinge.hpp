#pragma once

#include <object/component/BaseComponent.hpp>
#include <object/component/Collider.hpp>

#include <physics/physics.hpp>

namespace of::object::component
{
	class DoorHinge : public Base
	{
		virtual void onMessage(const of::object::messaging::Message&) override {};
		virtual void initialize() override;
		virtual void deconstruct() override;


	public:

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