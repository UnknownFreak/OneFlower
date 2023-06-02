#pragma once

#include "channel.hpp"

namespace of::messaging
{
	class ChannelTopic : public Channel
	{
	public:

		void addChannel(std::shared_ptr<Channel> channel)
		{
			channels.insert({channel->getId(), channel});
		}

		void addSubscriber(std::shared_ptr<Subscriber>& subscriber)
		{
			subscribers[subscriber->getId()] = subscriber;
		}

		void sendMessage(std::shared_ptr<Message> message) override
		{
			Channel::sendMessage(message);
			// parallel for loop, find the include file...
			for (auto& channel : channels)
			{
				channel.second->sendMessage(message);
			}
		}

		void sendMessage(const of::common::uuid& channelId, std::shared_ptr<Message> message)
		{
			if (channels.find(channelId) != channels.end())
			{
				channels[channelId]->sendMessage(message);
			}
			else
			{
				of::engine::GetModule<of::module::logger::OneLogger>().getLogger("of::messaging::courier").Warning(
					"Trying to post a message to a channel that does not exist");
			}
		}

		void sendMessage(const of::common::uuid& channelId, const of::common::uuid& subscriberId, std::shared_ptr<Message> message)
		{
			if (channels.find(channelId) != channels.end())
			{
				channels[channelId]->sendMessage(subscriberId, message);
			}
			else
			{
				of::engine::GetModule<of::module::logger::OneLogger>().getLogger("of::messaging::courier").Warning(
					"Trying to post a message to a channel that does not exist");
			}
		}

	private:
		std::unordered_map<of::common::uuid, std::shared_ptr<Channel>> channels;
	};
}