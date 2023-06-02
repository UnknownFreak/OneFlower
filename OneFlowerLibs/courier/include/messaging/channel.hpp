#pragma once
#include <utils/common/uuid.hpp>

#include <unordered_map>
#include <memory>

#include <messaging/message.h>
#include <messaging/subscriber.hpp>

#include <module/logger/OneLogger.hpp>

namespace of::messaging
{
	class Channel
	{
	public:

		virtual ~Channel() = default;
		virtual void sendMessage(std::shared_ptr<Message> message)
		{
			message;
			for (auto& subscriber : subscribers)
			{
				subscriber;
				//subscriber.second->sendMessage(message);
			}
		}

		void sendMessage(const of::common::uuid& subscriberId, std::shared_ptr<Message> message)
		{
			message;
			if (subscribers.find(subscriberId) != subscribers.end())
			{
				// TODO: see above
			}
			else
			{
				of::engine::GetModule<of::module::logger::OneLogger>().getLogger("of::messaging::Channel").Warning(
					"Trying to send message to a subscriber that does not exist.");
			}
		}

		void addSubscriber(std::shared_ptr<Subscriber> s)
		{
			subscribers[s->getId()] = s;
		}

		void removeSubscriber(const of::common::uuid& subscriberId)
		{
			subscribers.erase(subscriberId);
		}

		of::common::uuid& getId();

	protected:

		std::unordered_map<of::common::uuid, std::shared_ptr<Subscriber>> subscribers;
	private:
		of::common::uuid id;
	};

}