#include "GameEntry.hpp"

#include <SFML\System\Thread.hpp>
#include <SFML\Window\Event.hpp>

//#include <File/Asset/Manager.hpp>
#include <Module\EngineModuleManager.hpp>
#include <Module\BuildMode.hpp>

#include<File/GameConfig.hpp>

#include <Graphics/UI/Stats.hpp>
#include <Graphics/UI/BuildInfo.hpp>

#ifdef _EDITOR_
#include <Editor\MainEditorWindow.hpp>
#include <Editor\SplashScreen.hpp>
#endif

#include <chrono>
#include <thread>
#include <iostream>

GameEntry::GameEntry() : 
	gfx(Engine::GetModule<Graphics::RenderWindow>()),
	physics(Engine::GetModule<Physics::PhysicsEngine>()),
	time(Engine::GetModule<EngineModule::Time>()),
	input(Engine::GetModule<Input::InputHandler>()),
	world(gfx),
	console(Engine::GetModule<Console>()), m_exit(false)
{
}

void GameEntry::moveCamera(const Core::Vector2f& vec)
{
	gfx.moveCamera(vec);
}


int GameEntry::Run()
{
#ifdef _EDITOR_
	SplashScreen^ splash = gcnew SplashScreen();
	MainEditorWindow^ window = splash->InitializeEditor();
#endif

	auto width = Engine::GetModule<EngineModule::GameConfig>().videoMode.width;

	physics.renderBox = gfx.renderBox;
	gfx.setFramerate(Engine::GetModule<EngineModule::GameConfig>().getFramerateLimit());
	gfx.setActive(false);
	gfx.ui.addUIContext(Enums::UIContextNames::FPS, std::make_unique<Graphics::UI::Stats>("FPS", float(width - (140 * 2)), 30.f));
	gfx.ui.addUIContext(Enums::UIContextNames::UPS, std::make_unique<Graphics::UI::Stats>("UPS", float(width - 140), 30.f));
	gfx.ui.addUIContext(Enums::UIContextNames::BuildInfo, std::make_unique<Graphics::UI::BuildInfo>(Engine::GetBuildMode().getBuildNumberAsStringWithEditor(), float(width - (140 * 2)), 10.f));
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
		while (gfx.isOpen())
		{
#endif
			while (gfx.window->pollEvent(Game::event))
			{
				if (Game::event.type == sf::Event::Closed)
				{
					gfx.window->close();
				}
				if (input.isConsoleEnabled())
				{
					if (Game::event.type == sf::Event::TextEntered)
					{
						if (Game::event.text.unicode < 128)
						{
							char c = (char)Game::event.text.unicode;
							if (c == '\n' || c == '\r')
								console.execute();
							else if (c == char(8))
							{
								console.removeLastCharacter();
							}
							else
								console.addCharacter(c);
						}
					}
				}
			}
			//gfx.poll(Game::event);
		}
#endif
	m_exit = true;
	render_thread.wait();
	physics_thread.wait();

	gfx.clearDrawList();
	return EXIT_SUCCESS;
}

void GameEntry::render()
{
	auto fps = gfx.ui.getUIContext<Graphics::UI::Stats>(Enums::UIContextNames::FPS);

	gfx.setActive(true);
	fps->reset();
	while (!m_exit)
	{
		fps->update();
		fps->print();
		update();
		gfx.window->display();
	}
}

void GameEntry::update()
{
	//time.elapsed += time.clock.restart();
	//while (time.elapsed >= time.update_ms)
	//{
//	//	//Engine::GUI.updateMouseIcon();
	//	time.elapsed -= time.update_ms;
	//}
	if (!world.isLoading)
	{
		gfx.draw();
	}
	else
		gfx.window->clear();
	gfx.drawUI();

	//gfx.window->draw(fps);
	//gfx.window->draw(ups);

}

void GameEntry::physicsUpdate()
{
	world.createSimpleWorld();
	auto ups = gfx.ui.getUIContext<Graphics::UI::Stats>(Enums::UIContextNames::UPS);
	ups->reset();
	time.physicsElapsed = time.physicsClock.restart();
	const float update_time = time.update_ms.asSeconds();
	while (!m_exit)
	{
		while (world.isLoading)
		{
			time.physicsElapsed = time.update_ms;
			world.Update();
		}
		while (time.physicsElapsed >= time.update_ms)
		{
			time.physicsElapsed -= time.update_ms;
			{
				input.update(update_time);
				physics.update(update_time);
				world.Simulate(update_time);
				time.Simulate(update_time);
				ups->update();
				ups->print();
			}
		}
		time.physicsElapsed += time.physicsClock.restart();
	}
	std::cout << "Physics Exited!!" << std::endl;

}
