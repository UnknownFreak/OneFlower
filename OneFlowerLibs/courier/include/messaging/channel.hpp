#pragma once
#include <utils/common/uuid.hpp>

#include <unordered_map>
#include <memory>

#include <messaging/message.hpp>
#include <messaging/subscriber.hpp>

#include <module/logger/OneLogger.hpp>

#ifdef _WIN32
#include <ppl.h>
#define _PPL 1
#else
#include <omp.h>
#define _PPL 0
#endif
#include <iostream>

namespace of::messaging
{
	class Channel
	{
	public:

		Channel() : mMultithreadedEnabled(true)
		{
			subscribers.reserve(1000000);
		}

		virtual ~Channel()
		{
			if (subscribers.size() != 0)
			{
				of::engine::GetModule<of::module::logger::OneLogger>().getLogger("of::messaging::Channel").Warning("Dangling subscribers on destruction");
			}
		}
		virtual void sendMessage(const Message& message)
		{
		
		#if defined _PPL && _PPL == 1
			if (mMultithreadedEnabled)
			{

				concurrency::parallel_for((size_t)0, subscribers.size(),
					[&](size_t index)
					{
						subscribers[index].sendMessage(message);
					});
			}
			else
			{
				for (auto& s : subscribers)
				{
					s.sendMessage(message);
				}
			}
		#else
			// TODO: figure out for linux build
			//#pragma omp parallel for
			for (auto it = subscribers.begin(); it != subscribers.end() ; it++)
			{
				it->second.sendMessage(message);
			}
		#endif
		//*/
		}

		void sendMessage(const size_t& subscriberId, const Message& message)
		{
			//*
			auto it = std::lower_bound(subscribers.begin(), subscribers.end(), Subscriber(subscriberId));
			if (it != subscribers.end())
			{
				it->sendMessage(message);
			}
			else
			{
				of::engine::GetModule<of::module::logger::OneLogger>().getLogger("of::messaging::Channel").Warning(
					"Trying to send message to a subscriber that does not exist.");
			}
			//*/
		}
		void addSubscriber(const Subscriber& subscriber)
		{
			if (std::binary_search(subscribers.begin(), subscribers.end(), subscriber) == false)
			{
				subscribers.emplace_back(subscriber);
			}
		}

		void removeSubscriber(const size_t& subscriberId)
		{
			auto it = std::lower_bound(subscribers.begin(), subscribers.end(), Subscriber(subscriberId));
			if (it != subscribers.end())
			{
				subscribers.erase(it);
			}
		}

		of::common::uuid& getId()
		{
			return id;
		}

		size_t getSubscribersCount() const
		{
			return subscribers.size();
		}

		void scheduleRemoval(const size_t& subscriberId)
		{
			scheduledRemovals.push_back(subscriberId);
		}

		void handleScheduledRemovals()
		{
			for (auto removal : scheduledRemovals)
			{
				removeSubscriber(removal);
			}
			scheduledRemovals.clear();
		}

		void setMultiThreaded(const bool bEnabled)
		{
			mMultithreadedEnabled = bEnabled;
		}

	protected:

		bool mMultithreadedEnabled;
		std::vector<Subscriber> subscribers;
		std::vector<size_t> scheduledRemovals;
	private:
		of::common::uuid id;
	};

}