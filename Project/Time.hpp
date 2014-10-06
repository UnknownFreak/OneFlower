#ifndef Time_HPP
#define Time_HPP
#include <SFML\System\Clock.hpp>
class Time
{

	sf::Clock clock;
	sf::Clock timer;	
	float lastTime = 0;
	float currentTime = 0;

public:
	float FPS();
	
}

#endif