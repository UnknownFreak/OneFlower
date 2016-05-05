#ifndef Time_HPP
#define Time_HPP
#include <SFML\System\Clock.hpp>
#include <map>
#include <string>
class Time
{
public:

	double deltaTime();

	bool time(std::string,double msec);
	void remove(std::string);
	


	const sf::Time update_ms = sf::seconds(1.f / 30.f);

	sf::Time elapsed;
	sf::Clock clock;

private:
	sf::Clock timer;

	//LOW: Put this in Definer to avoid include of Map:String?
	std::map<std::string,sf::Clock> timers;
};

#endif