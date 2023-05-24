#pragma once
#include <utils/common/uuid.hpp>

#include <unordered_map>
#include <memory>

#include <messaging/message.h>
#include <messaging/subscriber.hpp>

namespace of::messaging
{
	class Channel
	{
	public:

		virtual ~Channel() = default;
		virtual void sendMessage(std::shared_ptr<Message> message);

		void addSubscriber(Subscriber s);

	protected:

		std::unordered_map<of::common::uuid, Subscriber> subscribers;

	};

}