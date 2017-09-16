#include "RenderView.hpp"
#include <Core\EngineSettings.hpp>
#include <SFML\Graphics\Image.hpp>
//LRESULT CALLBACK WndProcGameView(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam);
RenderView::RenderView() : size(Engine::Settings.res.width, Engine::Settings.res.height)
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
	render.create(sf::VideoMode(Engine::Settings.res.width, Engine::Settings.res.width), "Game View");
#endif
	camera.reset(sf::FloatRect(0, 0, 800, 600));
	sf::Image img;
	img.loadFromFile("Flower.png");
	render.setIcon(128, 128, img.getPixelsPtr());
}