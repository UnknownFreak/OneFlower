#include <courier/courier.hpp>
#include <logger/Logger.hpp>

#include <iostream>

of::module::EngineResourceType of::module::interface::IEngineResource<of::courier::Courier>::type = of::module::EngineResourceType::Courier;

namespace of::courier
{
	void Courier::post(const Topic topic, const Message& message)
	{

		if (channels.find(topic) != channels.end())
		{
			channels[topic]->sendMessage(message);
		}
		else
		{
			of::engine::GetModule<of::logger::Logger>().getLogger("of::courier::Courier").Warning(
				"Trying to post a message to a topic that has no registererd channel.");
		}
	}

	void Courier::post(const Topic topic, const of::common::uuid& channel, const Message& message)
	{
		if (channels.find(topic) != channels.end())
		{
			channels[topic]->sendMessage(channel, message);
		}
		else
		{
			of::engine::GetModule<of::logger::Logger>().getLogger("of::courier::Courier").Warning(
				"Trying to post a message to a topic that has no registererd channel.");
		}
	}

	void Courier::post(const Topic topic, const of::common::uuid& channel, const size_t subscriber, const Message& message)
	{
		if (channels.find(topic) != channels.end())
		{
			channels[topic]->sendMessage(channel, subscriber, message);
		}
		else
		{
			of::engine::GetModule<of::logger::Logger>().getLogger("of::courier::Courier").Warning(
				"Trying to post a message to a topic that has no registererd channel.");
		}
	}
	void Courier::schedule(const Topic topic, const Message& message)
	{
		scheduledMessages[topic].push_back(internal::ScheduledMessage{
			false, false, of::common::uuid::nil(), 0, message
		});
	}
	void Courier::schedule(const Topic topic, const of::common::uuid& channel, const Message& message)
	{
		scheduledMessages[topic].push_back(internal::ScheduledMessage{
			true, false, channel, 0, message
		});
	}
	void Courier::schedule(const Topic topic, const of::common::uuid& channel, const size_t subscriber, const Message& message)
	{
		scheduledMessages[topic].push_back(internal::ScheduledMessage{
			true, true, channel, subscriber, message
		});
	}

	void Courier::addSubscriber(const Topic topic, const Subscriber& subscriber)
	{
		if (channels.find(topic) == channels.end())
		{
			of::engine::GetModule<of::logger::Logger>().getLogger("of::courier::Courier").Info(
				"Trying to add a subscriber to a topic that has no registered channel.");
			of::engine::GetModule<of::logger::Logger>().getLogger("of::courier::Courier").Info(
				"Creating channel automatically.");
			createChannel(topic);
		}
		channels[topic]->addSubscriber(subscriber);
	}

	void Courier::removeSubscriber(const Topic topic, size_t subscriberId)
	{
		if (channels.find(topic) != channels.end())
		{
			channels[topic]->removeSubscriber(subscriberId);
		}
		else
		{
			of::engine::GetModule<of::logger::Logger>().getLogger("of::courier::Courier").Warning(
				"Trying to remove a subscriber from a topic that has no registererd channel.");
			of::engine::GetModule<of::logger::Logger>().getLogger("of::courier::Courier").Warning(
				"Topic = ", (unsigned int)topic, ", subscriberId = ", subscriberId);
		}
	}

	void Courier::scheduleRemoval(const Topic topic, const size_t subscriberId)
	{
		channels[topic]->scheduleRemoval(subscriberId);
	}

	void Courier::handleScheduledMessages()
	{
		for (auto [topic, messages] : scheduledMessages)
		{
			for (auto& message : messages)
			{
				if (message.sendToChannel == true)
				{
					if (message.sendToSubscriber)
					{
						post(topic, message.channel, message.subscriber, message.message);
					}
					else
					{
						post(topic, message.channel, message.message);
					}
				}
				else
				{
					post(topic, message.message);
				}
			}
		}
	}

	void Courier::handleScheduledRemovals()
	{
		for (auto& channel : channels)
		{
			channel.second->handleScheduledRemovals();
		}
	}
}
