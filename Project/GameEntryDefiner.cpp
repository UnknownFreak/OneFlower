#include "GameEntry.hpp"

#include <SFML\System\Thread.hpp>
#include <SFML\Window\Event.hpp>

#include <Asset/AssetManagerCore.hpp>
#include <Core\EngineModule\EngineModuleManager.hpp>

#ifdef _EDITOR_
#include <Editor\MainEditorWindow.hpp>
#include <Editor\SplashScreen.hpp>
#endif

GameEntry::GameEntry() : gfx(Engine::GetModule<Gfx>()), time(Engine::GetModule<Time>()), input(Engine::GetModule<InputHandler>()),
world(Engine::GetModule<WorldManager>()), physics(Engine::GetModule<PhysicsEngine>()), m_exit(false)
{

}

int GameEntry::main()
{
#ifdef _EDITOR_
	SplashScreen^ splash = gcnew SplashScreen();
	MainEditorWindow^ window = splash->InitializeEditor();
#endif

	gfx.view.render.setFramerateLimit(200);
	gfx.view.render.setActive(false);
	sf::Thread render_thread(&GameEntry::render, this);
	render_thread.launch();
	sf::Thread physics_thread(&GameEntry::physicsUpdate, this);
	physics_thread.launch();

#ifndef _UNITTESTS_
#ifdef _EDITOR_
	MSG message;
	while(!window->isClosed())
		while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
#else
		while (gfx.view.render.isOpen())
		{
#endif
			while (gfx.view.render.pollEvent(Game::event))
			{
				if (Game::event.type == sf::Event::Closed)
				{
					gfx.view.render.close();
				}
				if (Game::event.type == Game::event.MouseWheelMoved)
					input.deltaScrolls += Game::event.mouseWheel.delta;
			}
		}
#endif
	m_exit = true;
	render_thread.wait();
	physics_thread.wait();

	return EXIT_SUCCESS;
}

void GameEntry::render()
{
	gfx.view.render.setActive(true);
	while (!m_exit)
	{
		if (world.isLoading())
		{
			world.loadSome();
			world.drawLoadingScreen();
		}
		else
		{
			update();
		}
	}
}

void GameEntry::update()
{
	time.elapsed += time.clock.restart();
	
	while (time.elapsed >= time.update_ms)
	{
		input.update();
		//Engine::GUI.updateMouseIcon();
		time.elapsed -= time.update_ms;
	}
	
	gfx.draw();
	//Engine::GUI.draw();
	gfx.view.render.display();
}

void GameEntry::mainMenuUpdater()
{

	time.elapsed += time.clock.restart();
	InputHandler& input = Engine::GetModule<InputHandler>();

	while (time.elapsed >= time.update_ms)
	{
		input.update();
		//Engine::GUI.updateMouseIcon();
		time.elapsed -= time.update_ms;
	}
	
	gfx.drawBG();
	gfx.view.render.display();
}

void GameEntry::physicsUpdate()
{
	while (!m_exit)
	{
		time.physicsElapsed += time.physicsClock.restart();
		while (time.physicsElapsed >= time.update_ms)
		{
			// Only update physics if we are not loading.
			if (!world.isLoading())
			{
				physics.update();
				//Engine::game.update();
			}
			time.physicsElapsed -= time.update_ms;
		}
	}
}

