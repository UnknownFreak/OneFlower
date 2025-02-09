#include <component/attachToParent.hpp>
#include <utils/common/uuid.hpp>

#include <object/GameObject.hpp>
#include <component/transform.hpp>

#include <courier/courier.hpp>
#include <engine/courier/topic.hpp>

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
		if (subscriberId == courier::SubscriberId::NOT_SET)
		{
			using Topic = of::engine::courier::Topic;
			constexpr auto to = of::Topic::convert;

			subscriberId = courier::get().addSubscriber(to(Topic::Update), courier::Subscriber(isAlive(),
				[this](const courier::Message& msg) {update(msg.get<float>()); }));
		}
	}

	void AttachToParent::initialize()
	{

	}

	void AttachToParent::deconstruct()
	{
		if (subscriberId != courier::SubscriberId::NOT_SET)
		{
			using Topic = of::engine::courier::Topic;
			constexpr auto from = of::Topic::convert;

			courier::get().removeSubscriber(from(Topic::Update), subscriberId);
			subscriberId = courier::SubscriberId::NOT_SET;
		}
	}
};
