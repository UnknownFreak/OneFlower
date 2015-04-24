#ifndef Time_HPP
#define Time_HPP
#include <SFML\System\Clock.hpp>
#include <map>
#include <string>
class Time
{
public:

	float FPS();
	bool time(std::string,double sec);
	void remove(std::string);
	float deltaTime();
	void restartDelta();

private:
	sf::Clock delta;
	sf::Clock clock;
	sf::Clock timer;
	float lastTime = 0;
	float currentTime = 0;

	//LOW: Put this in Definer to avoid include of Map:String?
	std::map<std::string,sf::Clock> timers;
};

#endif