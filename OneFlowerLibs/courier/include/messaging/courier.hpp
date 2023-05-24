#pragma once

#include <module/IEngineModule.hpp>

#include <map>

#include <messaging/message.h>
#include <messaging/channel.hpp>
#include <messaging/channelTopic.hpp>
#include <messaging/topic/topic.hpp>

#include <utils/common/uuid.hpp>

namespace of::messaging
{
	class Courier : public of::module::interface::IEngineResource<Courier>
	{
	public:

		void post(const Topic& topic, std::shared_ptr<Message> message);
		void post(const Topic& topic, const of::common::uuid& channel, std::shared_ptr<Message> message);

		void addSubscriber(const Topic& topic, std::shared_ptr<Subscriber> subscriber);
		void removeSubscriber(const Topic& topic, of::common::uuid& subscriberId);

		std::shared_ptr<ChannelTopic> getChannel(const Topic& topic);

		of::module::EngineResourceType& getType() const override
		{
			return type;
		}

	private:
		std::map<Topic, std::shared_ptr<ChannelTopic>> channels;

	};
}