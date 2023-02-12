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
	of::common::String val;
	of::common::String duration;
	of::common::String blink;
	std::shared_ptr<sw::gfx::Texture> tex;
	std::shared_ptr<sw::gfx::Texture> tex2;
	std::shared_ptr<sw::gfx::Material> material;
	std::shared_ptr<sw::gfx::Material> material2;
	of::imgui::ProgressBarSettings settings {
		ImVec2{0.f, 0.f},ImVec2{1.f, 0.5f},
		ImVec2{0.f, 0.5f}, ImVec2{1.f, 1.f}
	};

	of::imgui::BuffIconSettings settings2 {true, 50, false, "Test", "body tooltip"};
	float min = 0.f;
	float max = 10.f;
	float c = 5.f;
	float u = -1.f;
	float barX = 800.f;
	float barY = 64.f;

	float cornerX = 32.f;
	float cornerY = 16.f;
	bool delay;
	float diminishSpeed = 0.01f;
	int idx = 0;
public:
	ttext(of::common::String s, const ImVec4& x, const of::graphics::ui::Relation& rel) : of::graphics::ui::UIRenderable(x, rel), m_s(s) 
	{
		val = "Value ###" + of::common::uuid().to_string();
		duration = "ShowDurationBar ###" + of::common::uuid().to_string();
		blink = "Icon blink on expire ###" + of::common::uuid().to_string();
		tex = of::engine::GetModule<of::module::texture::Loader>().requestTexture("ProgressBar.png");
		tex2 = of::engine::GetModule<of::module::texture::Loader>().requestTexture("EffectIconFrame.png", of::module::Settings::uiTexturePath);
		auto& proxy = of::engine::GetModule<of::module::window::Proxy>();

		material = ImGui_ImplSwizzle_CreateMaterial(proxy.getGfxContext());
		material2 = ImGui_ImplSwizzle_CreateMaterial(proxy.getGfxContext());
		material->setDescriptorTextureResource(0, tex);
		material2->setDescriptorTextureResource(0, tex2);
	}

	virtual void beginRender() override 
	{
	}
	virtual void endRender() override {}

	virtual void render() override
	{
		ImGui::SetCursorPos({m_renderBox.x, m_renderBox.y});
		ImGui::SliderFloat(val.c_str(), &c, min, max);
		ImGui::SliderFloat("AnimateFraction", &u, min, 1.f);
		ImGui::SliderFloat("DiminishSpeed", &diminishSpeed, min, 0.1f);
		ImGui::Checkbox("Delay", &delay);
		of::imgui::ProgressbarHitEffect({200.f, 20.f}, min, max, c, u, ImColor(0,0,0), ImColor(0,200, 0), ImColor(0, 255,0), delay, diminishSpeed);
		ImGui::SliderInt("ObjectiveState", &idx, 0, 2);
		of::imgui::objectiveIcon("test", (of::imgui::ObjectiveState)idx);
		//ImGui::Checkbox(duration.c_str(), &settings2.showIconDuration);
		//ImGui::Checkbox("ShowDurationSeconds", &settings2.showIconDurationInSeconds);
		//ImGui::Checkbox(blink.c_str(), &settings2.flashIconWhenAboutToExpire);
		//of::imgui::BuffIcon(&material2, { 32.f, 32.f }, max, c, settings2);
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
		//add(std::make_shared<tttext>(ImVec4{0.f, 0.f, 200.f, 20.f}, of::graphics::ui::Relation::TOP_LEFT));
		add(std::make_shared<ttext>("TL", ImVec4{0.f, 25.f, 1000.f, 200.f}, of::graphics::ui::Relation::TOP));
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

	gfx->addRenderable(of::graphics::window::RenderLayer::IMGUI, of::common::uuid(), std::make_shared<Test>(ImVec4{ 0, 25.f, 1000.f, 400.f }, of::graphics::ui::Relation::TOP));

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
