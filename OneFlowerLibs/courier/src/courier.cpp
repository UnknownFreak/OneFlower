#include <messaging/courier.hpp>
#include <module/logger/OneLogger.hpp>

of::module::EngineResourceType of::module::interface::IEngineResource<of::messaging::Courier>::type = of::module::EngineResourceType::Courier;

namespace of::messaging
{


	void Courier::post(const Topic& topic, std::shared_ptr<Message> message)
	{
		if (channels.find(topic) != channels.end())
		{
			channels[topic]->sendMessage(message);
		}
		else
		{
			of::engine::GetModule<of::module::logger::OneLogger>().getLogger("of::messaging::courier").Warning(
			"Trying to post a message to a topic that has no registererd channel.");
		}
	}


	void Courier::addSubscriber(const Topic& topic, std::shared_ptr<Subscriber> subscriber)
	{
		if (channels.find(topic) != channels.end())
		{
			channels[topic]->addSubscriber(subscriber);
		}
		else
		{
			of::engine::GetModule<of::module::logger::OneLogger>().getLogger("of::messaging::courier").Warning(
				"Trying to add a subscriber to a topic that has no registered channel.");
		}
	}
	void Courier::removeSubscriber(const Topic& topic, of::common::uuid& subscriberId)
	{
		if (channels.find(topic) != channels.end())
		{
			channels[topic]->removeSubscriber(subscriberId);
		}
		else
		{
			of::engine::GetModule<of::module::logger::OneLogger>().getLogger("of::messaging::courier").Warning(
				"Trying to remove a subscriber from a topic that has no registererd channel.");
		}
	}
}
