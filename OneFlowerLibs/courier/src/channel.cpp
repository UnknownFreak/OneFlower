#include <courier/channel.hpp>

#include <memory>

#include <logger/Logger.hpp>

#ifdef _WIN32
#include <ppl.h>
#define _PPL 1
#else
#include <omp.h>
#define _PPL 0
#endif
#include <iostream>


namespace of::courier
{

	Channel::Channel() : mMultithreadedEnabled(true)
	{
		subscribers.reserve(1000000);
	}

	Channel::~Channel()
	{
		if (subscribers.size() != 0)
		{
			of::engine::GetModule<of::logger::Logger>().getLogger("of::courier::Channel").Warning("Dangling subscribers on destruction");
			for (auto& sub : subscribers)
			{
				of::engine::GetModule<of::logger::Logger>().getLogger("of::courier::Channel").Warning(std::to_string(sub.id));
			}
		}
	}
	size_t Channel::sendMessage(const Message& message)
	{
		if (mMultithreadedEnabled)
		{
		#if defined _PPL && _PPL == 1
			concurrency::parallel_for((size_t)0, subscribers.size(),
				[&](size_t index)
				{
					subscribers[index].sendMessage(message);
				});
		
		#else
			// TODO: figure out for linux build
			//#pragma omp parallel for
			for (auto it = subscribers.begin(); it != subscribers.end(); it++)
			{
				it->second.sendMessage(message);
			}
		#endif
		}
		else
		{
			for (auto& s : subscribers)
			{
				s.sendMessage(message);
			}
		}
		return subscribers.size();
		//*/
	}

	size_t Channel::sendMessage(const size_t subscriberId, const Message& message)
	{
		//*
		Subscriber tmp;
		tmp.id = subscriberId;
		auto it = std::lower_bound(subscribers.begin(), subscribers.end(), tmp);
		if (it != subscribers.end())
		{
			it->sendMessage(message);
			return 1;
		}
		else
		{
			of::engine::GetModule<of::logger::Logger>().getLogger("of::messaging::Channel").Warning(
				"Trying to send message to a subscriber that does not exist.");
		}
		return 0;
		//*/
	}

	size_t Channel::addSubscriber(const Subscriber& subscriber)
	{
		if (std::binary_search(subscribers.begin(), subscribers.end(), subscriber) == false)
		{
			subscribers.emplace_back(subscriber);
		}
		return subscriber.id;
	}

	void Channel::removeSubscriber(const size_t subscriberId)
	{
		Subscriber tmp;
		tmp.id = subscriberId;
		auto it = std::lower_bound(subscribers.begin(), subscribers.end(), tmp);
		if (it != subscribers.end())
		{
			subscribers.erase(it);
		}
	}

	of::common::uuid& Channel::getId()
	{
		return id;
	}

	size_t Channel::getSubscribersCount() const
	{
		return subscribers.size();
	}

	void Channel::scheduleRemoval(const size_t subscriberId)
	{
		scheduledRemovals.push_back(subscriberId);
	}

	void Channel::handleScheduledRemovals()
	{
		for (auto removal : scheduledRemovals)
		{
			removeSubscriber(removal);
		}
		scheduledRemovals.clear();
	}

	void Channel::setMultiThreaded(const bool bEnabled)
	{
		mMultithreadedEnabled = bEnabled;
	}
}