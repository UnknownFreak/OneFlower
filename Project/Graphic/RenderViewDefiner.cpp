#include "RenderView.hpp"
#include <Core\EngineSettings.hpp>
//#include <Windows.h>
//LRESULT CALLBACK WndProcGameView(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam);
RenderView::RenderView() : size(Engine::Settings.res.width, Engine::Settings.res.height)
{
	render.create(sf::VideoMode(800, 600), "Game View");
	camera.reset(sf::FloatRect(0, 0, 800, 600));
}
