#include <object/component/Collider.hpp>

#include <object/GameObject.hpp>

#include <messaging/courier.hpp>

#include <module/logger/OneLogger.hpp>
#include <module/resource/MeshLoader.hpp>

namespace of::object::component
{
	void Collider::initialize()
	{
		mColliderInfoType.objectId = attachedOn->id;
		mColliderInfoType.hitType = of::module::physics::ColliderType::ObjectTrigger;
		
		mTransform = attachedOn->get<Transform>();

		if (mColliderType == ColliderType::STATIC)
		{
			auto model = of::engine::GetModule<of::module::mesh::Loader>().requestModel(mColliderMesh,
				of::module::Settings::meshPath, true);
			mActor = of::engine::GetModule<of::module::physics::PhysicsHandler>().createActor<physx::PxRigidStatic>(
				mTransform->pos, model);
		}
		else if (mColliderType == ColliderType::RIGID)
		{
			auto model = of::engine::GetModule<of::module::mesh::Loader>().requestModel(mColliderMesh,
				of::module::Settings::meshPath, true);

			mActor = of::engine::GetModule<of::module::physics::PhysicsHandler>().createActor<physx::PxRigidDynamic>(
				mTransform->pos, model);
			of::engine::GetModule<of::messaging::Courier>().addSubscriber(of::messaging::Topic::Update,
				of::messaging::Subscriber(instanceId, warrantyFromThis(), [this](const of::messaging::Message& msg) {
					auto p = mActor->getGlobalPose().p;
					mTransform->pos.x = p.x;
					mTransform->pos.y = p.y;
					mTransform->pos.z = p.z;

					// todo set quat rotation;

					}));
		}
		else
		{
			of::engine::GetModule<of::module::logger::OneLogger>().getLogger("of::object::component::Collider").Error(
			"Collider does not have a collider type set");
		}

		if (mActor)
		{
			mActor->userData = &mColliderInfoType;
		}
	}

	void Collider::deconstruct()
	{
		of::engine::GetModule<of::messaging::Courier>().removeSubscriber(of::messaging::Topic::Update, instanceId);
		if (of::engine::GetModule<of::module::physics::PhysicsHandler>().hasShutDown() == false)
		{
			mActor->release();
		}
	}
}
