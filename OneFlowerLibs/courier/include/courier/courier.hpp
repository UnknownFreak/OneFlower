#pragma once

#include <module/IEngineModule.hpp>
#include <module/ModuleManager.hpp>

#include <map>

#include <courier/message.hpp>
#include <courier/scheduledMessage.hpp>
#include <courier/channel.hpp>
#include <courier/channelTopic.hpp>
#include <courier/subscriber.hpp>
#include <courier/topic.hpp>

#include <utils/common/uuid.hpp>

namespace of::courier
{
	class Courier : public of::module::interface::IEngineResource<Courier>
	{
	public:

		void post(const Topic topic, const Message& message);
		void post(const Topic topic, const size_t subscriber, const Message& message);
		void post(const Topic topic, const of::common::uuid& channel, const Message& message);
		void post(const Topic topic, const of::common::uuid& channel, const size_t subscriberId, const Message& message);

		void schedule(const Topic topic, const Message& message);
		void schedule(const Topic topic, const size_t subscriberId, const Message& message);
		void schedule(const Topic topic, const of::common::uuid& channel, const Message& message);
		void schedule(const Topic topic, const of::common::uuid& channel, const size_t subscriberId, const Message& message);

		size_t addSubscriber(const Topic topic, const Subscriber& subscriber);
		void removeSubscriber(const Topic topic, size_t subscriberId);

		void createChannel(const Topic topic);
		std::shared_ptr<ChannelTopic> getChannel(const Topic topic);

		of::module::EngineResourceType& getType() const override
		{
			return type;
		}

		Courier& operator=(const Courier) = delete;

		void scheduleRemoval(const Topic, const size_t subscriberId);
		void handleScheduledMessages();
		void handleScheduledRemovals();
	private:
		std::map<Topic, std::shared_ptr<ChannelTopic>> channels;
		std::map<Topic, std::vector<internal::ScheduledMessage>> scheduledMessages;

	};
}