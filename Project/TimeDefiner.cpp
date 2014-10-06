#include "Time.hpp"
#include <SFML\System\Time.hpp>
#include <iostream>
float Time::FPS()
{
	currentTime = clock.restart().asSeconds();
	if(timer.getElapsedTime().asSeconds() > 1)
	{
		float fps = 0;
		timer.restart();
		fps = 1.f / (currentTime);
		lastTime = currentTime;

		std::cout << "\nFPS: " << fps;
	}
}