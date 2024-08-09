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
			of::logger::get().getLogger("of::courier::Channel").Warning("Dangling subscribers on destruction");
			for (auto& sub : subscribers)
			{
				of::logger::get().getLogger("of::courier::Channel").Warning(std::to_string(sub.id));
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
			of::logger::get().getLogger("of::messaging::Channel").Warning(
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
		if (scheduledRemovals.size() > 0)
		{
			if (scheduledRemovals.size() < 10)
			{
				for (auto i : scheduledRemovals)
				{
					removeSubscriber(i);
				}
				scheduledRemovals.clear();
			}
			else
			{
				std::sort(scheduledRemovals.begin(), scheduledRemovals.end(), std::greater<size_t>());
				auto it = subscribers.rbegin();
				auto eit = subscribers.rbegin();
				for (auto i : scheduledRemovals)
				{
					while (it != subscribers.rend())
					{
						if (it->id == i)
						{
							if (it == eit)
							{
								//its already at last place
								eit++;
								break;
							}
							std::iter_swap(it, eit);
							eit++;
							break;
						}
						else
						{
							it++;
						}
					}
				}
				if (scheduledRemovals.size() > 0)
				{
					size_t _id = eit->id;
					while (subscribers.back().id != _id)
					{
						subscribers.pop_back();
					}
					std::sort(subscribers.begin(), subscribers.end());
				}
				scheduledRemovals.clear();
			}
		}
	}

	void Channel::setMultiThreaded(const bool bEnabled)
	{
		mMultithreadedEnabled = bEnabled;
	}
}