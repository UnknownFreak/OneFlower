#pragma once

#include <object/component/BaseComponent.hpp>
#include <object/component/Transform.hpp>
#include <physics/physics.hpp>

namespace of::object::component
{
	class Collider : public Base
	{

		virtual void onMessage(const of::object::messaging::Message&) override {};
		virtual void initialize() override;
		virtual void deconstruct() override;

	public:

		enum class ColliderType
		{
			STATIC,
			RIGID,
			INHERIT,
			NONE,
		} mColliderType = ColliderType::NONE;

		of::common::String mColliderMesh;

		Transform* mTransform = nullptr;
		physx::PxRigidActor* mActor;

		Collider() = default;
		~Collider() = default;

		virtual Collider* copy() const override
		{
			return new Collider(*this);
		}

		virtual std::unique_ptr<Base> ucopy() const override
		{
			return std::make_unique<Collider>(*this);
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
			return "Collider";
		};

		static constexpr of::common::uuid typeId = "dfee5083-fe04-4ef9-97ba-a9bf564e8073";
	};
}