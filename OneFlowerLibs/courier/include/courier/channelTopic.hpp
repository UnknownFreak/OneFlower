#pragma once

#include <map>

#include <utils/common/uuid.hpp>

#include <courier/channel.hpp>
#include <courier/messageValidator.hpp>


namespace of::courier
{
	class ChannelTopic : public Channel
	{
	public:

		void addChannel(std::shared_ptr<Channel> channel);


		size_t sendMessage(const Message& message) override;

		size_t sendMessage(const size_t, const Message& message) override;

		size_t sendMessage(const of::common::uuid& channelId, const Message& message);

		size_t sendMessage(const of::common::uuid& channelId, const size_t subscriberId, const Message& message);

		void setMessageValidator(std::shared_ptr<MessageValidator> messageValidator);
		std::shared_ptr<MessageValidator> getValidator() const;

		bool validate(const Message& message) const;

	private:
		std::map<of::common::uuid, std::shared_ptr<Channel>> channels;
		std::shared_ptr<MessageValidator> validator;
	};
}