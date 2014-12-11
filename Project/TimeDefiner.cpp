#include "Time.hpp"
#include <SFML\System\Time.hpp>
#include <iostream>
#include <string>
#include "Engine.hpp"
HWND hWnd;
float Time::FPS()
{
	currentTime = clock.restart().asSeconds();
	if(timer.getElapsedTime().asSeconds() > 1)
	{
		float fps = 0;
		timer.restart();
		fps = 1.f / (currentTime);
		lastTime = currentTime;
		if(hWnd)
			SetWindowText(hWnd,std::to_string(fps).c_str());
		else
			hWnd = GetDlgItem(Engine::Window.hWnd,9003);
	}
	return 0;
}