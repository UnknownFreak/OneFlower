#include "GameEntry.hpp"

#include <thread>

#include <Module\BuildMode.hpp>

#include<File/GameConfig.hpp>

#include <Graphics/UI/Stats.hpp>
#include <Graphics/UI/BuildInfo.hpp>

#include <Graphics/UI/LoadingScreen.hpp>

#include <Graphics/Editor/EditorWindow.hpp>
#include <module/window/WindowProxy.hpp>
#include <Graphics/sky/skyBox.hpp>

#include <chrono>
#include <thread>
#include <iostream>

GameEntry::GameEntry() : 
	gfx(std::make_shared<of::graphics::window::Application>()),
	time(of::engine::GetModule<of::module::Time>()),
	input(of::engine::GetModule<Input::InputHandler>()),
	world(of::engine::GetModule<of::module::WorldManager>()), m_exit(false)
{
	of::engine::GetModule<of::module::window::WindowProxy>().setHandle(gfx);
	ups = std::make_shared<Graphics::UI::Stats>("UPS", 200.f, 70.f, Graphics::UI::Rel::Right);
	loadingScreenInfo = std::make_shared<Graphics::UI::LoadingScreenInfo>();
}


int GameEntry::Run()
{
	auto width = of::engine::GetModule<EngineModule::GameConfig>().videoMode.first;

	gfx->initialize();
	world.initialize();

	//gfx.setFramerate(of::engine::GetModule<EngineModule::GameConfig>().getFramerateLimit());

	gfx->addRenderable(of::graphics::window::RenderLayer::IMGUI, of::common::uuid(), std::make_shared<Graphics::UI::Stats>("FPS", 400.f, 70.f, Graphics::UI::Rel::Right));
	gfx->addRenderable(of::graphics::window::RenderLayer::IMGUI, of::common::uuid(), ups);
	gfx->addRenderable(of::graphics::window::RenderLayer::IMGUI, of::common::uuid(), std::make_shared<Graphics::UI::BuildInfo>(Engine::GetBuildMode().getDetailedBuildInfo(), 400.f, 10.f, Graphics::UI::Rel::Right));
	gfx->addRenderable(of::graphics::window::RenderLayer::IMGUI, of::common::uuid(), std::make_shared<Graphics::UI::Stats>("FPS", float(width - (200 * 2)), 70.f));

	gfx->addRenderable(of::graphics::window::RenderLayer::IMGUI, of::common::uuid(), std::make_shared<Graphics::UI::LoadingScreen>());
	gfx->addRenderable(of::graphics::window::RenderLayer::IMGUI, of::common::uuid(), loadingScreenInfo);

	/*
	gfx.postInitialize();

	auto& listener = gfx.getEventListener();
	listener.addListener("UIElementsUpdate", [](const swizzle::core::WindowEvent& evt) {
		if (evt.getEventType() == swizzle::core::WindowEventType::ResizeEvent)
		{
			auto& e = (const swizzle::core::WindowResizeEvent&)evt;

			auto& ui = of::engine::GetModule<Graphics::UI::UIHandler>();
			auto x = ui.getUIContext<Graphics::UI::UIContext>(Enums::UIContextNames::FPS);
			x->x = e.mWidth - 400.f;
			x = ui.getUIContext<Graphics::UI::UIContext>(Enums::UIContextNames::UPS);
			x->x = e.mWidth - 200.f;
			x = ui.getUIContext<Graphics::UI::UIContext>(Enums::UIContextNames::BuildInfo);
			x->x = e.mWidth - 400.f;
		}
		});
		*/
	if (Engine::GetBuildMode().isEditorMode())
	{
		gfx->addRenderable(of::graphics::window::RenderLayer::IMGUI, of::common::uuid(), std::make_shared<Graphics::Editor::MainEditorWindow>());
		/*
		listener.addListener("UIEditorElementsUpdate", [](const swizzle::core::WindowEvent& evt) {
			if (evt.getEventType() == swizzle::core::WindowEventType::ResizeEvent)
			{
				auto& e = (const swizzle::core::WindowResizeEvent&)evt;

				auto& ui = of::engine::GetModule<Graphics::UI::UIHandler>();
				auto editorWindow = ui.getUIContext<Graphics::Editor::MainEditorWindow>(Enums::UIContextNames::MainEditorWindow);
				editorWindow->setSize(e.mWidth, e.mHeight);
			}
			});
		*/
	}

	std::thread physics_thread(&GameEntry::physicsUpdate, this);


	gfx->loop();
	m_exit = true;
	physics_thread.join();

	//gfx.clearDrawList();
	return EXIT_SUCCESS;
}

void GameEntry::physicsUpdate()
{
	if (!Engine::GetBuildMode().isEditorMode())
	{
//		world.createMainMenu();
	}
	time.physicsElapsed = time.physicsClock.secondsAsFloat(true);
	const float update_time = time.update_ms;
	while (!m_exit)
	{
		while (world.isLoading)
		{
			time.physicsElapsed = time.update_ms;
			world.Update();
			loadingScreenInfo->update();
		}
		while (time.physicsElapsed >= time.update_ms)
		{
			time.physicsElapsed -= time.update_ms;
			{
				input.update(update_time);
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
