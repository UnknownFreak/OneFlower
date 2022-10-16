#include "GameEntry.hpp"

#include <thread>

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


int GameEntry::Run()
{
#ifdef _EDITOR_
	SplashScreen^ splash = gcnew SplashScreen();
	MainEditorWindow^ window = splash->InitializeEditor();
#endif

	auto width = Engine::GetModule<EngineModule::GameConfig>().videoMode.first;

	physics.renderBox = gfx.renderBox;
	gfx.initialize();
	world.initialize();
	gfx.setFramerate(Engine::GetModule<EngineModule::GameConfig>().getFramerateLimit());

	gfx.ui.addUIContext(Enums::UIContextNames::FPS, std::make_unique<Graphics::UI::Stats>("FPS", float(width - (200 * 2)), 50.f));
	gfx.ui.addUIContext(Enums::UIContextNames::UPS, std::make_unique<Graphics::UI::Stats>("UPS", float(width - 200), 50.f));
	gfx.ui.addUIContext(Enums::UIContextNames::BuildInfo, std::make_unique<Graphics::UI::BuildInfo>(Engine::GetBuildMode().getBuildNumberAsStringWithEditor(), float(width - (200 * 2)), 5.f));
	
	gfx.postInitialize();

	std::thread physics_thread(&GameEntry::physicsUpdate, this);


	gfx.run();
	m_exit = true;
	physics_thread.join();

	gfx.clearDrawList();
	return EXIT_SUCCESS;
}

void GameEntry::physicsUpdate()
{
	world.createSimpleWorld();
	auto ups = gfx.ui.getUIContext<Graphics::UI::Stats>(Enums::UIContextNames::UPS);
	time.physicsElapsed = time.physicsClock.secondsAsFloat(true);
	const float update_time = time.update_ms;
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
		time.physicsElapsed += time.physicsClock.secondsAsFloat(true);
	}
	std::cout << "Physics Exited!!" << std::endl;

}
