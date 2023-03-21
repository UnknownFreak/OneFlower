#include "EditorWindow.hpp"

#include <File/GameConfig.hpp>

#include <file/Handler.hpp>

void Graphics::Editor::MainEditorWindow::renderMenuBar()
{
	if (ImGui::BeginMainMenuBar())
	{
		//if (ImGui::IsKeyPressed((ImGuiKey)((int)ImGuiKeyModFlags_Ctrl | (int)ImGuiKey_N)) && newFileModal.isClosed())
		//{
		//	newFileModal.open();
		//}
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New", "Ctrl + N"))
			{
				newFileModal.open();
			}
			if (ImGui::MenuItem("Save", "Ctrl + S"))
			{
				auto& manager = of::engine::GetModule<of::file::Handler>();
				manager.saveGameDatabase(manager.openedFile.name, manager.openedFile);
			}
			if (ImGui::MenuItem("Load"))
			{
				loadFileModal.open();
			}
			if (ImGui::MenuItem("Save & Reload Dependencies", "Ctrl + Shift + R"))
			{

			}
			ImGui::Separator();
			if (ImGui::MenuItem("Exit", "Alt + F4"))
			{
				std::exit(0);
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Tools"))
		{
			// Terrain
			// Objects
			// Ai etc
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Translation"))
		{
			// Translation file management
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("UI"))
		{
			// UI customization
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Settings"))
		{
			// EditorSettings
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::MenuItem("Help"))
			{
			}
			if (ImGui::MenuItem("About"))
			{
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
	if (newFileModal.isOpen())
		newFileModal.show();
	if (loadFileModal.isOpen())
		loadFileModal.show();
	newFileModal.ImGuiRenderModal();
	loadFileModal.ImGuiRenderModal();
}

void Graphics::Editor::MainEditorWindow::setSize(const unsigned& inWidth, const unsigned& inHeight)
{
	width = (float)inWidth;
	height = (float)inHeight-30;
}

Graphics::Editor::MainEditorWindow::MainEditorWindow() : UI::UIContext(swizzle::input::Keys::KeyNone, "MainWindow", true), tree(height), newFileModal("New File", tree), loadFileModal("Load File", tree)
{
	auto gc = of::engine::GetModule<EngineModule::GameConfig>();
	width = (float)gc.videoMode.first;
	height = (float)gc.videoMode.second-30;
}

void Graphics::Editor::MainEditorWindow::onMouseHover(const glm::vec2&)
{
}

void Graphics::Editor::MainEditorWindow::readInput()
{
}

void Graphics::Editor::MainEditorWindow::render()
{
	if (visible)
	{
		ImGui::SetNextWindowPos({ 0.f, 0.f });
		ImGui::SetNextWindowSize({width, 0.f});
		ImGui::SetNextWindowBgAlpha(0);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0,0 });
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.f);
		ImGui::Begin(this->uiName.c_str(), nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav |ImGuiWindowFlags_NoBringToFrontOnFocus |ImGuiWindowFlags_MenuBar);
		ImGui::PopStyleVar(2);
		{
			renderMenuBar();
			//tree.render();
		}
		ImGui::End();

	}
}

void Graphics::Editor::MainEditorWindow::updateFrame(const float& )
{
}

void Graphics::Editor::MainEditorWindow::render(std::unique_ptr<swizzle::gfx::DrawCommandTransaction>& , of::graphics::view::MVP& )
{
	render();
}
