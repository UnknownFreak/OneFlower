#pragma once

#include "channel.hpp"

namespace of::messaging
{
	class ChannelTopic : public Channel
	{
	public:

		void sendMessage(std::shared_ptr<Message> message) override
		{
			Channel::sendMessage(message);
			for (auto& channel : channels)
			{
				channel.second->sendMessage(message);
			}
		}

	private:
		std::unordered_map<of::common::uuid, std::shared_ptr<Channel>> channels;
	};
}