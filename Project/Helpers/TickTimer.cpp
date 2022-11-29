#include "TickTimer.hpp"

bool Core::TickTimer::tick(const float& dt)
{
	currentTime += dt;
	return ready();
}

bool Core::TickTimer::ready() const
{
	return currentTime > maxTime;
}

of::common::String Core::TickTimer::remainingTime() const
{
	return std::to_string(maxTime - currentTime);
}

void Core::TickTimer::reset(const bool& hard)
{
	if (hard)
		currentTime = 0;
	else
		currentTime -= maxTime;
}

float Core::TickTimer::getFraction() const
{
	return currentTime / maxTime;
}

Core::TickTimer Core::TickTimer::from(const TickTimerInfo& info)
{
	return TickTimer{info.maxTime, info.currentTime};
}

Core::TickTimerInfo Core::TickTimer::getInfo() const
{
	return TickTimerInfo{ currentTime > 0.f, getFraction() >= 1.f, maxTime, currentTime };
}
