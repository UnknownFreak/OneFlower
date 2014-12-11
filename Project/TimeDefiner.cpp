#include "Time.hpp"
#include <SFML\System\Time.hpp>
#include <iostream>
#include <string>
#include "EditorUI\UIAddon.hpp"
#include "Engine.hpp"
HWND hWnd;
HWND wnd;
HWND awnd;
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
			SetWindowText(hWnd,std::to_string(fps).c_str());
			SetWindowText(wnd,std::to_string(EditorUI::GetLocalCoordinates(Engine::Window.hWnd).right).c_str());
			SetWindowText(awnd,std::to_string(EditorUI::GetLocalCoordinates(Engine::Window.hWnd).left).c_str());
		}
		else
		{
			hWnd = GetDlgItem(Engine::Window.hWnd,9003);
			wnd = GetDlgItem(Engine::Window.hWnd,9056);
			awnd = GetDlgItem(Engine::Window.hWnd,9057);
		}
	}
	return 0;
}