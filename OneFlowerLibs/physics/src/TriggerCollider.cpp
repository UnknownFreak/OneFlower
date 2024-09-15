#include <component/triggerCollider.hpp>

#include <component/transform.hpp>
#include <object/GameObject.hpp>


#include <logger/Logger.hpp>
#include <module/resource/MeshLoader.hpp>

namespace of::component
{
	void TriggerCollider::attached()
	{
		mColliderInfoType.objectId = attachedOn->id;
		mColliderInfoType.hitType = of::physics::PxColliderType::ObjectTrigger;
		mColliderInfoType.go = attachedOn;

		if (mColliderType == Collider::ColliderType::STATIC)
		{
			auto model = of::module::mesh::get().requestModel(mColliderMesh,
				of::engine::path::meshes, true);

			auto transform = attachedOn->get<Transform>();

			mActor = of::physics::get().createActor<physx::PxRigidStatic>(
				transform->pos, model, true);
			mActor->userData = attachedOn;
		}
		else if (mColliderType == Collider::ColliderType::INHERIT)
		{
			auto collider = attachedOn->get<Collider>();
			
			if (collider != nullptr)
			{
				mActor = collider->mActor;
				if (mColliderShapeType == ShapeType::MESH)
				{
					auto model = of::module::mesh::get().requestModel(mColliderMesh,
						of::engine::path::meshes, true);
					of::physics::get().attachTriggerShape(mActor, model, mTriggerShapeOffset, mTriggerShapeScale);
				}
				else if (mColliderShapeType == ShapeType::BOX)
				{
					of::physics::get().attachBoxTriggerShape(mActor, mTriggerShapeOffset, mTriggerShapeScale);
				}
				else
				{
					of::physics::get().attachCylinderTriggerShape(mActor, mTriggerShapeOffset, mTriggerShapeScale);
				}
			}
			else
			{
				of::logger::get().getLogger("of::object::component::TriggerCollider").Warning("Trying to create a trigger collider with inherit, but no collider to inherit the actor from. No collider will be created!");

			}
		}
		else if (mColliderType == Collider::ColliderType::RIGID)
		{
			of::logger::get().getLogger("of::object::component::TriggerCollider").Warning("Trying to create a trigger collider with type rigid, this is not supported for trigger colliders, use colliderType inherit instead, as that allows the trigger collider to attach it's shape to the rigid actor.");
		}
		else if (mColliderType == Collider::ColliderType::NONE)
		{
			of::logger::get().getLogger("of::object::component::TriggerCollider").Info("mColliderType is set to NONE, no collider will be created, is this intended?");
		}

		if (mActor != nullptr)
		{
			mActor->userData = &mColliderInfoType;
		}
	}

	void TriggerCollider::initialize()
	{

	}

	void TriggerCollider::deconstruct()
	{
		if (of::physics::get().hasShutDown() == false)
		{
			if (mColliderType == Collider::ColliderType::STATIC)
			{
				if (of::physics::get().hasShutDown() == false && mActor != nullptr)
				{
					mActor->release();
				}
			}
		}
		mActor = nullptr;
	}
}