#include <component/attachToParent.hpp>
#include <utils/common/uuid.hpp>

#include <object/GameObject.hpp>
#include <component/transform.hpp>

#include <courier/courier.hpp>

namespace of::component
{

	AttachToParent::AttachToParent(object::GameObject* objectToFollow) : objectToFollow(objectToFollow)
	{
	}

	void AttachToParent::update(const float)
	{
		attachedOn->get<Transform>()->pos = objectToFollow->get<Transform>()->buffered;
	}

	void AttachToParent::onMessage(const object::messaging::Message&)
	{
	}

	void AttachToParent::attached()
	{
		if (subscriberId == 0)
		{
			auto& courier = of::engine::GetModule<of::courier::Courier>();
			subscriberId = courier.addSubscriber(of::courier::Topic::Update, of::courier::Subscriber(isAlive(), [this](const of::courier::Message& msg) {update(msg.get<float>()); }));
		}
	}

	void AttachToParent::initialize()
	{

	}

	void AttachToParent::deconstruct()
	{
		if (subscriberId != 0)
		{
			auto& courier = of::engine::GetModule<of::courier::Courier>();
			courier.removeSubscriber(of::courier::Topic::Update, subscriberId);
			subscriberId = 0;
		}
	}
};
