#include "Time.hpp"
#include <SFML\System\Time.hpp>
#include <iostream>
#include <string>
#include "EditorUI\UIAddon.hpp"
#include "Engine.hpp"
HWND hWnd;
HWND wnd;
HWND awnd;


float Time::deltaTime()
{
	float deltaT = delta.getElapsedTime().asSeconds();
	return deltaT;
}

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
		{
			SetWindowTextA(hWnd,std::to_string(fps).c_str());
			SetWindowTextA(wnd,std::to_string(EditorUI::GetLocalCoordinates(Engine::Window.hWnd).right).c_str());
			SetWindowTextA(awnd,std::to_string(EditorUI::GetLocalCoordinates(Engine::Window.hWnd).left).c_str());
		}
		else
		{
			hWnd = GetDlgItem(Engine::Window.hWnd,9003);
			wnd = GetDlgItem(Engine::Window.hWnd,9056);
			awnd = GetDlgItem(Engine::Window.hWnd,9057);
		}
		return 1;
	}
	return 0;
}
bool Time::time(std::string name,int sec)
{
	std::map<std::string,sf::Clock>::iterator it = timers.find(name);
	if(it == timers.end())
	{
		it = timers.insert(std::make_pair(name,sf::Clock())).first;
		return 0;
	}
	else
	{
		//LOW: Research if needed
		//Make it modulus instead, Also make a custom Holder so that we can have diffrent start timer if needed
		if(it->second.getElapsedTime().asSeconds() > sec)
		{
			//Make it so that it doesnt restart
			it->second.restart();
			return 1;
		}
	}
	return 0;
}
void Time::remove(std::string name)
{
	timers.erase(name);
}