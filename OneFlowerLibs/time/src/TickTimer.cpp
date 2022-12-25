#include <resource/TickTimer.hpp>


namespace of::resource
{
	bool TickTimer::tick(const float& dt)
	{
		currentTime += dt;
		return ready();
	}

	bool TickTimer::ready() const
	{
		return currentTime > maxTime;
	}

	of::common::String TickTimer::remainingTime() const
	{
		return std::to_string(maxTime - currentTime);
	}

	void TickTimer::reset(const bool& hard)
	{
		if (hard)
			currentTime = 0;
		else
			currentTime -= maxTime;
	}

	float TickTimer::getFraction() const
	{
		return currentTime / maxTime;
	}

	TickTimer TickTimer::from(const TickTimerInfo& info)
	{
		return TickTimer{info.maxTime, info.currentTime};
	}

	TickTimerInfo TickTimer::getInfo() const
	{
		return TickTimerInfo{ currentTime > 0.f, getFraction() >= 1.f, maxTime, currentTime };
	}
}
