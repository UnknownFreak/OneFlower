#include <object/component/AttachToParent.hpp>
#include <utils/common/uuid.hpp>

#include <object/GameObject.hpp>
#include <object/component/Transform.hpp>

#include <courier/courier.hpp>

namespace of::object::component
{

	AttachToParent::AttachToParent(GameObject* objectToFollow) : objectToFollow(objectToFollow)
	{
	}

	void AttachToParent::update(const float&)
	{
		attachedOn->get<Transform>()->pos = objectToFollow->get<Transform>()->buffered;
	}

	void AttachToParent::onMessage(const messaging::Message&)
	{
	}

	void AttachToParent::initialize()
	{
		auto& courier = of::engine::GetModule<of::courier::Courier>();
		// todo create channel and push skills into the channel once executed & remove them automatically via it's instance id when the skill is done updating
		courier.addSubscriber(of::courier::Topic::Update, of::courier::Subscriber(instanceId, isAlive(), [this](const of::courier::Message& msg) {update(msg.get<float>()); }));
	}

	void AttachToParent::deconstruct()
	{
		auto& courier = of::engine::GetModule<of::courier::Courier>();
		courier.removeSubscriber(of::courier::Topic::Update, instanceId);
	}
};
