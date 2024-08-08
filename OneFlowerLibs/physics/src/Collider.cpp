#include <component/collider.hpp>

#include <object/GameObject.hpp>

#include <courier/courier.hpp>

#include <logger/Logger.hpp>
#include <module/resource/MeshLoader.hpp>

#pragma warning(push, 0)
#include <glm/gtc/quaternion.hpp>
#pragma warning(pop)

#include <engine/runMode.hpp>

namespace of::component
{
	void Collider::onMessage(const  of::object::messaging::Message& message)
	{
		using namespace  of::object::messaging;
		if (message.messageTopic == Topic::of(Topics::TELEPORT) && message.messageBody->bodyType == BodyType::TELEPORT)
		{
			auto ref = ((Teleport*)message.messageBody.get());
			if (ref->topic == Topic::of(Topics::TELEPORT))
			{
				if (mActor)
				{
					constexpr float dtr = glm::pi<float>() / 180.f;
					Transform* t = (Transform*)ref->transformVp;
					physx::PxTransform newPose(physx::PxVec3(t->pos.x, t->pos.y, t->pos.z));
					glm::vec3 nrot = t->rot;
					nrot.x *= dtr;
					nrot.y *= dtr;
					nrot.z *= dtr;
					glm::quat q = glm::quat(nrot);
					newPose.q = physx::PxQuat(q.x, q.y, q.z, q.w);
					mActor->setGlobalPose(newPose);
				}
			}
		}
	}

	void Collider::attached()
	{
		mColliderInfoType.objectId = attachedOn->id;
		mColliderInfoType.hitType = of::physics::PxColliderType::ObjectTrigger;
		mColliderInfoType.go = attachedOn;
		
		mTransform = attachedOn->get<Transform>();

		// TODO: think about how to do this... Static override is better for moving stuff as it does allow objects to be moved if clipping
		// however they cannot be simulated since their collider is force created as static...
		if (mColliderType == ColliderType::STATIC || of::engine::getRunMode() == of::engine::RunMode::EDITOR)
		{
			auto model = of::engine::GetModule<of::module::mesh::Loader>().requestModel(mColliderMesh,
				of::engine::path::meshes, true);
			mActor = of::physics::get().createActor<physx::PxRigidStatic>(
				mTransform->pos, model);

			
		}
		else if (mColliderType == ColliderType::RIGID)
		{
			auto model = of::engine::GetModule<of::module::mesh::Loader>().requestModel(mColliderMesh,
				of::engine::path::meshes, true);

			mActor = of::physics::get().createActor<physx::PxRigidDynamic>(
				mTransform->pos, model);
			if (subscriberId == 0)
			{
				subscriberId = of::courier::get().addSubscriber(of::courier::Topic::Update,
					of::courier::Subscriber(isAlive(), [this](const of::courier::Message& msg) {
						auto p = mActor->getGlobalPose().p;
						mTransform->pos.x = p.x;
						mTransform->pos.y = p.y;
						mTransform->pos.z = p.z;

						// todo set quat rotation;

						}));
			}
		}
		else
		{
			of::engine::GetModule<of::logger::Logger>().getLogger("of::object::component::Collider").Error(
			"Collider does not have a collider type set");
		}

		if (mActor)
		{
			mActor->userData = &mColliderInfoType;
		}
	}

	void Collider::initialize()
	{

	}

	void Collider::deconstruct()
	{
		if (subscriberId != 0)
		{
			of::courier::get().removeSubscriber(of::courier::Topic::Update, subscriberId);
			subscriberId = 0;
		}
		if (of::physics::get().hasShutDown() == false && mActor != nullptr)
		{
			mActor->release();
			mActor = nullptr;
		}
	}
}
