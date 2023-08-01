#pragma once

#include <object/component/BaseComponent.hpp>
#include <object/component/Collider.hpp>

#include <physics/physics.hpp>

namespace of::object::component
{
	class TriggerCollider : public Base
	{
		virtual void onMessage(const of::object::messaging::Message& message) override {};
		virtual void initialize() override;
		virtual void deconstruct() override;


	public:

		Collider::ColliderType mColliderType = Collider::ColliderType::INHERIT;
		enum class ShapeType
		{
			MESH,
			CYLINDER,
		} mColliderShapeType;

		of::common::String mColliderMesh;

		// trigger shapes has to be 1x or larger than collider mesh;
		float mTriggerShapeScale;

		physx::PxRigidActor* mActor;

		TriggerCollider() = default;
		~TriggerCollider() = default;

		virtual TriggerCollider* copy() const override
		{
			return new TriggerCollider(*this);
		}

		virtual std::unique_ptr<Base> ucopy() const override
		{
			return std::make_unique<TriggerCollider>(*this);
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
			return "TriggerCollider";
		};

		static constexpr of::common::uuid typeId = "4eb8d991-d06e-4231-b3bc-82e4b5d5199d";
	};
}