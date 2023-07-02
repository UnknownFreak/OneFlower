#include <object/component/AttachToParent.hpp>
#include <utils/common/uuid.hpp>

#include <object/GameObject.hpp>
#include <object/component/Transform.hpp>

#include <messaging/courier.hpp>

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
		auto courier = of::engine::GetModule<of::messaging::Courier>();
		// todo create channel and push skills into the channel once executed & remove them automatically via it's instance id when the skill is done updating
		courier.addSubscriber(of::messaging::Topic::Update, of::messaging::Subscriber(instanceId, warrantyFromThis(), [this](const of::messaging::Message& msg) {update(msg.as<of::messaging::BasicMessage<float>>().value); }));
	}

	void AttachToParent::deconstruct()
	{
		auto courier = of::engine::GetModule<of::messaging::Courier>();
		courier.removeSubscriber(of::messaging::Topic::Update, instanceId);
	}
};
