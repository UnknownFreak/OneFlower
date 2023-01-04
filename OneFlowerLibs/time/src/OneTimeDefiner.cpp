#include <module/OneTime.hpp>


of::module::EngineResourceType of::module::interface::IEngineResource<of::module::Time>::type = of::module::EngineResourceType::Time;

namespace of::module
{
	Time::Time() : timer(), clock(), elapsed(), physicsElapsed()
	{
		timer.reset();
		clock.reset();
	}

	float Time::deltaTime() const
	{
		return update_ms;
	}

	::utils::HighResolutionClock& Time::getTimer(const of::common::String& name)
	{
		std::unordered_map<of::common::String, ::utils::HighResolutionClock>::iterator it = timers.find(name);
		if (it == timers.end())
		{
			timers.insert(std::make_pair(name, ::utils::HighResolutionClock()));
		}
		return timers[name];
	}

	bool Time::time(const of::common::String& name, const double& msec)

	{
		std::unordered_map<of::common::String, ::utils::HighResolutionClock>::iterator it = timers.find(name);
		if (it == timers.end())
		{
			it = timers.insert(std::make_pair(name, ::utils::HighResolutionClock())).first;
			return 0;
		}
		else
		{
			//LOW: Research if needed
			//Make it modulus instead, Also make a custom Holder so that we can have diffrent start timer if needed

			if (it->second.secondsAsFloat() > msec)
			{
				//Make it so that it doesnt restart
				it->second.reset();
				return 1;
			}
		}
		return 0;
	}
	void Time::remove(const of::common::String& name)
	{
		timers.erase(name);
	}
	void Time::addTicKTimer(const of::file::FileId& timerId, const resource::TickTimer& tickTimer)
	{
		mtx.lock();
		tickTimers[timerId] = tickTimer;
		mtx.unlock();
	}
	bool Time::exists(const of::file::FileId& timerId) const
	{
		return tickTimers.find(timerId) != tickTimers.end();
	}
	resource::TickTimer& Time::getTickTimer(const of::file::FileId& timerId)
	{
		return tickTimers.at(timerId);
	}
	void Time::removeTimer(const of::file::FileId& timerId)
	{
		mtx.lock();
		tickTimers.erase(timerId);
		mtx.unlock();
	}
	void Time::Simulate(const float& fElapsedTime)
	{
		mtx.lock();
		for (auto& tickTimer : tickTimers)
		{
			tickTimer.second.tick(fElapsedTime);
		}
		mtx.unlock();
	}
}