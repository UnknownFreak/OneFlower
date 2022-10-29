#include "GameEntry.hpp"

#include <thread>

//#include <File/Asset/Manager.hpp>
#include <Module\EngineModuleManager.hpp>
#include <Module\BuildMode.hpp>

#include<File/GameConfig.hpp>

#include <Graphics/UI/Stats.hpp>
#include <Graphics/UI/BuildInfo.hpp>

#include <Graphics/Editor/EditorWindow.hpp>
#include <Graphics/Editor/ObjectSelector.hpp>

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
	auto width = Engine::GetModule<EngineModule::GameConfig>().videoMode.first;

	physics.renderBox = gfx.renderBox;
	gfx.initialize();
	world.initialize();
	gfx.setFramerate(Engine::GetModule<EngineModule::GameConfig>().getFramerateLimit());

	gfx.ui.addUIContext(Enums::UIContextNames::FPS, std::make_unique<Graphics::UI::Stats>("FPS", float(width - (200 * 2)), 70.f));
	gfx.ui.addUIContext(Enums::UIContextNames::UPS, std::make_unique<Graphics::UI::Stats>("UPS", float(width - 200), 70.f));
	gfx.ui.addUIContext(Enums::UIContextNames::BuildInfo, std::make_unique<Graphics::UI::BuildInfo>(Engine::GetBuildMode().getDetailedBuildInfo(), float(width - (200 * 2)), 10.f));
	


	gfx.postInitialize();

	auto& listener = gfx.getEventListener();
	listener.addListener("UIElementsUpdate", [](const swizzle::core::WindowEvent& evt) {
		if (evt.getEventType() == swizzle::core::WindowEventType::ResizeEvent)
		{
			auto& e = (const swizzle::core::WindowResizeEvent&)evt;

			auto& ui = Engine::GetModule<Graphics::UI::UIHandler>();
			auto x = ui.getUIContext<Graphics::UI::UIContext>(Enums::UIContextNames::FPS);
			x->x = e.mWidth - 400.f;
			x = ui.getUIContext<Graphics::UI::UIContext>(Enums::UIContextNames::UPS);
			x->x = e.mWidth - 200.f;
			x = ui.getUIContext<Graphics::UI::UIContext>(Enums::UIContextNames::BuildInfo);
			x->x = e.mWidth - 400.f;
		}
		});

	if (Engine::GetBuildMode().isEditorMode())
	{
		gfx.ui.addUIContext(Enums::UIContextNames::MainEditorWindow, std::make_unique<Graphics::Editor::MainEditorWindow>());
		gfx.ui.addUIContext(Enums::UIContextNames::ObjectSelector, std::make_unique<Graphics::Editor::ObjectSelector>());

		listener.addListener("UIEditorElementsUpdate", [](const swizzle::core::WindowEvent& evt) {
			if (evt.getEventType() == swizzle::core::WindowEventType::ResizeEvent)
			{
				auto& e = (const swizzle::core::WindowResizeEvent&)evt;

				auto& ui = Engine::GetModule<Graphics::UI::UIHandler>();
				auto editorWindow = ui.getUIContext<Graphics::Editor::MainEditorWindow>(Enums::UIContextNames::MainEditorWindow);
				editorWindow->setSize(e.mWidth, e.mHeight);
			}
			});
	}

	std::thread physics_thread(&GameEntry::physicsUpdate, this);


	gfx.run();
	m_exit = true;
	physics_thread.join();

	gfx.clearDrawList();
	return EXIT_SUCCESS;
}

void GameEntry::physicsUpdate()
{
	if (!Engine::GetBuildMode().isEditorMode())
	{
		world.createSimpleWorld();
//		world.createMainMenu();
	}
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
