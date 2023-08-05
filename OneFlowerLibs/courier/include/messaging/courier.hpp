#pragma once

#include <module/IEngineModule.hpp>
#include <module/ModuleManager.hpp>

#include <map>

#include <messaging/message.hpp>
#include <messaging/basicMessage.hpp>
#include <messaging/channel.hpp>
#include <messaging/channelTopic.hpp>
#include <messaging/subscriber.hpp>
#include <messaging/topic/topic.hpp>

#include <utils/common/uuid.hpp>

namespace of::messaging
{
	class Courier : public of::module::interface::IEngineResource<Courier>
	{
	public:

		void post(const Topic& topic, const Message& message);
		void post(const Topic& topic, const of::common::uuid& channel, const Message& message);
		void post(const Topic& topic, const of::common::uuid& channel, const size_t& subscriberId, const Message& message);

		void addSubscriber(const Topic& topic, const Subscriber& subscriber);
		void removeSubscriber(const Topic& topic, size_t& subscriberId);

		void createChannel(const Topic& topic)
		{
			channels[topic] = std::make_shared<ChannelTopic>();
		}

		std::shared_ptr<ChannelTopic> getChannel(const Topic& topic)
		{
			if (channels.find(topic) == channels.end())
			{
				createChannel(topic);
			}
			return channels[topic];
		}

		of::module::EngineResourceType& getType() const override
		{
			return type;
		}

		void scheduleRemoval(const Topic&, const size_t& subscriberId);
		void handleScheduledRemovals();
	private:
		std::map<Topic, std::shared_ptr<ChannelTopic>> channels;

	};
}