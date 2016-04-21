#include "TimerComponent.hpp"
#include "../../Engine.hpp"
const unsigned int IBaseComponent<Component::Timer>::typeID = 4364;
std::string IBaseComponent<Component::Timer>::componentName = "TimerComponent";

namespace Component
{
	Timer::~Timer()
	{
		Engine::game.removealTimed(attachedOn);
	}
	Timer::Timer(double lifeTime) : timedLife(lifeTime), currentTime(0)
	{

	}
	void Timer::update()
	{
		currentTime += Engine::time.deltaTime();
	}
	bool Timer::canRemove()
	{
		if (timedLife < currentTime)
			return true;
		return false;
	}
	void Timer::attachOn(GameObject* attachTo)
	{
		Timer::BaseComponent::attachOn(attachTo);
		Engine::game.addTimedObject(attachTo);
	}
}