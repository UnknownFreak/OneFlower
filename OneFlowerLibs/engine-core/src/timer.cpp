#include <timer/timer.hpp>
#include <unordered_map>

#include <logger/Logger.hpp>

std::unordered_map<of::common::String, utils::HighResolutionClock>* g_timers = nullptr;

namespace of::timer
{
	void init()
	{
		if (g_timers == nullptr)
		{
			engine::GetModule<of::logger::Logger>().Info("Initializing module: Timer");
			g_timers = new std::unordered_map<of::common::String, utils::HighResolutionClock>();
		}
	}

	void shutdown()
	{
		delete g_timers;
		g_timers = nullptr;
	}

	::utils::HighResolutionClock& get(const of::common::String& name)
	{
		auto it = g_timers->find(name);
		if (it == g_timers->end())
		{
			g_timers->insert(std::make_pair(name, ::utils::HighResolutionClock()));
		}
		return (*g_timers)[name];
	}

	float elapsedTime(const of::common::String& timer, const bool reset)
	{
		return get(timer).secondsAsFloat(reset);
	}

	void reset(const of::common::String& timer)
	{
		get(timer).reset();
	}

	bool passed(const of::common::String& timer, const float time)
	{
		auto myTimer = get(timer);
		bool passed = myTimer.secondsAsFloat() > time;
		if (passed)
		{
			myTimer.reset();
		}
		return passed;
	}

	void remove(const of::common::String& timer)
	{
		g_timers->erase(timer);
	}

}