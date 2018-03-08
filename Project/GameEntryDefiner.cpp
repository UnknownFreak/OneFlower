#include "GameEntry.hpp"

#include <SFML\System\Thread.hpp>
#include <SFML\Window\Event.hpp>

#include <Core\Core.hpp>
#include <Core\IEngineResource\EngineResourceManager.hpp>

#include <Graphic\GraphicsCore.hpp>

#ifdef _EDITOR_
#include <EditorManager\MainEditorWindow.hpp>
#include <EditorManager\SplashScreen.hpp>
#endif

GameEntry::GameEntry() : gfx(Engine::Get<Gfx>()), time(Engine::Get<Time>()), input(Engine::Get<InputHandler>()),
world(Engine::Get<WorldManager>()), physics(Engine::Get<PhysicsEngine>())
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
			while (gfx.view.render.pollEvent(Engine::event))
			{
				if (Engine::event.type == sf::Event::Closed)
				{
					gfx.view.render.close();
				}
				if (Engine::event.type == Engine::event.MouseWheelMoved)
					input.deltaScrolls += Engine::event.mouseWheel.delta;
			}
		}
#endif
	render_thread.terminate();
	physics_thread.terminate();
	render_thread.wait();

	return EXIT_SUCCESS;
}

void GameEntry::render()
{
	gfx.view.render.setActive(true);
	while (gfx.view.render.isOpen())
	{
		if (world.getIsLoading())
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
	InputHandler& input = Engine::Get<InputHandler>();

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
	while (gfx.view.render.isOpen())
	{
		time.physicsElapsed += time.physicsClock.restart();
		while (time.physicsElapsed >= time.update_ms)
		{
			// Only update physics if we are not loading.
			if (!world.getIsLoading())
			{
				physics.update();
				//Engine::game.update();
			}
			time.physicsElapsed -= time.update_ms;
		}
	}
}

