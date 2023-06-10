#pragma once

#include "channel.hpp"

#ifdef _WIN32
#include <ppl.h>
#define _PPL 1
#else
#include <omp.h>
#define _PPL 0
#endif

namespace of::messaging
{
	class ChannelTopic : public Channel
	{
	public:

		void addChannel(std::shared_ptr<Channel> channel)
		{
			channels.insert({channel->getId(), channel});
		}

		void sendMessage(const Message& message) override
		{
			Channel::sendMessage(message);
		#if defined _PPL && _PPL == 1
			concurrency::parallel_for_each(channels.begin(), channels.end(),
				[&](auto& pair)
				{
					pair.second->sendMessage(message);
				});
		#else
			//#pragma omp parallel for
			for (auto& channel : channels)
			{
				channel.second->sendMessage(message);
			}
		#endif
		}

		void sendMessage(const of::common::uuid& channelId, const Message& message)
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

		void sendMessage(const of::common::uuid& channelId, const of::common::uuid& subscriberId, const Message& message)
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
		std::map<of::common::uuid, std::shared_ptr<Channel>> channels;
	};
}