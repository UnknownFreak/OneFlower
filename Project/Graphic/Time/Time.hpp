#ifndef Time_HPP
#define Time_HPP
#include <SFML\System\Clock.hpp>
#include <map>
#include <Core/String.hpp>
class Time
{
public:

	double deltaTime();

	bool time(Core::String, double msec);
	void remove(Core::String);

	const sf::Time update_ms = sf::seconds(1.f / 30.f);

	sf::Time elapsed;
	sf::Clock clock;

private:
	sf::Clock timer;

	//LOW: Put this in Definer to avoid include of Map:String?
	std::map<Core::String, sf::Clock> timers;
};

#endif