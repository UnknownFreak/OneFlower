#include "OneTime.hpp"
#include <Module\EngineModuleManager.hpp>

Enums::EngineResourceType Interfaces::IEngineResource<EngineModule::Time>::type = Enums::EngineResourceType::Time;
namespace EngineModule
{
	Time::Time() : timer(), clock(), elapsed()
	{
		timer.restart();
		clock.restart();
	}

	double Time::deltaTime()
	{
		return update_ms.asSeconds();
	}

	sf::Clock& Time::getTimer(const Core::String& name)
	{
		std::unordered_map<Core::String, sf::Clock>::iterator it = timers.find(name);
		if (it == timers.end())
		{
			timers.insert(std::make_pair(name, sf::Clock()));
		}
		return timers[name];
	}

	bool Time::time(const Core::String& name, const double& msec)

	{
		std::unordered_map<Core::String, sf::Clock>::iterator it = timers.find(name);
		if (it == timers.end())
		{
			it = timers.insert(std::make_pair(name, sf::Clock())).first;
			return 0;
		}
		else
		{
			//LOW: Research if needed
			//Make it modulus instead, Also make a custom Holder so that we can have diffrent start timer if needed

			if (it->second.getElapsedTime().asMilliseconds() > msec)
			{
				//Make it so that it doesnt restart
				it->second.restart();
				return 1;
			}
		}
		return 0;
	}
	void Time::remove(const Core::String& name)
	{
		timers.erase(name);
	}
	void Time::addTicKTimer(const ModFileUUIDHelper& timerId, const Core::TickTimer& tickTimer)
	{
		mtx.lock();
		tickTimers[timerId] = tickTimer;
		mtx.unlock();
	}
	bool Time::exists(const ModFileUUIDHelper& timerId) const
	{
		return tickTimers.find(timerId) != tickTimers.end();
	}
	Core::TickTimer& Time::getTickTimer(const ModFileUUIDHelper& timerId)
	{
		return tickTimers.at(timerId);
	}
	void Time::removeTimer(const ModFileUUIDHelper& timerId)
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