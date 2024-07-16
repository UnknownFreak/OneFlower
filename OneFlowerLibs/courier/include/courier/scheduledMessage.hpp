#include <courier/message.hpp>

#include <utils/common/uuid.hpp>

namespace of::courier::internal
{
	struct ScheduledMessage
	{
		bool sendToChannel;
		bool sendToSubscriber;
		const common::uuid channel;
		const size_t subscriber;
		const Message message;
	};
}