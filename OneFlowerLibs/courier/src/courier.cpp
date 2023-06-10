#include <messaging/courier.hpp>
#include <module/logger/OneLogger.hpp>

#include <iostream>

of::module::EngineResourceType of::module::interface::IEngineResource<of::messaging::Courier>::type = of::module::EngineResourceType::Courier;

namespace of::messaging
{

	void Courier::post(const Topic& topic, const Message& message)
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

	void Courier::post(const Topic& topic, const of::common::uuid& channel, const Message& message)
	{
		if (channels.find(topic) != channels.end())
		{
			channels[topic]->sendMessage(channel, message);
		}
		else
		{
			of::engine::GetModule<of::module::logger::OneLogger>().getLogger("of::messaging::courier").Warning(
				"Trying to post a message to a topic that has no registererd channel.");
		}
	}

	void Courier::post(const Topic& topic, const of::common::uuid& channel, const of::common::uuid& subscriber, const Message& message)
	{
		if (channels.find(topic) != channels.end())
		{
			channels[topic]->sendMessage(channel, subscriber, message);
		}
		else
		{
			of::engine::GetModule<of::module::logger::OneLogger>().getLogger("of::messaging::courier").Warning(
				"Trying to post a message to a topic that has no registererd channel.");
		}
	}

	void Courier::addSubscriber(const Topic& topic, const of::common::uuid& id, Subscriber& subscriber)
	{
		if (channels.find(topic) == channels.end())
		{
			of::engine::GetModule<of::module::logger::OneLogger>().getLogger("of::messaging::courier").Info(
				"Trying to add a subscriber to a topic that has no registered channel.");
			of::engine::GetModule<of::module::logger::OneLogger>().getLogger("of::messaging::courier").Info(
				"Creating channel automatically.");
			createChannel(topic);
		}
		channels[topic]->addSubscriber(id, subscriber);
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
