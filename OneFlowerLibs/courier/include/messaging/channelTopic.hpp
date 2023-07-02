#pragma once

#include "channel.hpp"
#include "messageValidator.hpp"

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
			if (validate(message) == false)
			{
				return;
			}
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
			if (validate(message) == false)
			{
				return;
			}
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

		void sendMessage(const of::common::uuid& channelId, const size_t& subscriberId, const Message& message)
		{
			if (validate(message) == false)
			{
				return;
			}
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

		void setMessageValidator(std::shared_ptr<MessageValidator> messageValidator)
		{
			validator = messageValidator;
		}

		inline bool validate(const Message& message) const
		{
			if (validator)
			{
				return validator->validate(message);
			}
			return true;
		}

	private:
		std::map<of::common::uuid, std::shared_ptr<Channel>> channels;
		std::shared_ptr<MessageValidator> validator;
	};
}