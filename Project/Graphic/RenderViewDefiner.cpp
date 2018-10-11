#include "RenderView.hpp"
#include <SFML\Graphics\Image.hpp>
#include <Core\EngineModule\EngineModuleManager.hpp>
#include <Core\EngineSettings.hpp>
//LRESULT CALLBACK WndProcGameView(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam);
RenderView::RenderView() : size(Engine::GetModule<Settings::EngineSettings>().res.width,
								Engine::GetModule<Settings::EngineSettings>().res.height)
{

#ifndef _EDITOR_
	render.create(sf::VideoMode(800, 600), "Game View");
#endif

}
#ifdef _EDITOR_
void RenderView::init(HWND parent)
#else
void RenderView::init()
#endif
{
#ifdef _EDITOR_
	render.create(parent);
	//render.create(sf::VideoMode(800,600), "Game View");
	//SetParent(render.getSystemHandle(), parent);
#else
	render.create(sf::VideoMode(Engine::GetModule<Settings::EngineSettings>().res.width, Engine::GetModule<Settings::EngineSettings>().res.width), "One Flower");
#endif
	camera.reset(sf::FloatRect(0, 0, 800, 600));
	sf::Image img;
	img.loadFromFile("Flower.png");
	render.setIcon(128, 128, img.getPixelsPtr());
	Settings::EngineSettings::VSYNC vsync = Engine::GetModule<Settings::EngineSettings>().vsync;
	render.setVerticalSyncEnabled(vsync == Settings::EngineSettings::VSYNC::ON ? true : false);
}