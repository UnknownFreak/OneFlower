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

#include <graphics/ui/frame.hpp>
#include <module/window/GraphicsProxy.hpp>
#include <module/resource/TextureLoader.hpp>
#include <module/resource/ShaderLoader.hpp>
#include <module/window/GraphicsProxy.hpp>

#include <imgui/imgui_impl_swizzle.hpp>
#include <imgui/of_imgui_extensions.hpp>

class ttext : public of::graphics::ui::UIRenderable
{
	of::common::String m_s;
	std::shared_ptr<sw::gfx::Texture> tex;
	std::shared_ptr<sw::gfx::Material> material;
	of::imgui::ProgressBarSettings settings {
		ImVec2{0.f, 0.f},ImVec2{1.f, 0.5f},
		ImVec2{0.f, 0.5f}, ImVec2{1.f, 1.f}
	};
	float min = 0.f;
	float max = 100.f;
	float c = 50.f;
public:
	ttext(of::common::String s, const ImVec4& x, const of::graphics::ui::Relation& rel) : of::graphics::ui::UIRenderable(x, rel), m_s(s) 
	{
		tex = of::engine::GetModule<of::module::texture::Loader>().requestTexture("Progressbar.png");
		auto& proxy = of::engine::GetModule<of::module::window::Proxy>();

		material = ImGui_ImplSwizzle_CreateMaterial(proxy.getGfxContext());
		material->setDescriptorTextureResource(0, tex);
	}

	virtual void beginRender() override 
	{
	}
	virtual void endRender() override {}

	virtual void render() override
	{
		ImGui::SetCursorPos({m_renderBox.x, m_renderBox.y});
		//ImGui::Text(m_s.c_str());
		//ImGui::Image(&material, {64.f, 64.f});
		ImGui::SliderFloat("Value", &c, min, max);
		of::imgui::Progressbar(&material, {64.f, 16.f}, min, max, c, settings);
	}
};


class tttext : public of::graphics::ui::UIRenderable
{
public:
	tttext(const ImVec4& x, const of::graphics::ui::Relation& rel) : of::graphics::ui::UIRenderable(x, rel) {}

	virtual void beginRender() override {}
	virtual void endRender() override {}

	virtual void render() override
	{
		ImGui::SetCursorPos({ m_renderBox.x, m_renderBox.y });
		if (ImGui::BeginCombo("selector", nullptr))
		{
			if (ImGui::Selectable("TOP_LEFT")) { m_uiParent->m_windowRelation = of::graphics::ui::Relation::TOP_LEFT; }
			else if (ImGui::Selectable("LEFT")) { m_uiParent->m_windowRelation = of::graphics::ui::Relation::LEFT; }
			else if (ImGui::Selectable("BOTTOM_LEFT")) { m_uiParent->m_windowRelation = of::graphics::ui::Relation::BOTTOM_LEFT; }
			else if (ImGui::Selectable("TOP")) { m_uiParent->m_windowRelation = of::graphics::ui::Relation::TOP; }
			else if (ImGui::Selectable("CENTER")) { m_uiParent->m_windowRelation = of::graphics::ui::Relation::CENTER; }
			else if (ImGui::Selectable("BOTTOM")) { m_uiParent->m_windowRelation = of::graphics::ui::Relation::BOTTOM; }
			else if (ImGui::Selectable("TOP_RIGHT")) { m_uiParent->m_windowRelation = of::graphics::ui::Relation::TOP_RIGHT; }
			else if (ImGui::Selectable("RIGHT")) { m_uiParent->m_windowRelation = of::graphics::ui::Relation::RIGHT; }
			else if (ImGui::Selectable("BOTTOM_RIGHT")) { m_uiParent->m_windowRelation = of::graphics::ui::Relation::BOTTOM_RIGHT; }
			ImGui::EndCombo();
		}
	}
};

class Test : public of::graphics::ui::Frame
{
public:
	Test(const ImVec4& x, const of::graphics::ui::Relation& rel) : of::graphics::ui::Frame(x, rel) 
	{

		add(std::make_shared<tttext>(ImVec4{0.f, 0.f, 200.f, 20.f}, of::graphics::ui::Relation::TOP_LEFT));
		add(std::make_shared<ttext>("TL", ImVec4{0.f, 25.f, 200.f, 64}, of::graphics::ui::Relation::TOP_LEFT));
	}
};


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

	gfx->addRenderable(of::graphics::window::RenderLayer::IMGUI, of::common::uuid(), std::make_shared<Test>(ImVec4{ 0, 50.f, 200.f, 200.f }, of::graphics::ui::Relation::TOP));

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
		//gfx->addRenderable(of::graphics::window::RenderLayer::IMGUI, of::common::uuid(), std::make_shared<Graphics::Editor::MainEditorWindow>());
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
