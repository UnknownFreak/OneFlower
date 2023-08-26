#include <object/component/TriggerCollider.hpp>

#include <object/component/Transform.hpp>
#include <object/GameObject.hpp>


#include <module/logger/OneLogger.hpp>
#include <module/resource/MeshLoader.hpp>

namespace of::object::component
{
	void TriggerCollider::initialize()
	{
		if (mColliderType == Collider::ColliderType::STATIC)
		{
			auto model = of::engine::GetModule<of::module::mesh::Loader>().requestModel(mColliderMesh,
				of::module::Settings::meshPath, true);

			auto transform = attachedOn->get<Transform>();

			mActor = of::engine::GetModule<of::module::physics::PhysicsHandler>().createActor<physx::PxRigidStatic>(
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
					auto model = of::engine::GetModule<of::module::mesh::Loader>().requestModel(mColliderMesh,
						of::module::Settings::meshPath, true);
					of::engine::GetModule<of::module::physics::PhysicsHandler>().attachTriggerShape(mActor, model, mTriggerShapeOffset, mTriggerShapeScale);
				}
				else if (mColliderShapeType == ShapeType::BOX)
				{
					of::engine::GetModule<of::module::physics::PhysicsHandler>().attachBoxTriggerShape(mActor, mTriggerShapeOffset, mTriggerShapeScale);
				}
				else
				{
					of::engine::GetModule<of::module::physics::PhysicsHandler>().attachCylinderTriggerShape(mActor, mTriggerShapeOffset, mTriggerShapeScale);
				}
			}
			else
			{
				of::engine::GetModule<of::module::logger::OneLogger>().getLogger("of::object::component::TriggerCollider").Warning("Trying to create a trigger collider with inherit, but no collider to inherit the actor from. No collider will be created!");

			}
		}
		else if (mColliderType == Collider::ColliderType::RIGID)
		{
			of::engine::GetModule<of::module::logger::OneLogger>().getLogger("of::object::component::TriggerCollider").Warning("Trying to create a trigger collider with type rigid, this is not supported for trigger colliders, use colliderType inherit instead, as that allows the trigger collider to attach it's shape to the rigid actor.");
		}
		else if (mColliderType == Collider::ColliderType::NONE)
		{
			of::engine::GetModule<of::module::logger::OneLogger>().getLogger("of::object::component::TriggerCollider").Info("mColliderType is set to NONE, no collider will be created, is this intended?");
		}
	}

	void TriggerCollider::deconstruct()
	{
		if (of::engine::GetModule<of::module::physics::PhysicsHandler>().hasShutDown() == false)
		{
			if (mColliderType == Collider::ColliderType::STATIC)
			{
				mActor->release();
			}
		}
	}
}