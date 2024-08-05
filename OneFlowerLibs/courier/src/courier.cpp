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

	void Courier::post(const Topic topic, const size_t subscriber, const Message& message)
	{
		if (channels.find(topic) != channels.end())
		{
			channels[topic]->sendMessage(subscriber, message);
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

	void Courier::schedule(const Topic topic, const size_t subscriberId, const Message& message)
	{
		scheduledMessages[topic].push_back(internal::ScheduledMessage{ false, true, of::common::uuid::nil(), subscriberId, message });
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

	size_t Courier::addSubscriber(const Topic topic, const Subscriber& subscriber)
	{
		if (channels.find(topic) == channels.end())
		{
			of::engine::GetModule<of::logger::Logger>().getLogger("of::courier::Courier").Info(
				"Trying to add a subscriber to a topic that has no registered channel.");
			of::engine::GetModule<of::logger::Logger>().getLogger("of::courier::Courier").Info(
				"Creating channel automatically.");
			createChannel(topic);
		}
		return channels[topic]->addSubscriber(subscriber);
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

	void Courier::createChannel(const Topic topic)
	{
		channels[topic] = std::make_shared<ChannelTopic>();
	}

	std::shared_ptr<ChannelTopic> Courier::getChannel(const Topic topic)
	{
		if (channels.find(topic) == channels.end())
		{
			createChannel(topic);
		}
		return channels[topic];
	}


	void Courier::scheduleRemoval(const Topic topic, const size_t subscriberId)
	{
		channels[topic]->scheduleRemoval(subscriberId);
	}

	void Courier::handleScheduledMessages()
	{
		auto scheduledMessagesCopy = scheduledMessages;
		scheduledMessages.clear();
		for (auto& [topic, messages] : scheduledMessagesCopy)
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
					if (message.sendToSubscriber)
					{
						post(topic, message.subscriber, message.message);
					}
					else
					{
						post(topic, message.message);
					}
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
