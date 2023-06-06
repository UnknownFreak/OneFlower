#pragma once
#include <utils/common/uuid.hpp>

#include <unordered_map>
#include <memory>

#include <messaging/message.h>
#include <messaging/subscriber.hpp>

#include <module/logger/OneLogger.hpp>

#ifdef _WIN32
#include <ppl.h>
#define _PPL 1
#else
#include <omp.h>
#define _PPL 0
#endif

namespace of::messaging
{
	class Channel
	{
	public:

		virtual ~Channel()
		{
			if (subscribers.size() != 0)
			{
				of::engine::GetModule<of::module::logger::OneLogger>().getLogger("of::messaging::Channel").Warning("Dangling subscribers on destruction");
			}
		}
		virtual void sendMessage(std::shared_ptr<Message> message)
		{

		#if defined _PPL && _PPL == 1
			concurrency::parallel_for_each(subscribers.begin(), subscribers.end(),
				[&](auto & pair)
				{
					pair.second->sendMessage(message);
				});
		#else
			// TODO: figure out for linux build
			//#pragma omp parallel for
			for (auto it = subscribers.begin(); it != subscribers.end() ; it++)
			{
				it->second->sendMessage(message);
			}
		#endif
		}

		void sendMessage(const of::common::uuid& subscriberId, std::shared_ptr<Message> message)
		{
			if (subscribers.find(subscriberId) != subscribers.end())
			{
				subscribers[subscriberId]->sendMessage(message);
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

		of::common::uuid& getId()
		{
			return id;
		}

	protected:

		std::map<of::common::uuid, std::shared_ptr<Subscriber>> subscribers;
	private:
		of::common::uuid id;
	};

}