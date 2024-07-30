#pragma once

#include <component/base.hpp>
#include <component/collider.hpp>

#include <physics/physics.hpp>

namespace of::component
{
	class TriggerCollider : public Base
	{
		virtual void onMessage(const of::object::messaging::Message&) override {};
		virtual void attached() override;
		virtual void initialize() override;
		virtual void deconstruct() override;


	public:

		Collider::ColliderType mColliderType = Collider::ColliderType::INHERIT;
		enum class ShapeType
		{
			MESH,
			CYLINDER,
			BOX,
		} mColliderShapeType;

		of::common::String mColliderMesh;

		// trigger shapes has to be 1x or larger than collider mesh;
		glm::vec3 mTriggerShapeScale;
		glm::vec3 mTriggerShapeOffset = glm::vec3(0.f);

		physx::PxRigidActor* mActor = nullptr;

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

		static constexpr of::common::uuid typeId = "c2667abd-0783-4746-92d1-0b41c5e513ef";
	private:
		of::module::physics::ObjectType mColliderInfoType;

	};
}