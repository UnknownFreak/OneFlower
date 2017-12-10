#ifndef Time_HPP
#define Time_HPP

#include <map>

#include <SFML\System\Clock.hpp>

#include <Core\String.hpp>
#include <Core\IEngineResource\IEngineResource.hpp>

class Time : public IEngineResource<Time>
{

public:

	Time();

	double deltaTime();

	bool time(Core::String, double msec);
	void remove(Core::String);

	const sf::Time update_ms = sf::seconds(1.f / 30.f);

	sf::Time elapsed;
	sf::Clock clock;

	sf::Time physicsElapsed;
	sf::Clock physicsClock;

	const ResourceType& getType()
	{
		return type;
	}

private:
	sf::Clock timer;

	//LOW: Put this in Definer to avoid include of Map:String?
	std::map<Core::String, sf::Clock> timers;
};
#endif