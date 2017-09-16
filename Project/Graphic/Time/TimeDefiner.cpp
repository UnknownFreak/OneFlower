#include "Time.hpp"
#include <string>
//#include <SFML\System\Time.hpp>
/*
HWND hWnd;
HWND wnd;
HWND awnd;
//*/
double Time::deltaTime()
{
	return update_ms.asSeconds();
}
bool Time::time(Core::String name, double msec)

{
	std::map<Core::String, sf::Clock>::iterator it = timers.find(name);
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
void Time::remove(Core::String name)
{
	timers.erase(name);
}