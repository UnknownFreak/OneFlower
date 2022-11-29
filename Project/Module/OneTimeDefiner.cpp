#include "OneTime.hpp"
#include <Module\EngineModuleManager.hpp>

Enums::EngineResourceType Interfaces::IEngineResource<EngineModule::Time>::type = Enums::EngineResourceType::Time;
namespace EngineModule
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

	utils::HighResolutionClock& Time::getTimer(const of::common::String& name)
	{
		std::unordered_map<of::common::String, utils::HighResolutionClock>::iterator it = timers.find(name);
		if (it == timers.end())
		{
			timers.insert(std::make_pair(name, utils::HighResolutionClock()));
		}
		return timers[name];
	}

	bool Time::time(const of::common::String& name, const double& msec)

	{
		std::unordered_map<of::common::String, utils::HighResolutionClock>::iterator it = timers.find(name);
		if (it == timers.end())
		{
			it = timers.insert(std::make_pair(name, utils::HighResolutionClock())).first;
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
	void Time::addTicKTimer(const File::Mod::ModFileUUIDHelper& timerId, const Core::TickTimer& tickTimer)
	{
		mtx.lock();
		tickTimers[timerId] = tickTimer;
		mtx.unlock();
	}
	bool Time::exists(const File::Mod::ModFileUUIDHelper& timerId) const
	{
		return tickTimers.find(timerId) != tickTimers.end();
	}
	Core::TickTimer& Time::getTickTimer(const File::Mod::ModFileUUIDHelper& timerId)
	{
		return tickTimers.at(timerId);
	}
	void Time::removeTimer(const File::Mod::ModFileUUIDHelper& timerId)
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